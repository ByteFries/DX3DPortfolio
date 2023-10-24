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
