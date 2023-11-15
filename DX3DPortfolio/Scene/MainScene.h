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
	ModelReader* _reader;
};