#include "../TextureAndLight.hlsli"

float4 main(VertexTextureOutput input) : SV_TARGET
{
    return diffuseMap.Sample(samp, input.uv);
}