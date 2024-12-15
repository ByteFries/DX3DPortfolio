#pragma once

class PerObjectRenderer : public RendererInterface
{
public:
	PerObjectRenderer();
	virtual ~PerObjectRenderer();

	virtual void Draw(int indexCount) override;
	virtual RendererType GetType() override { return PEROBJ; }
protected:
};