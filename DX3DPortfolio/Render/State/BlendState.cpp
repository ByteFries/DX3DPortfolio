#include "framework.h"
#include "BlendState.h"

BlendState::BlendState()
{
    _dsc.AlphaToCoverageEnable = false;
    _dsc.IndependentBlendEnable = false;
    _dsc.RenderTarget[0].BlendEnable = false;
    _dsc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    _dsc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    _dsc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    _dsc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    _dsc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
    _dsc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    _dsc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    ChangeState();
}

BlendState::~BlendState()
{
    _state->Release();
}

void BlendState::SetState()
{
    float blendFactor[] = { 0,0,0,0 };
    DC->OMSetBlendState(_state, blendFactor, 0XFFFFFFFF);
}

void BlendState::ChangeState()
{
    if (_state != nullptr)
        _state->Release();

    DEVICE->CreateBlendState(&_dsc, &_state);
}

void BlendState::Alpha(bool value)
{
    _dsc.RenderTarget[0].BlendEnable = value;

    ChangeState();
}

void BlendState::AlphaToCoverage(bool value)
{
    _dsc.AlphaToCoverageEnable = value;

    ChangeState();
}

void BlendState::Additive()
{
    _dsc.RenderTarget[0].BlendEnable = true;
    _dsc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;

    ChangeState();
}
