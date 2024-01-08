#include "framework.h"
#include "ColliderSphere.h"

ColliderSphere::ColliderSphere(float radius, float sliceCount, float stackCount)
    :_radius(radius), _sliceCount(sliceCount), _stackCount(stackCount)
{
    _type = SPHERE;
    CreateMesh();
}

ColliderSphere::~ColliderSphere()
{
}

bool ColliderSphere::Collision(IN Ray& ray, OUT Contact* contact)
{
	Vector3 O = ray.origin;
	Vector3 D = ray.direction;

	Vector3 P = this->_worldTranslation;
	Vector3 X = O - P;

	float a = Vector3::Dot(D, D);
	float b = 2 * Vector3::Dot(D, X);
	float c = Vector3::Dot(X, X) - GetRadius() * GetRadius();

	if (b * b - 4 * a * c >= 0)
	{
		if (contact != nullptr)
		{
			float t = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);

			contact->distance = t;
			contact->hitPoint = O + D * t;
		}

		return true;
	}

	return false;
}

bool ColliderSphere::Collision(ColliderBox* other)
{
    return other->Collision(this);
}

bool ColliderSphere::Collision(ColliderSphere* other)
{

    return false;
}

bool ColliderSphere::Block(ColliderBox* other)
{

	return false;
}

bool ColliderSphere::Block(ColliderSphere* other)
{

	return false;
}

void ColliderSphere::CreateMesh()
{
	for (UINT i = 0; i < _stackCount + 1; i++)
	{
		float phi = XM_PI / _stackCount * i;

		for (UINT j = 0; j < _sliceCount + 1; j++)
		{
			float theta = XM_2PI / _sliceCount * j;

			Vertex vertex;

			vertex.pos.x = _radius * sin(phi) * cos(theta);
			vertex.pos.y = _radius * cos(phi);
			vertex.pos.z = _radius * sin(phi) * sin(theta);

			_vertices.push_back(vertex);
		}
	}

	for (UINT j = 0; j < _stackCount; j++)
	{
		for (UINT i = 0; i < _sliceCount; i++)
		{
			_indices.push_back(i + 0 + (_sliceCount + 1) * (j + 0));
			_indices.push_back(i + 1 + (_sliceCount + 1) * (j + 0));

			_indices.push_back(i + 0 + (_sliceCount + 1) * (j + 0));
			_indices.push_back(i + 0 + (_sliceCount + 1) * (j + 1));
		}
	}

	ModelPart* part = new ModelPart();
	part->CreateBuffers(_vertices, _indices);

	Material* material = new Material();
	material->SetShader(L"Collider");
	material->GetMaterialBuffer()->SetDiffuseColor(0.0f, 1.0f, 0.0f, 0.0f);

	part->SetMaterialSlot(0);

	_mesh = new StaticMesh();
	_mesh->AddMesh(part);
	_mesh->AddMaterial(material);
}
