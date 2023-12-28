#pragma once
class StateManager : public Singleton<StateManager>
{
	friend class Singleton;

	StateManager();
	~StateManager();

public:
	RasterizerState* GetRasterizer() { return _rasterizer; }
	SamplerState* GetSampler() { return _sampler; }

	void AlphaBegin();
	void AlphaEnd();

	void DepthEnable();
	void DepthDisable();
	
	void Set();
	void PostSet();

private:
	void CreateSamplerState();
	void CreateRasterizerState();
	void CreateBlendState();
	void CreateDepthStencilState();

	RasterizerState* _rasterizer;
	SamplerState* _sampler;

};

