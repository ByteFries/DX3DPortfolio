#pragma once
class VertexShader :public Shader
{
	friend class Shader;
private:
	VertexShader(wstring key);
	~VertexShader();

public:

	// Shader��(��) ���� ��ӵ�
	virtual void SetShader() override;

};

