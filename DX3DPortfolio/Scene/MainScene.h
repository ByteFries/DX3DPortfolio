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
	Cube* _cube;

	MatrixBuffer* view;
	MatrixBuffer* proj;

	XMMATRIX _projectionMatrix;
};

