#include "framework.h"
#include "Environment.h"


Environment::Environment()
{
	CreateViewport();
	CreateProjection();

	_sunBuffer = new SunBuffer();
}

Environment::~Environment()
{
	delete _proj;
	delete _sunBuffer;
}

void Environment::SetPerspective()
{
	_proj->SetVSBuffer(2);
	_sunBuffer->SetPSBuffer(0);
}

void Environment::CreateProjection()
{
	_proj = new MatrixBuffer();

	XMMATRIX matrix = XMMatrixPerspectiveFovLH(
		XM_PIDIV4,
		WIN_WIDTH / WIN_HEIGHT,
		0.1f,
		1000.0f
	);

	_proj->SetMatrix(matrix);
}

void Environment::CreateViewport()
{
	D3D11_VIEWPORT viewport;

	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width = WIN_WIDTH;
	viewport.Height = WIN_HEIGHT;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	DC->RSSetViewports(1, &viewport);
}
