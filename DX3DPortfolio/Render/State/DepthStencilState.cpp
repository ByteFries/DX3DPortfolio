#include "framework.h"
#include "DepthStencilState.h"

DepthStencilState::DepthStencilState()
{
    _dsc.DepthEnable = true;
    _dsc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    _dsc.DepthFunc = D3D11_COMPARISON_LESS;

    _dsc.StencilEnable = true;
    _dsc.StencilReadMask = 0xFF;
    _dsc.StencilWriteMask = 0xFF;

    _dsc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    _dsc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
    _dsc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    _dsc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    _dsc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    _dsc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
    _dsc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    _dsc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    ChangeState();
}

DepthStencilState::~DepthStencilState()
{
    _state->Release();
}

void DepthStencilState::SetState(UINT stencilRef)
{
    DC->OMSetDepthStencilState(_state, stencilRef);
}

void DepthStencilState::ChangeState()
{
    if (_state != nullptr)
        _state->Release();

    DEVICE->CreateDepthStencilState(&_dsc, &_state);
}

void DepthStencilState::DepthEnable(bool value)
{
    _dsc.DepthEnable = value;

    ChangeState();
}

void DepthStencilState::DepthWriteMask(D3D11_DEPTH_WRITE_MASK val)
{
    _dsc.DepthWriteMask = val;

    ChangeState();
}
