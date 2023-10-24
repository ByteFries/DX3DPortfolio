#include "framework.h"
#include "Material.h"

Material::Material()
{
}

Material::~Material()
{
}

void Material::SetShader(wstring path)
{
	SetVS(path);
	SetPS(path);
}

void Material::SetVS(wstring path)
{
	_vShader = Shader::AddVS(path);
}

void Material::SetPS(wstring path)
{
	_pShader = Shader::AddPS(path);
}

void Material::IASetBuffer()
{
	_vShader->SetShader();
	_pShader->SetShader();
	_texture->PSSetShaderResource(0);
}

void Material::SetTexture(wstring path)
{
	_texture = Texture::Get(path);
}
