#pragma once
class HatKid : public Actor
{
public:
	HatKid();
	~HatKid();



private:
	SkeletalModel* _model;
	Transform* _trasnform;
};

