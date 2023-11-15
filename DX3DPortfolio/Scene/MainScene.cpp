#include "framework.h"
#include "MainScene.h"

MainScene::MainScene()
{
	_terrain = new Terrain();
	_exporter = new ModelExporter("StanfordBunny");
	_exporter->ExportModel();
	_reader = new ModelReader("StanfordBunny");
}

MainScene::~MainScene()
{
	delete _terrain;
	delete _reader;
	delete _exporter;
}

void MainScene::Update()
{
	_terrain->Update();
}

void MainScene::Render()
{
	_terrain->Render();
	_reader->Render();
}

void MainScene::PostRender()
{
}
