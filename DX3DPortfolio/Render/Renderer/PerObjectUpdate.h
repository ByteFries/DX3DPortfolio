#pragma once
class RendererBase;
class PerOjbectUpdate : public RendererUpdateComponent
{
public:
	void Update(RendererInterface* renderer) override;
};

