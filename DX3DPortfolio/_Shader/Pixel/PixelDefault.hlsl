#include "../Header.hlsli"

float4 main(LightVertexOutput input) : SV_TARGET
{   
    LightMaterial material = GetLightMaterial(input);
    
    if (!affectByLight)
        return material.albedo + material.emissive;
    
    float4 finalColor = CalculateLights(material);
    
    float4 ambient = CalculateAmbient(material);
    
    return finalColor + ambient + material.emissive;
}