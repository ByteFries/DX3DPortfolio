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
    float padding1;
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

matrix SkinWorld(float4 indices, float4 weights)
{
    matrix transform = 0;
    matrix curAnim, nextAnim;
    matrix cur, next;
    
    float4 c0, c1, c2, c3;
    float4 n0, n1, n2, n3;
        
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
        
        curAnim = lerp(cur, next, motion.cur.time);
        
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