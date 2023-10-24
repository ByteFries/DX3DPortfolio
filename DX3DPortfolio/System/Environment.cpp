#include "framework.h"
#include "Environment.h"


Environment::Environment()
{
	CreateViewport();
	CreateProjection();
}

Environment::~Environment()
{
	delete _proj;
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

	_proj->SetVSBuffer(2);
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
