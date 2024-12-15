#pragma once
class GridScene : public Scene
{
public:
	GridScene();
	~GridScene();

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;

private:
	void CreateVertices();

	int _width = 1000;
	int _height = 1000;
	int _interval = 1;

	VertexBuffer* _vBuffer;
	WorldBuffer* _wBuffer;
	vector<VertexColor> _vertices;
	Material* _material;



	// Scene을(를) 통해 상속됨
	void Debug() override;

};

