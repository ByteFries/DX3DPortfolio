cbuffer SunBuffer : register(b0)
{
    float3 L;
    float padding;
}

cbuffer MaterialBuffer : register(b1)
{
    float4 diffuseColor;
    float4 specularColor;
    float4 ambientColor;
    float4 emissive;
    
    int hasDiffuse;
    int hasSpecular;
    int hasNormal;
    int shininess;
}

struct VertexOutput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
    float3 cameraDir : CAMERA_DIRECTION;
};

SamplerState samp : register(s0);
Texture2D diffuseMap : register(t0);
Texture2D specularMap : register(t1);
Texture2D normalMap : register(t2);

float4 main(VertexOutput input) : SV_TARGET
{
    float3 normal = input.normal;
    
    if (hasNormal)
    {
        float3 T = input.tangent;
        float3 B = input.binormal;
        float3 N = input.normal;
        
        float4 normalSamp = normalMap.Sample(samp, input.uv);
        
        normal = normalSamp * 2 - 1;
        
        float3x3 TBN = float3x3(T, B, N);
        
        normal = normalize(mul(normal, TBN));
        
    }
    
    
    //////diffuse/////
    float diffuseIntencity = dot(normal, L);
    
    float4 albedo = {1,1,1,1};
    
    if (hasDiffuse)
        albedo = diffuseMap.Sample(samp, input.uv);
    
    float diffuse = albedo * diffuseIntencity * diffuseColor;
    //////diffuse/////
    /////specular/////
    float3 reflection = normalize(reflect(L, normal));
    
    float specularIntencity = saturate(dot(-reflection, input.cameraDir));
    
    float4 specularSamp = { 1,1,1,1};
    
    if (hasSpecular)
        specularSamp = specularMap.Sample(samp, input.uv);
    
    float4 specular = pow(specularIntencity, shininess) * specularSamp * specularColor;
    /////specular/////
    //////amibent//////
    float4 ambient = albedo * ambientColor;
    
    //////amibent//////
    return diffuse + specular + ambient;
}