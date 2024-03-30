#include "../header.hlsli"

struct VertexOutput
{
    float4 pos : SV_POSITION;
    float3 originPos : POSITION;
};

struct VertexInputput
{
    float4 pos : POSITION;
    float2 uv : UV;
};

VertexOutput main(VertexInputput input)
{
    VertexOutput output;
    
    output.originPos = input.pos.xyz;
    
    output.pos.xyz = mul(input.pos.xyz, (float3x3) view);
    output.pos.w = 1.0f;
    output.pos = mul(output.pos, proj);
    
    return output;
}