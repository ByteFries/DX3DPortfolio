#include "framework.h"
#include "StateManager.h"

StateManager::StateManager()
{
	_rasterizer = new RasterizerState();
	_sampler = new SamplerState();
}

StateManager::~StateManager()
{
	delete _rasterizer;
	delete _sampler;
}

void StateManager::AlphaBegin()
{
}

void StateManager::AlphaEnd()
{
}

void StateManager::DepthEnable()
{
}

void StateManager::DepthDisable()
{
}

void StateManager::Set()
{
}

void StateManager::PostSet()
{
}

void StateManager::CreateSamplerState()
{
}

void StateManager::CreateRasterizerState()
{
}

void StateManager::CreateBlendState()
{
}

void StateManager::CreateDepthStencilState()
{
}
