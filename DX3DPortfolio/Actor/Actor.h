#pragma once
class Actor : public Transform
{
public:
	enum State
	{
		IDLE,
		WALK,
		JUMP,
		NONE
	};

	Actor(string name);
	virtual ~Actor();

	virtual void Render();
	virtual void Update();

	void Debug();


	void SetMesh(Mesh* mesh) { _mesh = mesh; }

protected:
	string _name;
	Mesh* _mesh;

	Collider* _collider;

	vector<NodeData> _nodes;
	vector<BoneData> _bones;
	map<string, UINT> _boneMap;

};