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

	void AddClip(string animName, float speed = 0.0f, float dirction = 0.0f);
	void PlayClip(State state, float speed = 1, float takeTime = 0.2f);

	void SetMesh(StaticMesh* mesh) { _mesh = mesh; }

protected:

	string _name;
	StaticMesh* _mesh;

	vector<NodeData> _nodes;
	vector<BoneData> _bones;
	map<string, UINT> _boneMap;

	class AnimManager* _animManager;
};