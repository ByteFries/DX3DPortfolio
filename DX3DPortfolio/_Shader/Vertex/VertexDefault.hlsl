#include "../Header.hlsli"

struct VertexInput
{
    float4 pos : POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float4 indices : INDICES;
    float4 weights : WEIGHTS;
};

LightVertexOutput main(VertexInput input)
{
    LightVertexOutput result;
    
    matrix transform;
    
    [branch]
    if (hasAnimation)
        transform = mul(SkinWorld(input.indices, input.weights), world);
    else
        transform = world;
    
    result.pos = mul(input.pos, transform);
    
    result.worldPos = result.pos;
    result.viewPos = invView._41_42_43;
    
    result.pos = mul(result.pos, view);
    
    result.pos = mul(result.pos, proj);
    
    result.uv = input.uv;
    
    result.normal = normalize(mul(input.normal, (float3x3)world));
    
    result.tangent = normalize(mul(input.tangent, (float3x3) world));
    
    result.binormal = cross(result.normal, result.tangent);
    
	return result;
}