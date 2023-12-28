#include "../Header.hlsli"

struct VertexOutput
{
    float4 pos : SV_POSITION;
    float4 reflectPos : POSITION;
};

cbuffer ReflectionBuffer : register(b10)
{
    matrix reflectionView;
}

VertexOutput main(Vertex42 input)
{
    VertexOutput result;
    
    result.pos = mul(input.pos, world);
    
    result.reflectPos = mul(result.pos, reflectionView);
    result.reflectPos = mul(result.reflectPos, proj);
    
    result.pos = mul(result.pos, view);
    result.pos = mul(result.pos, proj);
    
    return result;
}