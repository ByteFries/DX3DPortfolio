#include "framework.h"
#include "MainScene.h"

MainScene::MainScene()
{
	_terrain = new Terrain(XMFLOAT2(500, 500));

	//_cat = new Cat();
	_instancing = new ActorInstancing("cat_ver13");
	
	_instancing->Add(Vector3(0,0,0));
	_instancing->Add(Vector3(5,0,0));
	_instancing->Add(Vector3(10,0,0));
	//_instancing->AddClip("Idle");
	//_instancing->CreateAnimationTexture();
	
	//MAIN_CAMERA->SetTarget(_instancing);

	_terrain->GetMaterial()->SetDiffuseMap(L"_Texture/IMG/Floor.png");
	_terrain->GetMaterial()->SetNormalMap(L"_Texture/IMG/Floor_normal.png");

	//_actor = new Actor("cat_ver13");
	//_actor->_scale *= 0.01f;

	//_actor->AddClip("Idle");
	//_actor->AddClip("Walk");
	//_actor->AddClip("Jump");
	//_actor->CreateAnimationTexture();
	
}

MainScene::~MainScene()
{
	delete _terrain;
	//delete _cat;
	delete _instancing;
	//delete _actor;
}

void MainScene::Update()
{
	_terrain->Update();
	_instancing->Update();
	//_cat->Update();

	//_cat->Physics();
	//_actor->Update();

	//float height = 0;


	//if (_terrain->GetHeight(_cat->GetWorldPos(), height))
	{
		//if (_cat->_translation.y < height)
			//_cat->_translation.y = height;
	}
}

void MainScene::Render()
{
	_terrain->Render();
	//_actor->Render();
	//_cat->Render();
	_instancing->Render();
}

void MainScene::PostRender()
{
	//_cat->Debug();
	MAIN_CAMERA->Debug();
}
