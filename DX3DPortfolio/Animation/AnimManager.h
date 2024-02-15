#pragma once
class AnimManager
{
public:
	AnimManager(SkeletalMesh* mesh);
	~AnimManager();

	void AddAnimation(string actorName, string animName, float speed, float direction);
	void PlaySequence(int index, float speed, float takeTime);

	void Update();
	void SetSubResources();

	void CreateTexture();

	void SetTarget(class Actor* target) { _target = target; }

	void Debug();

	bool CanUse();
private:
	void CreateSequenceTransform(int index);
	
	SkeletalMesh* _meshRef;

	vector<AnimSequence*> _sequences = {};

	SequenceTransforms* _sequenceTransforms = nullptr;
	SequenceTransforms* _nodeTransforms = nullptr;

	FrameBuffer* _frameBuffer = nullptr;
	ID3D11Texture2D* _animationTexture = nullptr;
	ID3D11ShaderResourceView* _srv = nullptr;

	Actor* _target;

	UINT _index = 0; // MoveComp 로 이동할 예정

	bool _stop = false;
};

