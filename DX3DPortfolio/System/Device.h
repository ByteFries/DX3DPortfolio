#pragma once
class Device :public Singleton<Device>
{
	friend class Singleton;

private:
	Device();
	~Device();

public:
	ID3D11Device* GetDevice() { return _device; }
	ID3D11DeviceContext* GetDC() { return _dc; }
	
	void Clear();
	void Present();
private:
	void CreateDeviceAndSwapChain();
	void CreateBackBuffer();

	ID3D11Device* _device;
	ID3D11DeviceContext* _dc;
	IDXGISwapChain* _swapChain;
	ID3D11RenderTargetView* _renderTargetView;
	ID3D11DepthStencilView* _depthStencilView;
};

