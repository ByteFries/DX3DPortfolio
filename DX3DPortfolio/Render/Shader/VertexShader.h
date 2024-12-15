#pragma once
class VertexShader : public Shader
{
	friend class Shader;

private:
	VertexShader(wstring key);
	~VertexShader();

	void CreateInputLayout();

public:
	virtual void SetShader() override;
private:
	ID3D11InputLayout* _inputLayout;
	ID3D11VertexShader* _vShader;
	ID3D11ShaderReflection* _reflection;
};

