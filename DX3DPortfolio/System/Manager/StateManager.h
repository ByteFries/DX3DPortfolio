#pragma once
class StateManager : public Singleton<StateManager>
{
	friend class Singleton;

	StateManager();
	~StateManager();
public:
	RasterizerState* GetRS() { return _rasterizerState; }
	SamplerState* GetSampler() { return _samplerState; }

	void AlphaBegin();
	void AlphaEnd();

	void DepthEnable();
	void DepthDisable();

	void MainSet();
	void PostSet();
	void SetRS();
private:

	void CreateSamplerState();
	void CreateRasterizerState();
	void CreateBlendState();
	void CreateDepthStencilState();

	RasterizerState* _rasterizerState;
	SamplerState* _samplerState;

	vector<BlendState*> _blendStates;
	vector<DepthStencilState*> _depthStencilStates;
};

