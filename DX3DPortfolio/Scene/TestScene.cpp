#include "framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 1; i++)
	{
		Vector3 pos;
		//pos.x = i * 1.5 - 10;
		pos.y = 5;

		Vector3 rot;
		rot.x = rand() % 10 / 10.f;
		rot.y = rand() % 10 / 10.f;
		rot.z = rand() % 10 / 10.f;

		PhysicalObject* obj = PHYSICS->GetBox(10.0f, { 1, 1, 1 });
		obj->SetPos(pos);
		//obj->SetRotation(rot);
		obj->SetBehavior((PhysicsType::LINEAR | PhysicsType::ANGULAR));
		obj->SetCollisionHandling(PhysicsType::BLOCK);
		v.push_back(obj);
	}
	v[0]->GetShape()->SetColor({1,0,0,0});
	//v[1]->GetShape()->SetColor({0,1,0,0});
	//v[2]->GetShape()->SetColor({0,0,1,0});
	PhysicalObject* plane = PHYSICS->GetBox(0.0f, { 40.0f, 4.0f, 40.0f });
	plane->SetCollisionHandling(PhysicsType::BLOCK);
	plane->SetBehavior(PhysicsType::STATIC);
}

TestScene::~TestScene()
{
}

void TestScene::Update()
{
}

void TestScene::PreRender()
{
}

void TestScene::Render()
{
	MAIN_CAM->SetView();
}

void TestScene::PostRender()
{
}

void TestScene::Debug()
{
}
