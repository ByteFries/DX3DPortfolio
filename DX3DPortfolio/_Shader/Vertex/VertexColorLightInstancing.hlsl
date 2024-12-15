#include "../Shared.hlsli"
#include "../TextureAndLight.hlsli"

struct VertexInput
{
    float4 pos : POSITION;
    float3 normal : NORMAL;
	
    matrix instanceWorld : INSTANCE_TRANSFORM;
};

LightColorOutput main(VertexInput input)
{
    LightColorOutput result;
	
    result.pos = mul(input.pos, input.instanceWorld);
    
    result.worldPos = result.pos;
    
    float3 cameraPos = invView._41_42_43;
    
    result.viewDir = normalize(result.pos.xyz - cameraPos);
    
    result.pos = mul(result.pos, view);
    
    result.pos = mul(result.pos, projection);
    
    result.normal = normalize(mul(input.normal, (float3x3) world));
    
	return result;
}