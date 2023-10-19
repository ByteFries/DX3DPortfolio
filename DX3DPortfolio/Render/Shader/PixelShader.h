#pragma once
class PixelShader : public Shader
{
	friend class Shader;
private:
	PixelShader(wstring key);
	~PixelShader();

public:

	// Shader을(를) 통해 상속됨
	virtual void SetShader() override;
};