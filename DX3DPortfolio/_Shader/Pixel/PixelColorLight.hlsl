#include "../TextureAndLight.hlsli"

float4 main(LightColorOutput input) : SV_TARGET
{
    LightMaterial mat = GetLightMaterial(input);
    return CalculateLights(mat);
}