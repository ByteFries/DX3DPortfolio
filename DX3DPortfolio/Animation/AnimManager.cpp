#include "framework.h"
#include "AnimManager.h"

AnimManager::AnimManager(SkeletalMesh* mesh)
	:_meshRef(mesh)
{
	_frameBuffer = new FrameBuffer();
}

AnimManager::~AnimManager()
{
	for (auto sequence : _sequences)
		delete sequence;

	_sequences.clear();

	//delete[] _nodeTransform;
	//delete[] _clipTransform;

	delete _frameBuffer;

	if (_srv)
		_srv->Release();

	if (_animationTexture)
		_animationTexture->Release();
}

void AnimManager::AddAnimation(string actorName, string animName, float speed, float direction)
{
	AnimSequence* sequence = new AnimSequence(actorName, animName);

	_sequences.push_back(sequence);
}

void AnimManager::PlaySequence(Actor::State state, float speed, float takeTime)
{
	if (_state == state)
		return;

	_state = state;

	FrameBuffer::Frame& nextFrame = _frameBuffer->GetNextFrameRef();
	nextFrame.clipIndex = state;
	nextFrame.speed = speed;
	_frameBuffer->SetRunningTime(0.0f);
}

void AnimManager::Update(float speed, float direction)
{
	if (!_animationTexture)
		return;

	if (!_sequences.size())
		return;

	_sequences[speed]->Update(_frameBuffer->GetDataRef());

	int nextIndex = _frameBuffer->GetNextFrame().clipIndex;

	if (nextIndex < 0)
		return;

	_sequences[nextIndex]->UpdateNextFrame(_frameBuffer->GetDataRef());

}

void AnimManager::SetSubResources()
{
	_frameBuffer->SetVSBuffer(3);
	DC->VSSetShaderResources(0, 1, &_srv);
}

void AnimManager::CreateTexture()
{
	UINT clipCount = _sequences.size();

	_clipTransforms = new ClipTransform[clipCount];
	_nodeTransforms = new ClipTransform[clipCount];

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
			memcpy(temp, _clipTransforms[c].transform[i], MAX_BONE * sizeof(XMMATRIX));
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

	if (_animationTexture)
		_animationTexture->Release();

	DEVICE->CreateTexture2D(&desc, subResource, &_animationTexture);

	delete[] subResource;
	VirtualFree(ptr, 0, MEM_RELEASE); // 0 ?

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};

	srvDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
	srvDesc.Texture2DArray.MipLevels = 1;
	srvDesc.Texture2DArray.ArraySize = clipCount;

	if (_srv)
		_srv->Release();

	DEVICE->CreateShaderResourceView(_animationTexture, &srvDesc, &_srv);

	_frameBuffer->InitDatas();
}

void AnimManager::CreateClipTransform(int index)
{
	AnimSequence* sequence = _sequences[index];

	for (UINT f = 0; f < sequence->GetFrameCount(); f++)
	{
		UINT nodeIndex = 0;

		for (NodeData node : _meshRef->GetNodes())
		{
			XMMATRIX animWorld;

			vector<KeyTransform> transforms = sequence->GetKeyTransforms(node.name);

			if (transforms.size() > 0)
			{
				XMMATRIX S = XMMatrixScaling(transforms[f].scale.x, transforms[f].scale.y, transforms[f].scale.z);
				XMMATRIX R = XMMatrixRotationQuaternion(XMLoadFloat4(&transforms[f].rotation));
				XMMATRIX T = XMMatrixTranslation(transforms[f].position.x, transforms[f].position.y, transforms[f].position.z);

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
				parentWorld = _nodeTransforms[index].transform[f][parentIndex];

			_nodeTransforms[index].transform[f][nodeIndex] = animWorld * parentWorld;

			vector<BoneData> bones = _meshRef->GetBones();

			if (_meshRef->HasBone(node.name))
			{
				auto map = _meshRef->GetBoneMap();
				UINT boneIndex = map[node.name];

				XMMATRIX transform = bones[boneIndex].offset;

				transform *= _nodeTransforms[index].transform[f][nodeIndex];

				_clipTransforms[index].transform[f][boneIndex] = transform;
			}

			nodeIndex++;
		}
	}
}
