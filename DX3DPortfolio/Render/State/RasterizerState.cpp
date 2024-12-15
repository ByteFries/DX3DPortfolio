#include "framework.h"
#include "RasterizerState.h"

RasterizerState::RasterizerState()
{
	_dsc.FillMode = D3D11_FILL_SOLID;
	_dsc.CullMode = D3D11_CULL_BACK;

	DEVICE->CreateRasterizerState(&_dsc, &_rasterizerState);
}

RasterizerState::~RasterizerState()
{
	_rasterizerState->Release();
}

void RasterizerState::SetState()
{
	DC->RSSetState(_rasterizerState);
}

void RasterizerState::ChangeState(D3D11_FILL_MODE mod)
{
	if (_dsc.FillMode == mod)
		return;

	_dsc.FillMode = mod;

	if (_rasterizerState != nullptr)
		_rasterizerState->Release();

	DEVICE->CreateRasterizerState(&_dsc, &_rasterizerState);
	DC->RSSetState(_rasterizerState);
}

void RasterizerState::FrontCounterClockWise(bool val)
{
	_dsc.FrontCounterClockwise = val;

	if (_rasterizerState != nullptr)
		_rasterizerState->Release();

	DEVICE->CreateRasterizerState(&_dsc, &_rasterizerState);
}
