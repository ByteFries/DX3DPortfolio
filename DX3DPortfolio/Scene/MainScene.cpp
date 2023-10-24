#include "framework.h"
#include "MainScene.h"

MainScene::MainScene()
{
	_terrain = new Terrain();
}

MainScene::~MainScene()
{
	delete _terrain;
}

void MainScene::Update()
{
	_terrain->Update();
}

void MainScene::Render()
{
	_terrain->Render();
}

void MainScene::PostRender()
{
}
