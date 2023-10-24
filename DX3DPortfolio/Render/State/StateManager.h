#pragma once
class StateManager : public Singleton<StateManager>
{
	friend class Singleton;

	StateManager();
	~StateManager();

public:
	RasterizerState* GetRasterizer() { return _rasterizer; }
	SamplerState* GetSampler() { return _sampler; }

private:

	RasterizerState* _rasterizer;
	SamplerState* _sampler;
};

