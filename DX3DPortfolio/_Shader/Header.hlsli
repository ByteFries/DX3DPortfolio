
cbuffer World : register(b0)
{
    matrix world;
    int hasAnimation;
};

cbuffer View : register(b1)
{
    matrix view;
    matrix invView;
};

cbuffer Proj : register(b2)
{
    matrix proj;
};

cbuffer MaterialBuffer : register(b1)
{
    float4 diffuseColor;
    float4 specularColor;
    float4 ambientColor;
    float4 emissive;
    
    int hasDiffuse;
    int hasSpecular;
    int hasNormal;
    float shininess;
    
    int affectByLight;
}

struct Frame
{
    int clipIndex;
    uint curFrame;
    uint nextFrame;
    float time;
    
    float speed;
    float framePadding1;
    float framePadding2;
    float framePadding3;
};

struct Motion
{
    float tweenTime;
    float runningTime;
    float takeTime;
    float padding2;
    
    Frame cur, next;
};

cbuffer FrameBuffer : register(b3)
{
    Motion motion;
}

#define MAX_INSTANCE 128

cbuffer FrameInstancingBuffer : register(b4)
{
    Motion motions[MAX_INSTANCE];
}

Texture2DArray transformMap : register(t0);
Texture2DArray matrixMap : register(t1);

struct VertexDefault
{
    float4 pos : POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float4 indices : INDICES;
    float4 weights : WEIGHTS;
};

struct Vertex44
{
    float4 pos : POSITION;
    float4 data : DATA;
};

struct Vertex42
{
    float4 pos : POSITION;
    float2 data : DATA;
};

Texture2D diffuseMap : register(t0);
Texture2D specularMap : register(t1);
Texture2D normalMap : register(t2);

SamplerState samp : register(s0);

float4x4 GetTranslationMatrix(float3 translation)
{
    float4x4 M;
    
    M[0][0] = 1.0f;
    M[1][0] = 0.0f;
    M[2][0] = 0.0f;
    M[3][0] = 0.0f;
    
    M[0][1] = 0.0f;
    M[1][1] = 1.0f;
    M[2][1] = 0.0f;
    M[3][1] = 0.0f;
    
    M[0][2] = 0.0f;
    M[1][2] = 0.0f;
    M[2][2] = 1.0f;
    M[3][2] = 0.0f;
    
    M[0][3] = translation.x;
    M[1][3] = translation.y;
    M[2][3] = translation.z;
    M[3][3] = 1.0f;
    
    return M;
}

float4x4 GetQuatRotationMatrix(float4 quat)
{
    float qx = quat.x;
    float qxx = qx * qx;

    float qy = quat.y;
    float qyy = qy * qy;

    float qz = quat.z;
    float qzz = qz * qz;

    float qw = quat.w;

    float4x4 M;
    
    M[0][0] = 1.f - 2.f * qyy - 2.f * qzz;
    M[1][0] = 2.f * qx * qy + 2.f * qz * qw;
    M[2][0] = 2.f * qx * qz - 2.f * qy * qw;
    M[3][0] = 0.f;
    
    M[0][1] = 2.f * qx * qy - 2.f * qz * qw;
    M[1][1] = 1.f - 2.f * qxx - 2.f * qzz;
    M[2][1] = 2.f * qy * qz + 2.f * qx * qw;
    M[3][1] = 0.f;
    
    M[0][2] = 2.f * qx * qz + 2.f * qy * qw;
    M[1][2] = 2.f * qy * qz - 2.f * qx * qw;
    M[2][2] = 1.f - 2.f * qxx - 2.f * qyy;
    M[3][2] = 0.f;
    
    M[0][3] = 0.f;
    M[1][3] = 0.f;
    M[2][3] = 0.f;
    M[3][3] = 1.0f;
    
    return M;
}

float4x4 GetScaleMatrix(float3 scale)
{
    return float4x4(
        float4(scale.x, 0.0f, 0.0f, 0.0f),
        float4(0.0f, scale.y, 0.0f, 0.0f),
        float4(0.0f, 0.0f, scale.z, 0.0f),
        float4(0.0f, 0.0f, 0.0f, 1.0f)
    );
}

float4x4 CombinedTransformMatrix(float3 translation, float4 quaternion, float3 scale)
{
    return mul(mul(GetTranslationMatrix(translation), GetQuatRotationMatrix(quaternion)), GetScaleMatrix(scale));
}

float4x4 TransposeMatrix(float4x4 m)
{
    return float4x4(
        m[0][0], m[1][0], m[2][0], m[3][0],
        m[0][1], m[1][1], m[2][1], m[3][1],
        m[0][2], m[1][2], m[2][2], m[3][2],
        m[0][3], m[1][3], m[2][3], m[3][3]
    );
}

//TQuat<T> TQuat<T>::Slerp_NotNormalized(const TQuat<T>& Quat1, const TQuat<T>& Quat2, T Slerp)
//{
//	// Get cosine of angle between quats.
//	const T RawCosom =
//		Quat1.X * Quat2.X +
//		Quat1.Y * Quat2.Y +
//		Quat1.Z * Quat2.Z +
//		Quat1.W * Quat2.W;
//	// Unaligned quats - compensate, results in taking shorter route.
//	const T Cosom = FMath::FloatSelect(RawCosom, RawCosom, -RawCosom);
//
//	T Scale0, Scale1;
//
//	if (Cosom < T(0.9999f))
//	{
//		const T Omega = FMath::Acos(Cosom);
//		const T InvSin = T(1.f) / FMath::Sin(Omega);
//		Scale0 = FMath::Sin((T(1.f) - Slerp) * Omega) * InvSin;
//		Scale1 = FMath::Sin(Slerp * Omega) * InvSin;
//	}
//	else
//	{
//		// Use linear interpolation.
//		Scale0 = T(1.0f) - Slerp;
//		Scale1 = Slerp;
//	}
//
//	// In keeping with our flipped Cosom:
//	Scale1 = FMath::FloatSelect(RawCosom, Scale1, -Scale1);
//
//	TQuat<T> Result;
//
//	Result.X = Scale0 * Quat1.X + Scale1 * Quat2.X;
//	Result.Y = Scale0 * Quat1.Y + Scale1 * Quat2.Y;
//	Result.Z = Scale0 * Quat1.Z + Scale1 * Quat2.Z;
//	Result.W = Scale0 * Quat1.W + Scale1 * Quat2.W;
//
//	return Result;
//}

float4 Slerp(float4 q1, float4 q2, float t)
{
    q1 = normalize(q1);
    q2 = normalize(q2);
    
    float originAngle = q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
    
    float angle = originAngle >= 0.0f ? originAngle : (-1 * originAngle);
    
    float weight1, weight2;
    
    if (angle < (0.9f))
    {
        const float omega = acos(angle);
        const float invSin = 1.0f / sin(omega);
        
        weight1 = sin(1.0f - t) * omega * invSin;
        weight2 = sin(t * omega) * invSin;
    }
    else
    {
        weight1 = 1.0f - t;
        weight2 = t;
    }
    
    weight2 = originAngle >= 0.0f ? weight2 : (-1 * weight2);
    
    float4 result;
    
    result.x = weight1 * q1.x + weight2 * q2.x;
    result.y = weight1 * q1.y + weight2 * q2.y;
    result.z = weight1 * q1.z + weight2 * q2.z;
    result.w = weight1 * q1.w + weight2 * q2.w;
    
    result = normalize(result);
    
    return result;
}

float4 slerp(float4 q1, float4 q2, float t)
{
    q1 = normalize(q1);
    q2 = normalize(q2);
    
    float dotProduct = dot(q1, q2);
    
    if (dotProduct <= -0.9f)
    {
        return normalize(lerp(q1, -q2, t));
    }
    else if (abs(dotProduct) < 0.0024f)
    {
        float4 axis = float4(normalize(cross(q1.xyz, float3(1, 0, 0))), 0);
        
        float angle = 3.14159265358979323846f * t;
        
        float4 result = normalize(q1 * cos(angle / 2) + axis * sin(angle / 2));
        
        return result;
    }
    
    float theta = acos(dotProduct);
    
    if (theta < 0.0001f || abs(theta - 3.14159265358979323846f) < 0.0001f)
    {
        return lerp(q1, q2, t);
    }
    else
    {
        float weight1 = sin((1.0 - t) * theta) / sin(theta);
        float weight2 = sin(t * theta) / sin(theta);

        float sum = weight1 + weight2;
        
        return normalize(q1 * weight1 + q2 * weight2);
    }
}

float4x4 IdentityMatrix()
{
    return float4x4(
        float4(1.0f, 0.0f, 0.0f, 0.0f),
        float4(0.0f, 1.0f, 0.0f, 0.0f),
        float4(0.0f, 0.0f, 1.0f, 0.0f),
        float4(0.0f, 0.0f, 0.0f, 1.0f)
    );
}

matrix SkinWorld(float4 indices, float4 weights)
{
    matrix transform = 0;
    matrix animMatrix;
    
    float3 curS, nextS, curT, nextT;
    float4 curR, nextR;
    
    float3 lerpS, lerpT;
    float4 lerpR;
    
    float4 cur1, cur2, cur3, cur4;
    
    [unroll]
    for (int i = 0; i < 4; i++)
    {
        curS = transformMap.Load(int4(indices[i] * 3 + 0, motion.cur.curFrame, motion.cur.clipIndex, 0)).xyz;
        curR = transformMap.Load(int4(indices[i] * 3 + 1, motion.cur.curFrame, motion.cur.clipIndex, 0));
        curT = transformMap.Load(int4(indices[i] * 3 + 2, motion.cur.curFrame, motion.cur.clipIndex, 0)).xyz;
        
        nextS = transformMap.Load(int4(indices[i] * 3 + 0, motion.cur.nextFrame, motion.cur.clipIndex, 0)).xyz;
        nextR = transformMap.Load(int4(indices[i] * 3 + 1, motion.cur.nextFrame, motion.cur.clipIndex, 0));
        nextT = transformMap.Load(int4(indices[i] * 3 + 2, motion.cur.nextFrame, motion.cur.clipIndex, 0)).xyz;
        
        lerpS = lerp(curS, nextS, motion.cur.time);
        lerpR = Slerp(curR, nextR, motion.cur.time);
        lerpT = lerp(curT, nextT, motion.cur.time);
    
        [flatten]
        if (motion.next.clipIndex > -1)
        {
            curS = transformMap.Load(int4(indices[i] * 3 + 0, motion.next.curFrame, motion.next.clipIndex, 0)).xyz;
            curR = transformMap.Load(int4(indices[i] * 3 + 1, motion.next.curFrame, motion.next.clipIndex, 0));
            curT = transformMap.Load(int4(indices[i] * 3 + 2, motion.next.curFrame, motion.next.clipIndex, 0)).xyz;
        
            nextS = transformMap.Load(int4(indices[i] * 3 + 0, motion.next.nextFrame, motion.next.clipIndex, 0)).xyz;
            nextR = transformMap.Load(int4(indices[i] * 3 + 1, motion.next.nextFrame, motion.next.clipIndex, 0));
            nextT = transformMap.Load(int4(indices[i] * 3 + 2, motion.next.nextFrame, motion.next.clipIndex, 0)).xyz;
            
            float3 nextLerpS = lerp(curS, nextS, motion.next.time);
            float4 nextLerpR = Slerp(curR, nextR, motion.next.time);
            float3 nextLerpT = lerp(curT, nextT, motion.next.time);
            
            lerpS = lerp(lerpS, nextLerpS, motion.tweenTime);
            lerpR = Slerp(lerpR, nextLerpR, motion.tweenTime);
            lerpT = lerp(lerpT, nextLerpT, motion.tweenTime);
        }
        
        animMatrix = CombinedTransformMatrix(lerpT, lerpR, lerpS);
        animMatrix = TransposeMatrix(animMatrix);
        
        transform += mul(weights[i], animMatrix);
    }
    
    return transform;
}

cbuffer FrameInstancingBuffer : register(b4)
{
    Motion instanceMotions[MAX_INSTANCE];
}

matrix SkinWorld(uint instanceIndex, float4 indices, float4 weights)
{
    matrix transform = 0;
    matrix curAnim, nextAnim;
    matrix cur, next;
    
    float4 c0, c1, c2, c3;
    float4 n0, n1, n2, n3;
    
    Motion motion = instanceMotions[instanceIndex];
        
    [unroll]
    for (int i = 0; i < 4; i++)
    {
        c0 = transformMap.Load(int4(indices[i] * 4 + 0, motion.cur.curFrame, motion.cur.clipIndex, 0));
        c1 = transformMap.Load(int4(indices[i] * 4 + 1, motion.cur.curFrame, motion.cur.clipIndex, 0));
        c2 = transformMap.Load(int4(indices[i] * 4 + 2, motion.cur.curFrame, motion.cur.clipIndex, 0));
        c3 = transformMap.Load(int4(indices[i] * 4 + 3, motion.cur.curFrame, motion.cur.clipIndex, 0));

        cur = matrix(c0, c1, c2, c3);
        
        n0 = transformMap.Load(int4(indices[i] * 4 + 0, motion.cur.nextFrame, motion.cur.clipIndex, 0));
        n1 = transformMap.Load(int4(indices[i] * 4 + 1, motion.cur.nextFrame, motion.cur.clipIndex, 0));
        n2 = transformMap.Load(int4(indices[i] * 4 + 2, motion.cur.nextFrame, motion.cur.clipIndex, 0));
        n3 = transformMap.Load(int4(indices[i] * 4 + 3, motion.cur.nextFrame, motion.cur.clipIndex, 0));

        next = matrix(n0, n1, n2, n3);
        
        curAnim = lerp(cur, next, instanceMotions[instanceIndex].cur.time);
        
        [flatten]
        if (motion.next.clipIndex > -1)
        {
            c0 = transformMap.Load(int4(indices[i] * 4 + 0, motion.next.curFrame, motion.next.clipIndex, 0));
            c1 = transformMap.Load(int4(indices[i] * 4 + 1, motion.next.curFrame, motion.next.clipIndex, 0));
            c2 = transformMap.Load(int4(indices[i] * 4 + 2, motion.next.curFrame, motion.next.clipIndex, 0));
            c3 = transformMap.Load(int4(indices[i] * 4 + 3, motion.next.curFrame, motion.next.clipIndex, 0));
        
            cur = matrix(c0, c1, c2, c3);
        
            n0 = transformMap.Load(int4(indices[i] * 4 + 0, motion.next.nextFrame, motion.next.clipIndex, 0));
            n1 = transformMap.Load(int4(indices[i] * 4 + 1, motion.next.nextFrame, motion.next.clipIndex, 0));
            n2 = transformMap.Load(int4(indices[i] * 4 + 2, motion.next.nextFrame, motion.next.clipIndex, 0));
            n3 = transformMap.Load(int4(indices[i] * 4 + 3, motion.next.nextFrame, motion.next.clipIndex, 0));
        
            next = matrix(n0, n1, n2, n3);
        
            nextAnim = lerp(cur, next, motion.next.time);
            
            curAnim = lerp(curAnim, nextAnim, motion.tweenTime);
        }
        
        transform += mul(weights[i], curAnim);
    }
    
    return transform;
}


struct LightMaterial
{
    float3 normal;
    float4 albedo;
    float4 emissive;
    float4 specularSamp;
    
    float shininess;
    
    float3 viewPos;
    float3 worldPos;
};

struct LightData
{
    float4 color;
    
    float3 direction;
    int type;
    
    float3 position;
    float range;
    
    float inner;
    float outer;
    float length;
    int active;
    
};

#define MAX_LIGHT 10

cbuffer LightBuffer : register(b0)
{
    LightData lights[MAX_LIGHT];
    
    int lightCount;
    float3 ambientLight;
    float3 ambientCeil;
}

struct LightVertexOutput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
    float3 normal : NORMAL;
    float3 viewPos : VIEW_POS;
    float3 worldPos : WORLD_POS;
};

float3 GetNormal(float3 T, float3 B, float3 N, float2 uv)
{
    T = normalize(T);
    B = normalize(B);
    N = normalize(N);
    
    float3 normal = N;
    
    [flatten]
    if (hasNormal)
    {
        float4 normalSamp = normalMap.Sample(samp, uv);
        normal = normalSamp * 2.0f - 1.0f;
        float3x3 TBN = float3x3(T, B, N);
        normal = normalize(mul(normal, TBN));
    }

    return normal;
    
}

LightMaterial GetLightMaterial(LightVertexOutput input)
{
    LightMaterial result;
    
    result.normal = GetNormal(input.tangent, input.binormal, input.normal, input.uv);
    
    [branch]
    if (hasDiffuse)
        result.albedo = diffuseMap.Sample(samp, input.uv);
    else
        result.albedo = float4(1,1,1,1);
    
    [branch]
    if (hasSpecular)
        result.specularSamp = specularMap.Sample(samp, input.uv);
    else
        result.specularSamp = float4(1, 1, 1, 1);
    
    result.viewPos = input.viewPos;
    result.worldPos = input.worldPos;
    
    result.emissive = emissive;
    
    return result;
}

float4 AddDirectionalLight(LightMaterial input, LightData light)
{
    float3 L = normalize(light.direction);
    
    float diffuseIntencity = saturate(dot(input.normal, -L));
    
    float4 diffuse = light.color * diffuseColor * diffuseIntencity;
    
    float3 viewDir = normalize(input.worldPos - input.viewPos);
    float3 halfWay = normalize(viewDir + L);
    float specular = saturate(dot(input.normal, -halfWay));
    
    diffuse += light.color * pow(specular, shininess) * input.specularSamp * specularColor;
    
    return diffuse * input.albedo;
}

float4 AddPointLight(LightMaterial input, LightData light)
{
    float3 lightDir = input.worldPos - light.position;
    float lightDistance = length(lightDir);
    
    lightDir /= lightDistance;
    
    float diffuseIntencity = dot(input.normal, -lightDir);
    
    float4 diffuse = light.color * diffuseIntencity * diffuseColor;
    
    float3 viewDir = normalize(input.worldPos - input.viewPos);
    float3 halfWay = normalize(viewDir + lightDir);
    float specular = saturate(dot(input.normal, -halfWay));
    
    diffuse += light.color * pow(specular, shininess) * input.specularSamp * specularColor;
    
        
    float distanceToLightNormal = 1.0f - saturate(lightDistance / light.range);
    
    float attention = pow(distanceToLightNormal, 2);
    
    return diffuse * input.albedo * attention;
}

#define DIRECTIONALLIGHT 0
#define POINTLIGHT       1
#define SPOTLIGHT        2
#define CAPSULELIGHT     3

float4 CalculateLights(LightMaterial input)
{
    float4 color = {0,0,0,1};
    
    [unroll(MAX_LIGHT)]
    for (int i = 0; i < lightCount; i++)
    {
        if (!lights[i].active)
            continue;
        
        if (lights[i].type == DIRECTIONALLIGHT)
            color += AddDirectionalLight(input, lights[i]);
        else if (lights[i].type == POINTLIGHT)
            color += AddPointLight(input, lights[i]);
        
    }
    
    return color;
}

float4 CalculateAmbient(LightMaterial input)
{
    float up = input.normal.y * 0.5f + 0.5f;
    
    float4 result = (float4(ambientLight + up * ambientCeil, 1.0f));
    
    return result * input.albedo * ambientColor;
}