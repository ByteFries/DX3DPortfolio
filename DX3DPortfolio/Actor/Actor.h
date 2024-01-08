#pragma once
class Actor : public Transform
{
public:
	enum State
	{
		IDLE,
		WALK,
		JUMP
	};

	Actor(string name);
	virtual ~Actor();

	void Render();
	void Update();

	void Debug();

	void AddClip(string file);
	void PlayClip(State state, float speed = 1, float takeTime = 0.2f);

	XMMATRIX GetTransformByBone(UINT boneIndex);
	XMMATRIX GetTransformByNode(UINT nodeIndex);

	void CreateAnimationTexture();
protected:
	void CreateClipTransform(UINT index);

	void ReadStaticMesh(string name);
	void ReadSkeletalMesh(string name);

	string _name;
	StaticMesh* _mesh;
	vector<NodeData> _nodes;
	vector<BoneData> _bones;	
	map<string, UINT> _boneMap;


	ClipTransform* _clipTransform;
	ClipTransform* _nodeTransform;
	


	float _takeTime = 0;
	
	vector<ModelClip*> _clips;
	FrameBuffer* _frameBuffer;
	State _state = IDLE;
	ID3D11Texture2D* _animationTexture;
	ID3D11ShaderResourceView* _srv;
};