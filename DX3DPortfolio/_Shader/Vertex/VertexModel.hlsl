#include "../Shared.hlsli"
#include "../TextureAndLight.hlsli"
#include "../Animation.hlsli"

struct VertexInput
{
    float4 pos : POSITION;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 bitangent : BITANGENT;
    float2 uv : UV;
    float4 indices : BLENDINDICES;
    float4 weights : BLENDWEIGHT;
};

LightTextureOutput main(VertexInput input)
{
    LightTextureOutput result;
    
    float4x4 transform;
    
    //[branch]
    //if (hasAnimation)
        //transform = BlendAndSkinAnimation(input.indices, input.weights);
    //else
        transform = world;
    
    result.pos = mul(input.pos, transform);
    
    result.worldPos = result.pos.xyz;
    
    float3 cameraPos = invView._41_42_43;
    
    result.viewDir = normalize(result.pos.xyz - cameraPos);
    
    result.pos = mul(result.pos, view);
    result.pos = mul(result.pos, projection);
    
    result.normal = normalize(mul(input.normal, (float3x3) world));
    result.tangent = normalize(mul(input.tangent, (float3x3) world));
    result.bitangent = normalize(mul(input.bitangent, (float3x3) world));
    
    result.uv = input.uv;
    
    return result;
}