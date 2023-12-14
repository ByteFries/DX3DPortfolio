#pragma once
class Program
{
public:
	Program();
	~Program();

	void Update();

	void Render();

private:
	void Initialize();

	class MainScene* _scene;

	bool _wireFrame = false;
};

