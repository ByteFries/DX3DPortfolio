#include "../Header.hlsli"

struct VertexOutput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};

float4 main(VertexOutput input) : SV_TARGET
{
    float4 tex = diffuseMap.Sample(samp, input.uv);
    
    return tex;
}