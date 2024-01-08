#include "framework.h"
#include "RenderTarget.h"

RenderTarget::RenderTarget(UINT width, UINT height)
	:_width(width), _height(height)
{
	CreateTexture();
	CreateRTV();
	CreateSRV();
}

RenderTarget::~RenderTarget()
{
	_texture->Release();
	_rtv->Release();
	_srv->Release();
}

void RenderTarget::Set(DepthStencil* depthStencil, XMFLOAT4 clearColor)
{
	//ID3D11RenderTargetView* nullRTV = nullptr;
	//ID3D11DepthStencilView* nullDSV = nullptr;
	//
	//DC->OMSetRenderTargets(1, &nullRTV, nullDSV);

	DC->OMSetRenderTargets(1, &_rtv, depthStencil->GetDSV());

	DC->ClearRenderTargetView(_rtv, (float*)&clearColor);
	depthStencil->Clear();

	Environment::Get()->SetEnvironment();
	Environment::Get()->SetViewport(_width, _height);
}

void RenderTarget::SetMulti(RenderTarget** targets, UINT count, DepthStencil* depthStencil, XMFLOAT4 clearColor)
{
	vector<ID3D11RenderTargetView*> rtvs;

	for (UINT i = 0; i < count; i++)
	{
		rtvs.push_back(targets[i]->GetRTV());
		DC->ClearRenderTargetView(rtvs.back(), (float*)&clearColor);
	}

	depthStencil->Clear();

	DC->OMSetRenderTargets(count, rtvs.data(), depthStencil->GetDSV());
	Environment::Get()->SetEnvironment();
}

void RenderTarget::CreateTexture()
{
	D3D11_TEXTURE2D_DESC desc;

	desc.Width = _width;
	desc.Height = _height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	DEVICE->CreateTexture2D(&desc, nullptr, &_texture);
}

void RenderTarget::CreateRTV()
{
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};

	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	DEVICE->CreateRenderTargetView(_texture, &rtvDesc, &_rtv);
}

void RenderTarget::CreateSRV()
{
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};

	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2DArray.MipLevels = 1;

	DEVICE->CreateShaderResourceView(_texture, &srvDesc, &_srv);
}
