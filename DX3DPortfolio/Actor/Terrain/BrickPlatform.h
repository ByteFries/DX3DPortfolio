#pragma once
class BrickPlatform : public PlatformBase
{
public:
	BrickPlatform(Vector3 size);
	~BrickPlatform();

private:

	void Init() override;

	Vector3 _size;
};

