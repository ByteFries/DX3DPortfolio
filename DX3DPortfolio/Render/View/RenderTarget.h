#pragma once
class RenderTarget
{
public:
	RenderTarget(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);
	~RenderTarget();

	ID3D11RenderTargetView* GetRTV() { return _rtv; }
	ID3D11ShaderResourceView* GetSRV() { return _srv; }
	ID3D11ShaderResourceView*& GetSRVRef() { return _srv; }

	void Set(DepthStencil* depthStencil, XMFLOAT4 clearColor = { 1, 1, 1, 1 });

	static void SetMulti(RenderTarget** targets, UINT count, DepthStencil* depthStencil, XMFLOAT4 clearColor = { 1, 1, 1, 1 });

private:
	void CreateTexture();
	void CreateRTV();
	void CreateSRV();

	UINT _width, _height;

	ID3D11Texture2D* _texture;
	ID3D11RenderTargetView* _rtv;
	ID3D11ShaderResourceView* _srv;
};

