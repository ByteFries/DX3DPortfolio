#include "framework.h"
#include "Shader.h"

unordered_map<wstring, Shader*> Shader::_shaders = {};

Shader::~Shader()
{
	_blob->Release();
}

VertexShader* Shader::AddVS(wstring key)
{
	wstring path = L"_Shader/Vertex/Vertex" + key + L".hlsl";
	
	assert(PathFileExists(path.c_str()));
	
	if (_shaders.count(path) > 0)
		return (VertexShader*)_shaders[path];
	
	_shaders[path] = new VertexShader(path);
	_shaders[path]->_path = key;

	return (VertexShader*)_shaders[path];
}

PixelShader* Shader::AddPS(wstring key)
{
	wstring path = L"_Shader/Pixel/Pixel" + key + L".hlsl";

	assert(PathFileExists(path.c_str()));

	if (_shaders.count(path) > 0)
		return (PixelShader*)_shaders[path];
	
	_shaders[path] = new PixelShader(path);
	_shaders[path]->_path = key;

	return (PixelShader*)_shaders[path];
}

ComputeShader* Shader::AddCS(wstring key)
{
	wstring path = L"_Shader/Compute/Compute" + key + L".hlsl";

	assert(PathFileExists(path.c_str()));

	if (_shaders.count(path) > 0)
		return (ComputeShader*)_shaders[path];

	_shaders[path] = new ComputeShader(path);
	_shaders[path]->_path = key;

	return (ComputeShader*)_shaders[path];
}

void Shader::Clear()
{
	for (pair<wstring, Shader*> pair : _shaders)
		delete pair.second;

	_shaders.clear();
}
