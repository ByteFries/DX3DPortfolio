#pragma once
class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;

private:
	PhysicalObject* p1;
	vector<PhysicalObject*> v;
	
	// Scene을(를) 통해 상속됨
	void Debug() override;
};

