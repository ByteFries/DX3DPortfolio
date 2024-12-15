#include "../Shared.hlsli"
#include "../TextureAndLight.hlsli"

struct VertexInput
{
    float4 pos : POSITION;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float2 uv : UV;
};

LightTextureOutput main(VertexInput input)
{
    LightTextureOutput result;
    
    result.pos = mul(input.pos, world);
    
    result.worldPos = result.pos;
    
    float3 cameraPos = invView._41_42_43;
    
    result.viewDir = normalize(result.pos.xyz - cameraPos);
    
    result.pos = mul(result.pos, view);
    result.pos = mul(result.pos, projection);
    
    result.uv = input.uv;
    
    result.normal = normalize(mul(input.normal, (float3x3)world));
    result.tangent = normalize(mul(input.tangent, (float3x3) world));
    result.bitangent = cross(result.normal, result.tangent);
    
    return result;
}