cbuffer LightBuffer : register(b0)
{
    float3 L;
    float padding;
}

struct VertexOutput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 cameraDir : CAMERA_DIRECTION;
};

SamplerState samp : register(s0);
Texture2D diffuseMap : register(t0);

float4 main(VertexOutput input) : SV_TARGET
{
    float diffuseIntencity = dot(input.normal, L);
    
    float3 reflection = normalize(reflect(L, input.normal));
    
    float specularIntencity = saturate(dot(-reflection, input.cameraDir));
    
    return diffuseMap.Sample(samp, input.uv) * diffuseIntencity + specularIntencity;
}