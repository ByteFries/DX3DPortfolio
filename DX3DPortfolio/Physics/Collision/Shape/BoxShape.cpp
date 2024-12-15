#include "framework.h"
#include "BoxShape.h"

BoxShape::BoxShape(Vector3 size)
    : _size(size)
{
    CreateResource();
	CreateFaces();

	_shapeType = BOX;
	_surfaceArea = 2.0f * (_size.z * _size.x + _size.z * _size.y + _size.x * _size.y);
}

void BoxShape::CreateResource()
{
	Vector3 halfSize = _size * 0.5f;

	_vertices =
	{
		 { -halfSize.x, +halfSize.y, -halfSize.z },
		 { +halfSize.x, +halfSize.y, -halfSize.z },
		 { -halfSize.x, -halfSize.y, -halfSize.z },
		 { +halfSize.x, -halfSize.y, -halfSize.z },
		 { -halfSize.x, +halfSize.y, +halfSize.z },
		 { +halfSize.x, +halfSize.y, +halfSize.z },
		 { -halfSize.x, -halfSize.y, +halfSize.z },
		 { +halfSize.x, -halfSize.y, +halfSize.z },
	};

	

	_indices =
	{
		0, 1,
		1, 3,
		3, 2,
		2, 0,

		4, 5,
		5, 7,
		7, 6,
		6, 4,

		0, 4,
		1, 5,
		3, 7,
		2, 6
	};

	_mesh->CreateBuffers(_vertices, _indices);
	_worldVertices.resize(_vertices.size());
}

void BoxShape::CreateFaces()
{
	vector<UINT> indices = {
		0, 1, 3, 2, // Front (사각형의 4개 정점)
		1, 5, 7, 3, // Right
		0, 4, 5, 1, // Top
		4, 0, 2, 6, // Left
		5, 4, 6, 7, // Back
		2, 3, 7, 6  // Bottom
	};

	unordered_map<Vector3, unordered_set<Edge, Edge::Hash>, hash<Vector3>> faceMap;
	
	for (int i = 0; i < indices.size(); i += 4) {
		Vector3 p1 = _vertices[indices[i]];
		Vector3 p2 = _vertices[indices[i + 1]];
		Vector3 p3 = _vertices[indices[i + 2]];
		Vector3 p4 = _vertices[indices[i + 3]];
	
		Vector3 v1 = p2 - p1;
		Vector3 v2 = p3 - p1;
		Vector3 normal = Vector3::Cross(v1, v2).GetNormalized();
	
		Edge e1{ p1, p2 };
		Edge e2{ p2, p3 };
		Edge e3{ p3, p4 };
		Edge e4{ p4, p1 };
	
		faceMap[normal].insert(e1);
		faceMap[normal].insert(e2);
		faceMap[normal].insert(e3);
		faceMap[normal].insert(e4);
	}
	
	for (const auto& pair : faceMap)
	{
		vector<Edge> edges(pair.second.begin(), pair.second.end());
		Face face{ pair.first, edges };
		_faces.push_back(face);
	}
}

float BoxShape::GetFrontalArea(Vector3 direction)
{
	direction.Normalize();

	float areaX = ProjectArea(_size.y, _size.z, 1, 0, 0, direction);
	float areaY = ProjectArea(_size.x, _size.z, 0, 1, 0, direction);
	float areaZ = ProjectArea(_size.x, _size.y, 0, 0, 1, direction);

	return areaX + areaY + areaZ;
}

float BoxShape::ProjectArea(float width, float height, float nx, float ny, float nz, Vector3 direction)
{
    float dotProduct = std::fabs(nx * direction.x + ny * direction.y + nz * direction.z);
    return width * height * dotProduct;
}

std::shared_ptr<Shape> BoxShape::GetClone()
{
	std::shared_ptr<Shape> clone = std::make_shared<BoxShape>(_size);
	clone->UpdateTransform(_transform->_translation, _transform->_rotation);

	return clone;
}

Matrix3x3 BoxShape::GetInertiaTensor(float mass)
{
	float width = _size.x;
	float height = _size.y;
	float depth = _size.z;

	float Ixx = (1.0f / 12.0f) * mass * (height * height + depth * depth);
	float Iyy = (1.0f / 12.0f) * mass * (width * width + depth * depth);
	float Izz = (1.0f / 12.0f) * mass * (width * width + height * height);

	return Matrix3x3(
		Ixx, 0.0f, 0.0f,   // 첫 번째 행: Ixx, 0, 0
		0.0f, Iyy, 0.0f,   // 두 번째 행: 0, Iyy, 0
		0.0f, 0.0f, Izz    // 세 번째 행: 0, 0, Izz
	);
}
