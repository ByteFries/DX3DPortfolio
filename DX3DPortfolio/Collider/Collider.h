#pragma once

struct Ray
{
	Vector3 origin;
	Vector3 direction;
};

struct Contact
{
	Vector3 hitPoint;
	float distance;
};

class Collider : public Transform
{
public:
	enum ColliderType
	{
		BOX, SPHERE, CAPSULE
	};

	static bool _hidden;

	Collider();
	virtual ~Collider();

	bool Collision(Collider* other);

	virtual bool Collision(IN Ray& ray, OUT Contact* contact = nullptr) abstract;
	virtual bool Collision(class ColliderBox* other) abstract;
	virtual bool Collision(class ColliderSphere* other) abstract;

	virtual void CreateMesh() abstract;

	void Render();

	void SetColor(float r, float g, float b) { _material->GetMaterialBuffer()->SetDiffuseColor( r, g, b, 1.0f ); }

protected:
	Material* _material;
		Mesh*	  _mesh;
    ColliderType  _type;

	vector<Vertex> _vertices;
	  vector<UINT>  _indices;
};

