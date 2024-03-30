#pragma once
class MainScene :public Scene
{
public:
	MainScene();
	~MainScene();

	void Update() override;

	void PreRender() override;
	void Render() override;
	void PostRender() override;

private:
	Terrain* _terrain;
	Cat* _cat;
	Watcher* _watcher;
	Actor* actor;
	SkyBox* _sky;
};