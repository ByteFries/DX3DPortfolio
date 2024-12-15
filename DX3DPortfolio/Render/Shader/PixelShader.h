#pragma once
class PixelShader : public Shader
{
	friend class Shader;

private:
	PixelShader(wstring key);
	~PixelShader();

public:
	virtual void SetShader() override;

private:
	ID3D11PixelShader* _pShader;
};

