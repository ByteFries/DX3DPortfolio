#include "framework.h"
#include "RasterizerState.h"

RasterizerState::RasterizerState()
{
	_desc.FillMode = D3D11_FILL_SOLID;
	_desc.CullMode = D3D11_CULL_BACK;

	DEVICE->CreateRasterizerState(&_desc, &_rasterizerState);
}

RasterizerState::~RasterizerState()
{
	_rasterizerState->Release();
}

void RasterizerState::SetState()
{
	DC->RSSetState(_rasterizerState);
}

void RasterizerState::ChangeState(D3D11_FILL_MODE mode)
{
	if (_desc.FillMode == mode)
		return;

	_desc.FillMode = mode;

	if (_rasterizerState != nullptr)
		_rasterizerState->Release();

	DEVICE->CreateRasterizerState(&_desc, &_rasterizerState);
	DC->RSSetState(_rasterizerState);
}
