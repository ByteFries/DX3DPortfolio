#include "framework.h"
#include "TextureCube.h"

TextureCube::TextureCube(XMFLOAT2 size)
	:_size(size)
{
	CreateQuads();
}

TextureCube::~TextureCube()
{
	for (auto q : _quads)
		delete q;

	_quads.clear();
}

void TextureCube::Render()
{
	for (auto q : _quads)
		q->Render();
}

void TextureCube::Update()
{
	Transform::Update();

	for (auto q : _quads)
		q->Update();
}

void TextureCube::CreateQuads()
{
	//FRONT,
	{
		Quad* q = new Quad(_size);
		q->_translation.z = -_size.x * 0.5f;
		q->SetParent(this);
		_quads.push_back(q);
	}
	//LEFT,
	{
		Quad* q = new Quad(_size);
		q->_rotation.y = XM_PIDIV2;
		q->_translation.x = -_size.x * 0.5f;
		q->SetParent(this);
		_quads.push_back(q);
	}
	//RIGHT,
	{
		Quad* q = new Quad(_size);
		q->_rotation.y = -XM_PIDIV2;
		q->_translation.x = _size.x * 0.5f;
		q->SetParent(this);
		_quads.push_back(q);
	}
	//BACKWARD,
	{
		Quad* q = new Quad(_size);
		q->_rotation.y = -XM_PI;
		q->_translation.z = _size.x * 0.5f;
		q->SetParent(this);
		_quads.push_back(q);
	}
	//TOP,
	{
		Quad* q = new Quad(_size);
		q->_rotation.x = XM_PIDIV2;
		q->_translation.y = _size.x * 0.5f;
		q->SetParent(this);
		_quads.push_back(q);
	}
	//DOWN
	{
		Quad* q = new Quad(_size);
		q->_rotation.x = -XM_PIDIV2;
		q->_translation.y = -_size.x * 0.5f;
		q->SetParent(this);
		_quads.push_back(q);
	}

}