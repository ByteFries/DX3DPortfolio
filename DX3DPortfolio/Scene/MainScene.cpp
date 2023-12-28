#include "framework.h"
#include "MainScene.h"

MainScene::MainScene()
{
	_terrain = new Terrain(XMFLOAT2(500, 500));

	_cat = new Cat();
	
	//MAIN_CAMERA->SetTarget(_cat);

	_terrain->GetMaterial()->SetDiffuseMap(L"_Texture/IMG/Floor.png");
	_terrain->GetMaterial()->SetNormalMap(L"_Texture/IMG/Floor_normal.png");
	
	_watcher = new Watcher();
	_watcher->_translation.z = 10.0f;
	_watcher->_translation.y = 10.0f;
}

MainScene::~MainScene()
{
	delete _terrain;
	delete _cat;
	delete _watcher;
	
}

void MainScene::Update()
{
	_terrain->Update();
	//_instancing->Update();
	_cat->Update();
	_watcher->Update();

	//_cat->Physics();
	//_actor->Update();

	//float height = 0;


	//if (_terrain->GetHeight(_cat->GetWorldPos(), height))
	{
		//if (_cat->_translation.y < height)
			//_cat->_translation.y = height;
	}
}

void MainScene::PreRender()
{
	_watcher->PreRender();
	_terrain->Render();
}

void MainScene::Render()
{
	MAIN_CAMERA->SetVSBuffer(1);
	_terrain->Render();
	//_actor->Render();
	//_cat->Render();
	//_instancing->Render();
	_watcher->Render();
	
}

void MainScene::PostRender()
{
	//_cat->Debug();
	MAIN_CAMERA->Debug();
}
