#include "../Shared.hlsli"
#include "../TextureAndLight.hlsli"

VertexTextureOutput main(VertexTexture input)
{
    VertexTextureOutput result;
    result.pos = input.pos;
	
    result.pos = mul(input.pos, world);
    result.pos = mul(result.pos, view);
    result.pos = mul(result.pos, projection);
	
    result.uv = input.uv;
    
	return result;
}