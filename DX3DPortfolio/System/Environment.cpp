#include "framework.h"
#include "Environment.h"

Environment::Environment()
{
	CreateViewport();
	CreateProjection();

	_lBuffer = new LightBuffer();
}

Environment::~Environment()
{
	delete _pers;
	delete _lBuffer;
}

void Environment::SetPerspective()
{
	_pers->SetVSBuffer(2);
	_lBuffer->SetPSBuffer(0);
}

void Environment::CreateProjection()
{
	_pers = new MatrixBuffer();

	_persMatrix = XMMatrixPerspectiveFovLH(
		XM_PIDIV4,
		WIN_WIDTH / WIN_HEIGHT,
		0.1f,
		1000.0f
	);

	_pers->SetMatrix(_persMatrix);
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
