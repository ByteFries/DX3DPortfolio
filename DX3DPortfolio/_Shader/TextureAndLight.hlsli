#ifndef LIGHTING_FILE
#define LIGHTING_FILE


Texture2D diffuseMap : register(t0);
Texture2D specularMap : register(t1);
Texture2D normalMap : register(t2);

SamplerState samp : register(s0);

struct VertexTexture
{
    float4 pos : POSITION;
    float2 uv : UV;
};

struct VertexTextureOutput
{
    float4 pos : SV_Position;
    float2 uv : UV;
};

struct VertexTextureNormalTangent
{
    float4 pos : POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
};

struct VertexTextureNormalTangentAlpha
{
    float4 pos : POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float4 alpha : ALPHA;
};

struct LightData
{
    int type;  //directional, point, spot, capsule
    float3 direction;
 
    float4 color;
    
    float3 position;
    float range;
    
    float inner;
    float outer;
    
    float length;
    int active;
};

#define MAX_LIGHT 10

struct LightTextureOutput
{
    float4 pos : SV_Position;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 bitangent : BITANGENT;
    float3 viewDir : VIEWDIR;
    float3 worldPos : WORLD_POS;
};

struct LightColorOutput
{
    float4 pos : SV_Position;
    float3 normal : NORMAL;
    float3 viewDir : VIEWDIR;
    float3 worldPos : WORLD_POS;
};

cbuffer LightBuffer : register(b0)
{
    LightData lights[MAX_LIGHT];
    
    int lightCount;
    float3 ambientLight;
    float3 ambientCeil;
    int padding;
};

cbuffer MaterialBuffer : register(b1)
{
    float4 mDiffuse; //보정 값들
    float4 mSpecular;
    float4 mAmbient;
    float4 mEmissive;
    
    int hasTexture;
    int hasDiffuseMap;
    int hasSpecularMap;
    int hasNormalMap;
    int hasAlphaMap;
    
    float shininess;
    int affectByLight; //광원 효과 적용 유무
    float lightPadding;
}

cbuffer ColorBuffer : register(b2) //b1 = materialBuffer
{
    float4 bufferColor;
}

struct LightMaterial
{
    float4 albedo;
    float4 ambient;
    float4 specularSample;
    float3 normal;
    float3 viewDir;
    float3 worldPos;
};

LightMaterial GetLightMaterial(LightColorOutput input);
LightMaterial GetLightMaterial(LightTextureOutput input);

float4 PointLight(LightMaterial mat, LightData data);
float4 DirectionalLight(LightMaterial mat, LightData data);
float4 SpotLight(LightMaterial mat, LightData data);
float4 CapsuleLight(LightMaterial mat, LightData data);

float3 GetNormal(float3 T, float3 B, float3 N, float2 uv);

/////////////////////////// 메인 ///////////////////////////
float4 CalculateLights(LightMaterial material)
{
    float4 result = float4(0, 0, 0, 0);
    
    [unroll(MAX_LIGHT)]
    for (int i = 0; i < lightCount; i++)
    {
        [flatten]
        if (!lights[i].active)
            continue;
        
        [branch]
        if (lights[i].type == 0)
            result += PointLight(material, lights[i]);
         else if (lights[i].type == 1)
            result += DirectionalLight(material, lights[i]);
        else if (lights[i].type == 2)
            result += SpotLight(material, lights[i]);
        else if (lights[i].type == 3)
           result += CapsuleLight(material, lights[i]);
    }

    return result;
}
/////////////////////////// 광원 계산 ///////////////////////////
float4 PointLight(LightMaterial mat, LightData light)
{
    float3 toLight = mat.worldPos - light.position;
    float distanceToLight = length(toLight);

    toLight /= distanceToLight;
    
    float diffuseIntensity = saturate(dot(mat.normal, -toLight));
    
    float4 finalColor = light.color * diffuseIntensity * mDiffuse;
    
    float3 viewDir = normalize(mat.worldPos - mat.viewDir);
    float3 halfWay = normalize(viewDir + toLight);
    float specular = saturate(dot(mat.normal, -halfWay));
    
    finalColor += light.color * pow(specular, shininess) * mat.specularSample * mSpecular;

    float distanceToLightNormal = 1.0f - saturate(distanceToLight / light.range);

    float attention = pow(distanceToLightNormal, 2);
    
    return finalColor * mat.albedo * attention;
}

float4 DirectionalLight(LightMaterial mat, LightData light)
{
    float3 L = normalize(light.direction);
    float diffuseIntensity = saturate(dot(mat.normal, -L));
    
    float3 reflection = normalize(reflect(L, mat.normal));
    float specularIntensity = saturate(dot(-reflection, mat.viewDir));
    
    float4 specular = saturate(pow(specularIntensity, shininess) * mSpecular);
    
    float4 diffuse = mat.albedo * diffuseIntensity * mDiffuse;
    
    return diffuse + mat.ambient + specular;
}

float4 SpotLight(LightMaterial mat, LightData light)
{
    float3 toLight = mat.worldPos - light.position;
    float distanceToLight = length(toLight);
    
    toLight /= distanceToLight;
    
    float diffuseIntensity = saturate(dot(mat.normal, -toLight));
    
    float4 finalColor = light.color * diffuseIntensity * mDiffuse;
    
    float3 viewDir = normalize(mat.worldPos - mat.viewDir);
    float3 halfWay = normalize(viewDir + toLight);
    float specular = saturate(dot(mat.normal, -halfWay));
    
    finalColor += light.color * pow(specular, shininess) * mat.specularSample * mSpecular;
    float3 dir = normalize(light.direction);
    float cosAngle = dot(dir, toLight);
    
    float outer = cos(radians(light.outer));
    float inner = 1.0f / cos(radians(light.inner));
    
    float conAttention = saturate((cosAngle - outer) * inner);
    
    conAttention = pow(conAttention, 2);
    
    float distanceToLightNormal = 1.0f - saturate(distanceToLight / light.range);
    
    float attention = pow(distanceToLightNormal, 2);

    return finalColor * mat.albedo * attention * conAttention;
}

float4 CapsuleLight(LightMaterial mat, LightData light)
{
    float3 direction = normalize(light.direction);
    float3 start = mat.worldPos - light.position;
    float distanceOnLine = dot(start, direction) / light.length;
    distanceOnLine = saturate(distanceOnLine) * light.length;
    
    float3 pointOnLine = light.position + direction * distanceOnLine;
    
    float3 toLight = mat.worldPos - pointOnLine;
    float distanceToLight = length(toLight);
    
    toLight /= distanceToLight;

    float diffuseIntensity = saturate(dot(mat.normal, -toLight));
    
    float4 finalColor = light.color * diffuseIntensity * mDiffuse;
    
    float3 viewDir = normalize(mat.worldPos - mat.viewDir);
    float3 halfWay = normalize(viewDir + toLight);
    float specular = saturate(dot(mat.normal, -halfWay));
    
    finalColor += light.color * pow(specular, shininess) * mat.specularSample * mSpecular;
    
    float distanceToLightNormal = 1.0f - saturate(distanceToLight / light.range);
    
    float attention = pow(distanceToLightNormal, 2);

    return finalColor * mat.albedo * attention;
}

/////////////////////////// 기타 ///////////////////////////

LightMaterial GetLightMaterial(LightColorOutput input)
{
    LightMaterial material;
    
    material.albedo = bufferColor;
    material.specularSample = float4(1, 1, 1, 1);
    material.ambient = material.albedo * float4(ambientLight, 1) * mAmbient;
    material.normal = input.normal;
    material.viewDir = input.viewDir;
    material.worldPos = input.worldPos;
    
    return material;
}

LightMaterial GetLightMaterial(LightTextureOutput input)
{
    LightMaterial result;
    
    result.normal = GetNormal(input.tangent, input.bitangent, input.normal, input.uv);
    
    [branch]
    if (hasDiffuseMap || hasTexture)
        result.albedo = diffuseMap.Sample(samp, input.uv);
    else
        result.albedo = float4(1, 1, 1, 1);
    
    result.ambient = result.albedo * float4(ambientLight, 1) * mAmbient;
    
    [branch]
    if (hasSpecularMap)
        result.specularSample = specularMap.Sample(samp, input.uv);
    else
        result.specularSample = float4(1, 1, 1, 1);
    
    result.viewDir = input.viewDir;
    result.worldPos = input.worldPos;
    
    return result;
}


float3 GetNormal(float3 T, float3 B, float3 N, float2 uv)
{
    T = normalize(T);
    B = normalize(B);
    N = normalize(N);
    
    float3 normal = N;
    
    [flatten]
    if (hasNormalMap)
    {
        float4 normalSample = normalMap.Sample(samp, uv);
        
        normal = normalSample.xyz * 2.0f - 1.0f;
        
        float3x3 TBN = float3x3(T, B, N);
        
        normal = normalize(mul(TBN, normal));
    }
    
    return normal;
}

#endif