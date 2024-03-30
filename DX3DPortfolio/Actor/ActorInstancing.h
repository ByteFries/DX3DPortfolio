#pragma once
class ActorInstancing :public Actor
{
	struct InstanceData
	{
		XMMATRIX world;
		UINT index;
		UINT animation = 0;
	};


public:
	struct Data
	{
		Transform* transform;
		UINT index;
		UINT animation = 0;
		bool isActive = true;
		bool transformRef = false;
	};

	ActorInstancing(string name);
	~ActorInstancing();

	void Update();
	void Render();

	void Add(Vector3 position, Transform* transform = nullptr);

	void AddAnimation(UINT index);

	vector<Data>& GetDatas() { return _datas; };
protected:
	UINT _drawCount = 0;
	string _name;

	VertexBuffer* _instanceBuffer;

	InstancingFrameBuffer* _frameBuffer;
	vector<InstanceData> _instanceDatas;
	vector<Data> _datas;

	//AnimManager* _animManager;
};