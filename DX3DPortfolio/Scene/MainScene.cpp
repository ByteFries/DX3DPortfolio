#include "framework.h"
#include "MainScene.h"

MainScene::MainScene()
{
	_cube = new Cube();

	_cube->_translation.z += 100;

	view = new MatrixBuffer();
	proj = new MatrixBuffer();

	_projectionMatrix = XMMatrixPerspectiveFovLH(
		XM_PIDIV4,
		WIN_WIDTH / WIN_HEIGHT,
		0.1f,
		1000.0f
	);

	proj->SetMatrix(_projectionMatrix);

	view->SetVSBuffer(1);
	proj->SetVSBuffer(2);
}

MainScene::~MainScene()
{
	delete _cube;
	delete view;
	delete proj;
}

void MainScene::Update()
{
	_cube->Update();
}

void MainScene::Render()
{
	_cube->Render();
}

void MainScene::PostRender()
{
}
