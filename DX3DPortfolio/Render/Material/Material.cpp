#include "framework.h"
#include "Material.h"

Material::Material()
{
	_mBuffer = new MaterialBuffer();
}

Material::~Material()
{
	delete _mBuffer;
}

void Material::SetShader(wstring path)
{
	SetVS(path);
	SetPS(path);
}


void Material::IASetBuffer()
{
	if (_mBuffer->HasTexture())
		_texture->PSSetShaderResources(0);
	else if (_mBuffer->HasDiffuseMap())
		_diffuseMap->PSSetShaderResources(0);
	if (_mBuffer->HasSpecularMap())
		_specularMap->PSSetShaderResources(1);
	if (_mBuffer->HasNormalMap())
		_normalMap->PSSetShaderResources(2);

	_vShader->SetShader();
	_pShader->SetShader();

	_mBuffer->SetPSBuffer(1);
}

void Material::SetTexture(wstring path)
{
	_texture = Texture::Get(path);
	_mBuffer->SetTexture(true);
}

void Material::SetDiffuseMap(wstring path)
{
	_diffuseMap = Texture::Get(path);
	_mBuffer->SetDiffuseMap(true);
}

void Material::SetSpecularMap(wstring path)
{
	_specularMap = Texture::Get(path);
	_mBuffer->SetSpecularMap(true);
}

void Material::SetNormalMap(wstring path)
{
	_normalMap = Texture::Get(path);
	_mBuffer->SetNormalMap(true);
}

void Material::Save(wstring path)
{
}

void Material::Save(string path)
{
	BinaryWriter writer(path);

	writer.WriteData(_name);

	if (_vShader)
		writer.WriteData(_vShader->GetPath());
	else
		writer.WriteData(L"");

	if (_pShader)
		writer.WriteData(_pShader->GetPath());
	else
		writer.WriteData(L"");

	if (_diffuseMap)
		writer.WriteData(_diffuseMap->GetPath());
	else
		writer.WriteData(L"");

	if (_specularMap)
		writer.WriteData(_specularMap->GetPath());
	else
		writer.WriteData(L"");

	if (_normalMap)
		writer.WriteData(_normalMap->GetPath());
	else
		writer.WriteData(L"");

	writer.WriteData(_mBuffer->GetDiffuseColor());
	writer.WriteData(_mBuffer->GetSpecularColor());
	writer.WriteData(_mBuffer->GetAmbientColor());
	writer.WriteData(_mBuffer->GetAmbientColor());
	writer.WriteData(_mBuffer->GetShininess());

}

void Material::Load(wstring path)
{
	string sPath = Utility::ToString(path);
	Load(sPath);
}

void Material::Load(string path)
{
	BinaryReader reader(path);

	if (!reader.Succeeded())
		return;

	_name = reader.ReadString();

	wstring shaderPath = reader.ReadWString();

	if (shaderPath != L"")
		_vShader = Shader::AddVS(shaderPath);

	shaderPath = reader.ReadWString();

	if (shaderPath != L"")
		_pShader = Shader::AddPS(shaderPath);

	shaderPath = reader.ReadWString();

	if (shaderPath != L"")
		SetDiffuseMap(shaderPath);

	shaderPath = reader.ReadWString();

	if (shaderPath != L"")
		SetSpecularMap(shaderPath);

	shaderPath = reader.ReadWString();

	if (shaderPath != L"")
		SetNormalMap(shaderPath);


	XMFLOAT4 color = reader.ReadXMFLOAT4();
	_mBuffer->SetDiffuseColor(color.x, color.y, color.z, color.w);

	color = reader.ReadXMFLOAT4();
	_mBuffer->SetSpecularColor(color.x, color.y, color.z, color.w);

	color = reader.ReadXMFLOAT4();
	_mBuffer->SetAmbientColor(color.x, color.y, color.x, color.w);

	color = reader.ReadXMFLOAT4();
	_mBuffer->SetEmissiveColor(color.x, color.y, color.x, color.w);

	_mBuffer->SetShininess(reader.ReadFloat());
}
