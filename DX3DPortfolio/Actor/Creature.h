#pragma once
class Creature : public Actor
{
public:
	Creature(string name);
	virtual ~Creature();

	void Update() override;
	void Render() override;

	void PlayClip(State state, float speed = 1, float takeTime = 0.2f);

protected:

	class AnimManager* _animManager;

	////// MoveComponent //////
	float _speed = 0.0f;
	float _direction = 0.0f;
	bool _onGround = true;

	bool _isActive = false;

	int _hp;
};