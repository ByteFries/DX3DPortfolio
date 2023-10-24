#pragma once
class TextureCube :public Transform
{
	enum Faces
	{
		FRONT,
		LEFT,
		RIGHT,
		BACKWARD,
		TOP,
		DOWN
	};

public:
	TextureCube(XMFLOAT2 size);
	~TextureCube();

	void Render();
	void Update();

private:
	void CreateQuads();

	vector<Quad*> _quads;


	XMFLOAT2 _size;
};

