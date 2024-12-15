#include "../TextureAndLight.hlsli"

float4 main(LightTextureOutput input) : SV_TARGET
{
    
    if (!affectByLight)
        return diffuseMap.Sample(samp, input.uv);
    LightMaterial mat = GetLightMaterial(input);
    return CalculateLights(mat);
}