#include "../Header.hlsli"

float4 main(LightVertexOutput input) : SV_TARGET
{
    LightMaterial material = GetLightMaterial(input);
    
    float4 finalColor = CalculateLights(material);
    
    float4 ambient = CalculateAmbient(material);
    
    return finalColor + ambient;
}