#include "framework.h"
#include "SamplerState.h"

SamplerState::SamplerState()
{
	D3D11_SAMPLER_DESC samplerDesc = {};

	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	DEVICE->CreateSamplerState(&samplerDesc, &_samplerState);

	DC->PSSetSamplers(0, 1, &_samplerState);
}

SamplerState::~SamplerState()
{
	_samplerState->Release();
}
