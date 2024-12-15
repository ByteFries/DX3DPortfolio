#include "../TextureAndLight.hlsli"

float4 main(LightTextureOutput input) : SV_TARGET
{
    LightMaterial mat = GetLightMaterial(input);
    
    return CalculateLights(mat);
}