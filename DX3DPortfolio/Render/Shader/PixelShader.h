#pragma once
class PixelShader : public Shader
{
	friend class Shader;
private:
	PixelShader(wstring key);
	~PixelShader();

public:

	// Shader��(��) ���� ��ӵ�
	virtual void SetShader() override;
};