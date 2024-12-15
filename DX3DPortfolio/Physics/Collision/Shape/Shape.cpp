#include "framework.h"
#include "Shape.h"

Shape::Shape()
{
	_transform = new Transform();
	_mesh = new StaticMesh();

	_vShader = Shader::AddVS(L"Color");
	_pShader = Shader::AddPS(L"Color");
	_cBuffer = new ColorBuffer();
}

Shape::~Shape()
{
	delete _transform;
	delete _cBuffer;
	delete _mesh;
}

void Shape::UpdateWorldVertices()
{
	for (int i = 0; i < _vertices.size(); i++)
	{
		_worldVertices[i] = (_transform->ApplyingToVertex(_vertices[i]));
	}

	_needToUpdate = false;
}

void Shape::UpdateTransform(Vector3 pos, Vector3 eular)
{
	_transform->_translation = pos;
	_transform->_rotation = eular;

	_transform->Update();

	_needToUpdate = true;
}

void Shape::Render()
{
    _transform->SetWorld();

	_vShader->SetShader();
	_pShader->SetShader();

	_cBuffer->SetPSBuffer(0);

	_mesh->IASetBuffer(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	DC->DrawIndexed(_mesh->GetIndexSize(), 0, 0);
}

Vector3 Shape::FindFurthestPoint(const Vector3& direction)
{
	if (_needToUpdate)
		UpdateWorldVertices();

	Vector3 originPos = _transform->GetWorldPos();

	Vector3 maxPoint;
	float maxDistance = -FLT_MAX;
	for (const Vector3& vertex : _worldVertices)
	{
		Vector3 relativeVertex = vertex - originPos;

		float distance = Vector3::Dot(relativeVertex, direction);

		if (distance > maxDistance)
		{
			maxDistance = distance;
			maxPoint = vertex;
		}
	}

	return maxPoint;
}

Vector3 Shape::GetClosestPoint(const Vector3& pos)
{
	float minDistance = FLT_MAX;
	Vector3 closestPoint;

	for (const Vector3& vertex : _worldVertices)
	{
		float distance = (vertex - pos).Length2();

		if (distance < minDistance)
		{
			minDistance = distance;
			closestPoint = vertex;
		}
	}

	//if (minDistance == FLT_MAX)
		//오류처리


	return closestPoint;
}

vector<Vector3> Shape::GetWorldVertices()
{
	if (_needToUpdate)
		UpdateWorldVertices();

	return _worldVertices;
}

vector<Edge> Shape::GetWorldEdges()
{
	if (_needToUpdate)
		UpdateWorldVertices();

	vector<Edge> worldEdge;
	vector<Vector3> vertices = GetWorldVertices();

	for (int i = 0; i < _indices.size(); i += 2)
	{
		int index1 = _indices[i];
		int index2 = _indices[(i + 1) % _indices.size()];

		Edge e{ vertices[index1], vertices[index2]};

		worldEdge.push_back(e);
	}

	return worldEdge;
}

vector<Face> Shape::GetWorldFaces()
{
	if (_needToUpdate)
		UpdateWorldVertices();

	vector<Face> worldFaces;
	worldFaces.resize(_faces.size());

	Quaternion rotation = _transform->GetQuaternion();

	for (int i = 0; i < _faces.size(); ++i)
	{
		worldFaces[i].normal = Quaternion::Rotate(rotation, _faces[i].normal);

		for (int j = 0; j < _faces[i].edges.size(); j++)
		{
			worldFaces[i].edges.resize(_faces[i].edges.size());
			worldFaces[i].edges[j].v1 = _transform->ApplyingToVertex(_faces[i].edges[j].v1);
			worldFaces[i].edges[j].v2 = _transform->ApplyingToVertex(_faces[i].edges[j].v2);
		}
	}

	return worldFaces;
}

AABB Shape::GetAABB()
{
	AABB result;

	result.xEnd[0] = FLT_MAX, result.xEnd[1] = FLT_MIN;
	result.yEnd[0] = FLT_MAX, result.yEnd[1] = FLT_MIN;
	result.zEnd[0] = FLT_MAX, result.zEnd[1] = FLT_MIN;

	vector<Vector3> worldVertices = GetWorldVertices();

	for (const Vector3& vertex : worldVertices)
	{
		if (result.xEnd[0] > vertex.x)
			result.xEnd[0] = vertex.x;
		if (result.xEnd[1] < vertex.x)
			result.xEnd[1] = vertex.x;

		if (result.yEnd[0] > vertex.y)
			result.yEnd[0] = vertex.y;
		if (result.yEnd[1] < vertex.y)
			result.yEnd[1] = vertex.y;

		if (result.zEnd[0] > vertex.z)
			result.zEnd[0] = vertex.z;
		if (result.zEnd[1] < vertex.z)
			result.zEnd[1] = vertex.z;
	}

	return result;
}
