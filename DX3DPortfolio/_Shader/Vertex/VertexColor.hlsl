#include "../Shared.hlsli"

struct VertexInput
{
    float4 pos : POSITION;
};

struct VertexOutput
{
    float4 pos : SV_Position;
};

VertexOutput main(VertexInput input)
{
    VertexOutput result;
    result.pos = mul(input.pos, world);
    result.pos = mul(result.pos, view);
    result.pos = mul(result.pos, projection);
    
    return result;
}