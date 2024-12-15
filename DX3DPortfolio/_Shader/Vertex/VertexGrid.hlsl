#include "../Shared.hlsli"

struct VertexInput
{
    float4 pos : POSITION;
    float4 color : COLOR;
};

struct VertexOutput
{
    float4 pos : SV_Position;
    float4 color : COLOR;
};

VertexOutput main(VertexInput input)
{
    VertexOutput result;
    result.pos = input.pos;
    result.pos = mul(input.pos, world);
    result.pos = mul(result.pos, view);
    result.pos = mul(result.pos, projection);
    
    result.color = input.color;
    
    return result;
}