#include "framework.h"
#include "ActorInstancing.h"

ActorInstancing::ActorInstancing(string name)
	:Actor(name),_name(name)
{
	_instanceDatas.resize(MAX_INSTANCE);
	_instanceBuffer = new VertexBuffer(_instanceDatas);
	_mesh = new StaticMesh();
	_mesh->SetShader(L"DefualtInstance");

	_frameBuffer = new InstancingFrameBuffer();
}

ActorInstancing::~ActorInstancing()
{
	delete _instanceBuffer;

	for (Data data : _datas)
	{
		if (!data.transformRef)
			delete data.transform;
	}

	_datas.clear();

	delete _frameBuffer;

	delete _mesh;
}

void ActorInstancing::Update()
{
	_drawCount = 0;

	for (Data data : _datas)
	{
		if (!data.isActive)
			continue;

		data.transform->Update();
		_instanceDatas[_drawCount].world = XMMatrixTranspose(data.transform->GetSRT());
		_instanceDatas[_drawCount].animation = data.animation;
		_instanceDatas[_drawCount++].index = data.index;
	}

	_instanceBuffer->UpdateVertices(_instanceDatas.data(), _drawCount * sizeof(InstanceData));
}

void ActorInstancing::Render()
{
	_instanceBuffer->InstancingSetBuffer();

	_frameBuffer->SetVSBuffer(3);
	
	//if (_animManager)
	//{
	//	_animManager->SetSubResources();
	//	_wBuffer->SetAnimation(true);
	//
	//}
	//else
	//	_wBuffer->SetAnimation(false);

	_mesh->RenderInstanced(_drawCount);
}

void ActorInstancing::Add(Vector3 position, Transform* transform)
{
	Data data;

	if (transform)
	{
		data.transform = transform;
		data.transformRef = true;
	}
	else
	{
		data.transform = new Transform();
	}

	data.transform->_translation = position;
	
	data.isActive = true;
	data.index = _datas.size() + 1;
	
	_datas.push_back(data);
}

void ActorInstancing::AddAnimation(UINT index)
{
	_datas[index].animation = 1;
}
