#include "../Header.hlsli"

struct VertexOutput
{
	float4 pos : SV_POSITION;
    float4 reflectPos : POSITION;
};

Texture2D reflectionMap : register(t10);

float4 main(VertexOutput input) : SV_TARGET
{
    float2 uv;
    
    uv.x = +input.reflectPos.x / input.reflectPos.w * 0.5f + 0.5f;
    uv.y = -input.reflectPos.y / input.reflectPos.w * 0.5f + 0.5f;
    
    return reflectionMap.Sample(samp, uv);
}