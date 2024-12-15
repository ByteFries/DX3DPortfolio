#pragma once
class RendererInterface
{
public:
	enum RendererType
	{
		PEROBJ,
		INSTANCED
	};

	RendererInterface() {}
	virtual ~RendererInterface() {}
	virtual void Draw(int indexCount) abstract;
	virtual RendererType GetType() abstract;
};