#include "framework.h"
#include "Material.h"

Material::Material()
{
	_mBuffer = new MaterialBuffer();
	_mBuffer->SetShininess(24);
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

	_mBuffer->SetPSBuffer(1);

	if (_isTexture)
		_texture->PSSetShaderResource(0);

	else if (_mBuffer->HasDiffuseMap())
		_diffuseMap->PSSetShaderResource(0);

	if (_mBuffer->HasSpecularMap())
		_specularMap->PSSetShaderResource(1);

	if (_mBuffer->HasNormalMap())
		_normalMap->PSSetShaderResource(2);
}

void Material::SetTexture(wstring path)
{
	_texture = Texture::Get(path);
	_isTexture = true;
}

void Material::SetDiffuseMap(wstring path)
{
	_diffuseMap = Texture::Get(path);
	_mBuffer->SetDiffuseMap(true);
}

void Material::SetDiffuseMap(Texture* texture)
{
	_diffuseMap = texture;
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

void Material::Save(string path)
{
	BinaryWriter writer(path);

	writer.WriteData(_label);

	if(_vShader)
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

void Material::Load(string path)
{
	BinaryReader reader(path);

	if (!reader.Succeeded())
		return;

	_label = reader.ReadString();

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

void Material::Debug()
{
	char* str = (char*)_label.data();

	ImGui::InputText("Label", str, 128);

	_label = str;

	if (_label[0] == '\0')
		_label = "NULL";

	if (ImGui::BeginMenu(_label.c_str()))
	{
		ImGui::ColorEdit4((_label + " Diffuse").c_str(), (float*)&_mBuffer->GetDiffuseColorRef());
		ImGui::ColorEdit4((_label + " Specular").c_str(), (float*)&_mBuffer->GetSpecularColorRef());
		ImGui::ColorEdit4((_label + " Ambient").c_str(), (float*)&_mBuffer->GetAmbientColorRef());

		ImGui::Checkbox((_label + " HasDiffuseMap").c_str(), (bool*)&_mBuffer->HasDiffuseMapRef());
		ImGui::Checkbox((_label + " HasSpecularMap").c_str(), (bool*)&_mBuffer->HasSpecularMapRef());
		ImGui::Checkbox((_label + " HasNormalMap").c_str(), (bool*)&_mBuffer->HasNormalMapRef());

		ImGui::SliderFloat((_label + " Shininess").c_str(), &_mBuffer->GetShininessRef(), 1.0f, 50.0f);

		ImGui::EndMenu();
	}
}
