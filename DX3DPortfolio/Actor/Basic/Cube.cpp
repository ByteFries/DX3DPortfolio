#include "framework.h"
#include "Cube.h"

Cube::Cube()
{
	CreateVertices();
	
	_mesh = new Mesh(_vertices, _indices);
	_material = new Material();
	_material->SetShader(L"Color");
    //_material->SetTexture(L"LighthouseScene.png");
}

Cube::~Cube()
{
	delete  _mesh;
	delete _material;
}

void Cube::Update()
{
	Transform::Update();
}

void Cube::Render()
{
	_wBuffer->SetVSBuffer(0);

	_mesh->IASetBuffer();
	_material->IASetBuffer();

	DC->DrawIndexed(_indices.size(), 0, 0);
}

void Cube::CreateVertices()
{
	Vector3 halfSize = _size * 0.5f;

	VertexTexture v;
    
    v.pos = { -halfSize.x, +halfSize.y, -halfSize.z };
    _vertices.push_back(v);

    v.pos = { +halfSize.x, +halfSize.y, -halfSize.z };
    _vertices.push_back(v);

    v.pos = { -halfSize.x, -halfSize.y, -halfSize.z };
    _vertices.push_back(v);

    v.pos = { +halfSize.x, -halfSize.y, -halfSize.z };
    _vertices.push_back(v);

    v.pos = { -halfSize.x, +halfSize.y, +halfSize.z };
    _vertices.push_back(v);

    v.pos = { +halfSize.x, +halfSize.y, +halfSize.z };
    _vertices.push_back(v);

    v.pos = { -halfSize.x, -halfSize.y, +halfSize.z };
    _vertices.push_back(v);

    v.pos = { +halfSize.x, -halfSize.y, +halfSize.z };
    _vertices.push_back(v);

    _indices =
    {
        //F
        0,1,2,
        2,1,3,
        //R
        1,5,3,
        3,5,7,
        //T
        0,4,1,
        1,4,5,
        //L
        4,0,6,
        6,0,2,
        //Ba
        5,4,7,
        7,4,6,
        //Bo
        2,3,6,
        6,3,7
    };
   
    //v.pos = { -halfSize.x, halfSize.y, -halfSize.z }; // 0
    //_vertices.push_back(v);
    //
    //v.pos = { -halfSize.x, halfSize.y, -halfSize.z }; // 1
    //_vertices.push_back(v);
    //
    //v.pos = { -halfSize.x,-halfSize.y, -halfSize.z }; // 2
    //_vertices.push_back(v);
    //
    //v.pos = { halfSize.x,-halfSize.y, -halfSize.z }; // 3
    //_vertices.push_back(v);
    //
    //v.pos = { halfSize.x, halfSize.y, halfSize.z }; // 4
    //_vertices.push_back(v);
    //
    //v.pos = { -halfSize.x,halfSize.y, halfSize.z }; // 5
    //_vertices.push_back(v);
    //
    //v.pos = { halfSize.x, -halfSize.y, halfSize.z }; // 6
    //_vertices.push_back(v);
    //
    //v.pos = { -halfSize.x, -halfSize.y, halfSize.z }; // 7
    //_vertices.push_back(v);
    //
    //
    //_indices.push_back(0);
    //_indices.push_back(1);
    //_indices.push_back(2);
    //
    //_indices.push_back(2);
    //_indices.push_back(1);
    //_indices.push_back(3);
    //
    //_indices.push_back(1);
    //_indices.push_back(4);
    //_indices.push_back(3);
    //
    //_indices.push_back(3);
    //_indices.push_back(4);
    //_indices.push_back(6);
    //
    //_indices.push_back(5);
    //_indices.push_back(0);
    //_indices.push_back(7);
    //
    //_indices.push_back(7);
    //_indices.push_back(0);
    //_indices.push_back(2);
    //
    //_indices.push_back(4);
    //_indices.push_back(5);
    //_indices.push_back(6);
    //
    //_indices.push_back(6);
    //_indices.push_back(5);
    //_indices.push_back(7);
    //
    //_indices.push_back(5);
    //_indices.push_back(4);
    //_indices.push_back(0);
    //
    //_indices.push_back(0);
    //_indices.push_back(4);
    //_indices.push_back(1);
    //
    //_indices.push_back(2);
    //_indices.push_back(3);
    //_indices.push_back(7);
    //
    //_indices.push_back(7);
    //_indices.push_back(3);
    //_indices.push_back(6);
}
