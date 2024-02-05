#pragma once
class AnimManager
{
public:
	AnimManager(SkeletalMesh* mesh);
	~AnimManager();

	void AddAnimation(string actorName, string animName, float speed, float direction);
	void PlaySequence(Actor::State state, float speed, float takeTime);

	void Update();
	void SetSubResources();

	void CreateTexture();

	void SetTarget(class Actor* target) { _target = target; }

	void Debug();

	bool CanUse();
private:
	void CreateSequenceSRV(int index);
	
	SkeletalMesh* _meshRef;

	vector<AnimSequence*> _sequences = {};

	SequenceSRT* _sequenceSRTs = nullptr;

	FrameBuffer* _frameBuffer = nullptr;
	ID3D11Texture2D* _animationTexture = nullptr;
	ID3D11ShaderResourceView* _srv = nullptr;

	Actor* _target;

	Actor::State _state = Actor::State::IDLE; // MoveComp 로 이동할 예정

	bool _stop = false;
};

