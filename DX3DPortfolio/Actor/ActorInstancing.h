#pragma once
class ActorInstancing :public Actor
{

public:
	ActorInstancing(string name);
	~ActorInstancing();

	void Update();
	void Render();

	void Add(Vector3 position);

	void AddAnimation(UINT index);
protected:
	UINT _drawCount = 0;
	string _name;

	VertexBuffer* _instanceBuffer;

	struct InstanceData
	{
		XMMATRIX world;
		UINT index;
		UINT animation = 0;
	};
	
	struct Data
	{
		Transform* transform;
		UINT index;
		UINT animation = 0;
		bool isActive = true;
	};
	
	InstancingFrameBuffer* _frameBuffer;
	vector<InstanceData> _instanceDatas;
	vector<Data> _datas;
};