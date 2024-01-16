#include "framework.h"
#include "MainScene.h"

MainScene::MainScene()
{	
	//ModelExporter* exporter = new ModelExporter("cat");
	//exporter->ExportModel();
	//delete exporter;
	
	_terrain = new Terrain(L"_Texture/HeightMap/HeightMap.png");
	
	_terrain->GetMaterial()->SetDiffuseMap(L"_Texture/IMG/Floor.png");
	_terrain->GetMaterial()->SetNormalMap(L"_Texture/IMG/Floor_normal.png");
	
	_watcher = new Watcher();
	//actor = new Actor("cat");

	_cat = new Cat();
}

MainScene::~MainScene()
{
	delete _terrain;
	delete _watcher;
	delete _cat;
	//delete actor;
}

void MainScene::Update()
{
	_terrain->Update();

	_watcher->Update();

	_cat->Update();
	//actor->Update();
}

void MainScene::PreRender()
{
	_watcher->PreRender();

	_terrain->Render();
}

void MainScene::Render()
{
	MAIN_CAMERA->SetView();
	
	_watcher->Render();
	
	_terrain->Render();

	//actor->Render();

	_cat->Render();
}

void MainScene::PostRender()
{
	_watcher->Debug();
}
