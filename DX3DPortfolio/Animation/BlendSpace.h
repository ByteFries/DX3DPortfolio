#pragma once
class BlendSpace
{
public:
	BlendSpace(string actorName);
	~BlendSpace();

	void Update(int speed, int direction);

	void AddAnimation(string animName, int speed, int direction);

private:
	string _actorName;

	vector<vector<AnimSequence*>> _sequences;

	int _maxSpeed, _minSpeed;
};