#include "framework.h"
#include "BrickPlatform.h"

BrickPlatform::BrickPlatform(Vector3 size)
	:_size(size)
{
	Init();
}

BrickPlatform::~BrickPlatform()
{
}

void BrickPlatform::Init()
{
	_render = new TextureCube(_size, L"_Texture/Terrain/floor_brick_tiled.png");
	//_rigidBody = PHYSICS->GetBox(0.0, _size);
	//_rigidBody->SetBehavior(PhysicsType::STATIC);

	_render->GetTransform()->SetParent(_transform);
}
