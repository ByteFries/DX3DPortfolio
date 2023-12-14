#pragma once
class MainScene :public Scene
{
public:
	MainScene();
	~MainScene();

	void Update() override;
	void Render() override;
	void PostRender() override;

private:
	Terrain* _terrain;
	ModelExporter* _exporter;
	Cat* _cat;
	Actor* _actor;
	ActorInstancing* _instancing;
};