#pragma once
class VertexShader :public Shader
{
	friend class Shader;
private:
	VertexShader(wstring key);
	~VertexShader();

public:

	// Shader을(를) 통해 상속됨
	virtual void SetShader() override;

};

