#include "framework.h"
#include "Actor.h"

Actor::Actor(string name)
	:_name(name)
{
	ReadData();
}

Actor::~Actor()
{
	delete _mesh;

	delete[] _nodeTransform;
	delete[] _clipTransform;

	delete _frameBuffer;

	_srv->Release();
	_animationTexture->Release();
}

void Actor::Render()
{
	_wBuffer->SetVSBuffer(0);

	if (_wBuffer->HasAnimation())
	{
		_frameBuffer->SetVSBuffer(3);
		DC->VSSetShaderResources(0, 1, &_srv);
	}

	_mesh->Render();
}

void Actor::Update()
{
	Transform::Update();

	if (!_clips.size())
		return;

	_clips[_state]->Update(_frameBuffer->GetDataRef());

	if (_frameBuffer->GetNextFrame().clipIndex < 0)
		return;

	float& tweenTime = _frameBuffer->GetTweenTimeRef();
	tweenTime += Time::Delta() / _takeTime;

	ModelClip* clip = _clips[_frameBuffer->GetNextFrame().clipIndex];

	FrameBuffer::Frame& nextFrame = _frameBuffer->GetNextFrameRef();

	if (tweenTime >= 1.0f)
	{
		_frameBuffer->SetCurFrame(_frameBuffer->GetNextFrame());
		_frameBuffer->SetTweenTime(0.0f);

		nextFrame.clipIndex = -1;
		nextFrame.curFrame = 0;
		nextFrame.nextFrame = 1;
		nextFrame.time = 0.0f;
		nextFrame.speed = 1.0f;
		_takeTime = 0.0f;
	}
	else
	{
		nextFrame.time += Time::Delta() * clip->GetTicksPerSec() * nextFrame.speed;

		if (nextFrame.time >= 1.0f)
		{
			++nextFrame.curFrame %= (clip->GetFrameCount());
			nextFrame.nextFrame = (nextFrame.curFrame + 1) % clip->GetFrameCount();
			nextFrame.time = 0.0f;
		}
	}
}

void Actor::Debug()
{
	//for (ModelPart* part : _parts)
	//{
	//	part->GetMaterial()->Debug();
	//}
}

void Actor::AddClip(string file)
{
	ClipData data = {};
	data.savePath = "Actor/Model/Data/" + _name + "/Clip/" + file + ".clip";

	ModelReader::ReadClip(data);

	ModelClip* clip = new ModelClip(data);

	_clips.emplace_back(clip);

	_wBuffer->SetAnimation(true);

	if (_clips.size() == 1)
	{
		_frameBuffer = new FrameBuffer();
		_wBuffer->SetAnimation(true);
	}
}

void Actor::PlayClip(State state, float speed, float takeTime)
{
	if (_state == state)
		return;

	_state = state;

	FrameBuffer::Frame& nextFrame = _frameBuffer->GetNextFrameRef();
	nextFrame.clipIndex = state;
	nextFrame.speed = speed;
	_takeTime = takeTime;
}

XMMATRIX Actor::GetTransformByBone(UINT boneIndex)
{
	return XMMATRIX();
}

XMMATRIX Actor::GetTransformByNode(UINT nodeIndex)
{
	return XMMATRIX();
}

void Actor::CreateClipTransform(UINT index)
{
	ModelClip* clip = _clips[index];

	int frameCount = clip->GetFrameCount();

	for (UINT i = 0; i < frameCount; i++)
	{
		UINT nodeIndex = 0;

		for (NodeData node : _nodes)
		{
			XMMATRIX animWorld;

			KeyFrame* frame = clip->GetKeyFrames(node.name);

			if (frame != nullptr)
			{
				KeyTransform transform = frame->transforms[i];

				XMMATRIX S = XMMatrixScaling(transform.scale.x, transform.scale.y, transform.scale.z);
				XMMATRIX R = XMMatrixRotationQuaternion(XMLoadFloat4(&transform.rotation));
				XMMATRIX T = XMMatrixTranslation(transform.position.x, transform.position.y, transform.position.z);

				animWorld = S * R * T;
			}
			else
			{
				animWorld = XMMatrixIdentity();
			}

			XMMATRIX parentWorld;

			int parentIndex = node.parent;

			if (parentIndex < 0)
				parentWorld = XMMatrixIdentity();
			else
				parentWorld = _nodeTransform[index].transform[i][parentIndex];

			_nodeTransform[index].transform[i][nodeIndex] = animWorld * parentWorld;

			vector<BoneData> bones = _bones;

			if (_boneMap.count(node.name))
			{
				UINT boneIndex = _boneMap[node.name];

				XMMATRIX transform = bones[boneIndex].offset;

				transform *= _nodeTransform[index].transform[i][nodeIndex];

				_clipTransform[index].transform[i][boneIndex] = transform;
			}

			nodeIndex++;
		}
	}
}

void Actor::ReadData()
{
	ModelData data;
	ModelReader::ReadModel(data, _name);
	_mesh = new StaticMesh();
	_mesh->SetMesh(_name);
	_bones = data.bones;
	_nodes = data.nodes;
	_boneMap = data.boneMap;

	_mesh->SetShader(L"Default");
}

void Actor::CreateAnimationTexture()
{
	UINT clipCount = _clips.size();

	_clipTransform = new ClipTransform[clipCount];
	_nodeTransform = new ClipTransform[clipCount];

	for (UINT i = 0; i < clipCount; i++)
	{
		CreateClipTransform(i);
	}

	D3D11_TEXTURE2D_DESC desc = {};

	desc.Width = MAX_BONE * 4;
	desc.Height = MAX_FRAME_KEY;
	desc.ArraySize = clipCount;
	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.MipLevels = 1;
	desc.SampleDesc.Count = 1;

	UINT pageSize = MAX_BONE * sizeof(XMMATRIX) * MAX_FRAME_KEY;

	void* ptr = VirtualAlloc(nullptr, pageSize * clipCount, MEM_RESERVE, PAGE_READWRITE);

	for (UINT c = 0; c < clipCount; c++)
	{
		UINT start = c * pageSize;

		for (UINT i = 0; i < MAX_FRAME_KEY; i++)
		{
			void* temp = (BYTE*)ptr + MAX_BONE * i * sizeof(XMMATRIX) + start;

			VirtualAlloc(temp, MAX_BONE * sizeof(XMMATRIX), MEM_COMMIT, PAGE_READWRITE);
			memcpy(temp, _clipTransform[c].transform[i], MAX_BONE * sizeof(XMMATRIX));
		}
	}

	D3D11_SUBRESOURCE_DATA* subResource = new D3D11_SUBRESOURCE_DATA[clipCount];

	for (UINT c = 0; c < clipCount; c++)
	{
		void* temp = (BYTE*)ptr + c * pageSize;

		subResource[c].pSysMem = temp;
		subResource[c].SysMemPitch = MAX_BONE * sizeof(XMMATRIX);
		subResource[c].SysMemSlicePitch = pageSize;
	}

	DEVICE->CreateTexture2D(&desc, subResource, &_animationTexture);

	delete[] subResource;
	VirtualFree(ptr, 0, MEM_RELEASE); // 0 ?

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};

	srvDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
	srvDesc.Texture2DArray.MipLevels = 1;
	srvDesc.Texture2DArray.ArraySize = clipCount;

	DEVICE->CreateShaderResourceView(_animationTexture, &srvDesc, &_srv);
}
