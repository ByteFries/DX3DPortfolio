#include "../Header.hlsli"

struct VertexInput
{
    float4 pos : POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float4 indices : INDICES;
    float4 weights : WEIGHTS;
    
    matrix transform : INSTANCE_TRANSFORM;
    uint index : INSTANCE_INDEX;
    uint animation : INSTANCE_ANIMATION;
};

LightVertexOutput main(VertexInput input)
{
    LightVertexOutput result;
    
    matrix transform;
    
    if (input.animation)
        transform = mul(SkinWorld(input.indices, input.weights), input.transform);
    else
        transform = input.transform;
    
    result.pos = mul(input.pos, transform);
    
    result.worldPos = result.pos;
    result.viewPos = invView._41_42_43;
    
    result.pos = mul(result.pos, view);
    
    
    result.pos = mul(result.pos, proj);
    
    result.uv = input.uv;
    
    result.normal = normalize(mul(input.normal, (float3x3)input.transform));
    
    result.tangent = normalize(mul(input.tangent, (float3x3)input.transform));
    
    result.binormal = cross(result.normal, result.tangent);
    
    return result;
}