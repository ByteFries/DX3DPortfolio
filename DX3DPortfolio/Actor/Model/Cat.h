#pragma once
class Cat :public Creature
{
public:
	Cat();
	~Cat();

	void Update();
	void Render();

	void Physics();

	void Debug();
private:
	void KeyInput();
	void Move();

	float _speed = 10.0f;
	float _jumpPower = 0.0f;
	float _jumpMax = 10.0f;

	float _curRotation = FLT_MAX;
	float _rotAngle = FLT_MAX;
	float _rotTime = 0;

};

