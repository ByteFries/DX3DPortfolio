#include "framework.h"
#include "AnimManager.h"
#include <DirectXMath.h>

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

	delete[] _sequenceTransforms;
	delete[] _nodeTransforms;

	delete _frameBuffer;

	if (_animationTexture)
		_animationTexture->Release();

	if (_srv)
		_srv->Release();
}

void AnimManager::AddAnimation(string actorName, string animName, float speed, float direction)
{
	AnimSequence* sequence = new AnimSequence(actorName, animName);

	_sequences.push_back(sequence);
}

void AnimManager::PlaySequence(int index, float speed, float takeTime)
{
	if (_index == index)
		return;

	_index = index;

	FrameBuffer::Frame& curFrame = _frameBuffer->GetCurFrameRef();

	if (curFrame.clipIndex == -1)
	{
		curFrame.clipIndex = index;
		curFrame.speed = speed;
	}

	FrameBuffer::Frame& nextFrame = _frameBuffer->GetNextFrameRef();

	nextFrame.clipIndex = index;
	nextFrame.speed = speed;
	_frameBuffer->SetTakeTime(takeTime);
	_frameBuffer->SetRunningTime(0.0f);
}

void AnimManager::Update()
{
	if (!CanUse())
		return;

	if (_stop)
		return;

	int index = _frameBuffer->GetCurFrame().clipIndex;
	int nextIndex = _frameBuffer->GetNextFrame().clipIndex;

	_sequences[index]->Update(_frameBuffer->GetDataRef());
	
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
	UINT sequenceCount = _sequences.size();

	delete[] _sequenceTransforms;
	delete[] _nodeTransforms;

	_sequenceTransforms = new SequenceTransforms[sequenceCount];
	_nodeTransforms     = new SequenceTransforms[sequenceCount];

	for (UINT i = 0; i < sequenceCount; i++)
	{
		CreateSequenceTransform(i);
	}

	UINT pageSize = MAX_BONE * sizeof(XMMATRIX) * MAX_FRAME_KEY;

	void* ptr = VirtualAlloc(nullptr, pageSize * sequenceCount, MEM_RESERVE, PAGE_READWRITE);

	for (UINT i = 0; i < sequenceCount; i++)
	{
		UINT start = i * pageSize;

		for (UINT j = 0; j < MAX_FRAME_KEY; j++)
		{
			void* tmp = (BYTE*)ptr + MAX_BONE * j * sizeof(XMMATRIX) + start;

	    	VirtualAlloc(tmp, MAX_BONE * sizeof(XMMATRIX), MEM_COMMIT, PAGE_READWRITE);

			memcpy(tmp, _sequenceTransforms[i].transform[j], MAX_BONE * sizeof(XMMATRIX));
		}
	}

	D3D11_SUBRESOURCE_DATA* subResource = new D3D11_SUBRESOURCE_DATA[sequenceCount];

	for (UINT c = 0; c < sequenceCount; c++)
	{
		void* tmp = (BYTE*)ptr + c * pageSize;

		subResource[c].pSysMem = tmp;
		subResource[c].SysMemPitch = MAX_BONE * sizeof(XMMATRIX);
		subResource[c].SysMemSlicePitch = pageSize;
	}

	if (_animationTexture)
		_animationTexture->Release();

	D3D11_TEXTURE2D_DESC desc = {};

	desc.Width = MAX_BONE * 4;
	desc.Height = MAX_FRAME_KEY;
	desc.ArraySize = sequenceCount;
	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.MipLevels = 1;
	desc.SampleDesc.Count = 1;

	DEVICE->CreateTexture2D(&desc, subResource, &_animationTexture);

	delete[] subResource;

	VirtualFree(ptr, 0, MEM_RELEASE);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};

	srvDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
	srvDesc.Texture2DArray.MipLevels = 1;
	srvDesc.Texture2DArray.ArraySize = sequenceCount;

	if (_srv)
		_srv->Release();

	DEVICE->CreateShaderResourceView(_animationTexture, &srvDesc, &_srv);

	_frameBuffer->InitDatas();
}

void AnimManager::CreateSequenceTransform(int index)
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
			

				_sequenceTransforms[index].transform[f][boneIndex] = transform;
			}

			nodeIndex++;
		}
	}
}

void AnimManager::Debug()
{
	//int index = _target->_speed / _sequences.size();

	FrameBuffer::Frame& frame = _frameBuffer->GetCurFrameRef();

	if (ImGui::TreeNode(_sequences[0]->GetName().c_str()))
	{
		ImGui::Checkbox("Stop", &_stop);

		ImGui::DragInt("CurFrame", (int*)&frame.curFrame);
		ImGui::DragInt("NextFrame", (int*)&frame.nextFrame);
		ImGui::DragFloat("Speed", &frame.speed);
	
		ImGui::TreePop();
	}
}

bool AnimManager::CanUse()
{
	if (!_animationTexture ||
		!_sequences.size() ||
		!_target)
	{
		return false;
	}

	return true;
}
