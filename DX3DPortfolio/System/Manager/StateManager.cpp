#include "framework.h"
#include "StateManager.h"

StateManager::StateManager()
{
	CreateSamplerState();
	CreateRasterizerState();
	CreateBlendState();
	CreateDepthStencilState();
}

StateManager::~StateManager()
{
	delete _rasterizerState;
	delete _samplerState;

	for (BlendState* state : _blendStates)
		delete state;

	_blendStates.clear();

	for (DepthStencilState* state : _depthStencilStates)
		delete state;
	_depthStencilStates.clear();
}

void StateManager::AlphaBegin()
{
	_blendStates[1]->SetState();
}

void StateManager::AlphaEnd()
{
	_blendStates[0]->SetState();
}

void StateManager::DepthEnable()
{
	_depthStencilStates[0]->SetState();
}

void StateManager::DepthDisable()
{
	_depthStencilStates[1]->SetState();
}

void StateManager::MainSet()
{
	AlphaEnd();
	DepthEnable();
}

void StateManager::PostSet()
{
	AlphaBegin();
	DepthDisable();
}

void StateManager::SetRS()
{
	_rasterizerState->SetState();
}

void StateManager::CreateSamplerState()
{
	_samplerState = new SamplerState();
}

void StateManager::CreateRasterizerState()
{
	_rasterizerState = new RasterizerState();
	_rasterizerState->SetState();
}

void StateManager::CreateBlendState()
{
	_blendStates.push_back(new BlendState());
	_blendStates.push_back(new BlendState());
	_blendStates.push_back(new BlendState());
	_blendStates.push_back(new BlendState());

	_blendStates[1]->Alpha(true);
	_blendStates[2]->Additive();
	_blendStates[3]->AlphaToCoverage(true);
}

void StateManager::CreateDepthStencilState()
{
	_depthStencilStates.push_back(new DepthStencilState());
	_depthStencilStates.push_back(new DepthStencilState());
	_depthStencilStates.push_back(new DepthStencilState());

	_depthStencilStates[1]->DepthEnable(false);
	_depthStencilStates[2]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);
}
