#pragma once
class Shader
{
protected:
	virtual ~Shader();

public:
	static class VertexShader* AddVS(wstring key);
	static class PixelShader* AddPS(wstring key);

	static void Clear();

	virtual void SetShader() abstract;

	wstring GetPath() { return _path; }

protected:
	static unordered_map<wstring, Shader*> _shaders;

	ID3DBlob* _blob;

	wstring _path;
};

