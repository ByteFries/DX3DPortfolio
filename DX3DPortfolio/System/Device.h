#pragma once
class Device : public Singleton<Device>
{
	friend class Singleton;
public:
	void Clear();
	void Present();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

private:
	Device();
	~Device();

	void CreateDeviceAndSwapChain();
	void CreateBackBuffer();

	ID3D11Device* _device;
	ID3D11DeviceContext* _deviceContext;

	IDXGISwapChain* _swapChain;
	ID3D11RenderTargetView* _renderTargetView;
	ID3D11DepthStencilView* _depthStencilView;
};

