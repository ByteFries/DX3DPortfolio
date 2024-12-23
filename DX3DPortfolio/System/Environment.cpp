#include "framework.h"
#include "Environment.h"

Environment::Environment()
{
	CreateViewport();
	CreateProjection();

}

Environment::~Environment()
{
	delete _persBuffer;
	delete _camBuffer;
}


void Environment::SetEnvrionment()
{
	//_lBuffer->SetPSBuffer(0);
	_persBuffer->SetVSBuffer(2);

	StateManager::Get()->MainSet();
}

void Environment::SetViewport(UINT width, UINT height)
{
	D3D11_VIEWPORT viewPort;
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;
	viewPort.Width = width;
	viewPort.Height = height;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;

	DC->RSSetViewports(1, &viewPort);
}

void Environment::Debug()
{
	if (ImGui::TreeNode("Environment"))
	{

		ImGui::TreePop();
	}
}

void Environment::CreateProjection()
{
	_persBuffer = new MatrixBuffer();

	_persMatrix = XMMatrixPerspectiveFovLH(
		XM_PIDIV2,
		WIN_WIDTH / WIN_HEIGHT,
		0.1f,
		1000.0f
	);

	_persBuffer->SetMatrix(_persMatrix);
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
