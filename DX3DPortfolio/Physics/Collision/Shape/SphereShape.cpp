#include "framework.h"
#include "SphereShape.h"

SphereShape::SphereShape(float radius, UINT stack, UINT slice)
    :_radius(radius), _stackCount(stack), _sliceCount(slice)
{
    CreateResource();
    CreateFaces();

    _shapeType = SPHERE;
    _surfaceArea = 4.0f * XM_PI * radius * radius;
}

float SphereShape::GetFrontalArea(Vector3 direction)
{
    return XM_PI * _radius * _radius;
}

Vector3 SphereShape::FindFurthestPoint(const Vector3& direction)
{
    return _transform->GetWorldPos() + _radius * direction;
}

void SphereShape::CreateResource()
{
    Vector3 vertex;
    vertex = { 0, _radius, 0 };
    _vertices.push_back(vertex);

    float phiStep = XM_PI / _stackCount;
    float thetaStep = XM_2PI / _sliceCount;

    for (int i = 1; i <= _stackCount - 1; ++i) {
        float phi = i * phiStep;

        for (int j = 0; j <= _sliceCount; ++j) {

            float theta = j * thetaStep;

            vertex = {
                (_radius * sin(phi) * cos(theta)),
                (_radius * cos(phi)),
                (_radius * sin(phi) * sin(theta))
            };

            _vertices.push_back(vertex);
        }
    }

    vertex = { 0, -_radius, 0 };

    _vertices.push_back(vertex);

    for (int i = 1; i <= _stackCount - 1; ++i) {
        for (int j = 0; j < _sliceCount; ++j) {
            int current = (i - 1) * (_sliceCount + 1) + j + 1;
            _indices.push_back(current);
            _indices.push_back(current + 1);
        }
    }

    for (int i = 0; i < _sliceCount; ++i) {
        for (int j = 0; j < _stackCount - 2; ++j) {
            int current = j * (_sliceCount + 1) + i + 1;
            int next = current + (_sliceCount + 1);
            _indices.push_back(current);
            _indices.push_back(next);
        }
    }

    for (int i = 0; i < _sliceCount; ++i) {
        _indices.push_back(0); // ºÏ±Ø Á¤Á¡
        _indices.push_back(i + 1);
    }

    int southPoleIndex = static_cast<int>(_vertices.size()) - 1;
    int baseIndex = southPoleIndex - _sliceCount - 1;

    for (int i = 0; i < _sliceCount; ++i) {
        _indices.push_back(southPoleIndex);
        _indices.push_back(baseIndex + i);
    }

    _mesh->CreateBuffers(_vertices, _indices);

    _worldVertices.resize(_vertices.size());
}

void SphereShape::CreateFaces()
{
    vector<UINT> indices;

    for (int i = 1; i <= _sliceCount; i++) {
        indices.push_back(0);
        indices.push_back(i + 1);
        indices.push_back(i);
    }
    
    float baseIndex = 1;
    float ringVertexCount = _sliceCount + 1;
    
    for (int i = 0; i < _stackCount - 2; i++) {
        for (int j = 0; j < _sliceCount; j++) {
            indices.push_back(baseIndex + i * ringVertexCount + j);
            indices.push_back(baseIndex + i * ringVertexCount + j + 1);
            indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);
    
            indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);
            indices.push_back(baseIndex + i * ringVertexCount + j + 1);
            indices.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);
        }
    }
    float southPoleIndex = _vertices.size() - 1;
    
    baseIndex = southPoleIndex - ringVertexCount;
    
    for (int i = 0; i < _sliceCount; i++) {
        indices.push_back(southPoleIndex);
        indices.push_back(baseIndex + i);
        indices.push_back(baseIndex + i + 1);
    }

    unordered_map<Vector3, unordered_set<Edge, Edge::Hash>, std::hash<Vector3>> faceMap;
    
    for (int i = 0; i < indices.size(); i += 3)
    {
        Vector3 p1 = _vertices[indices[i]];
        Vector3 p2 = _vertices[indices[i + 1]];
        Vector3 p3 = _vertices[indices[i + 2]];
    
        Vector3 v1 = p2 - p1;
        Vector3 v2 = p3 - p1;
    
        Vector3 normal = Vector3::Cross(v1, v2).GetNormalized();
    
        Edge e1{ p1, p2 };
        Edge e2{ p2, p3 };
        Edge e3{ p3, p1 };
    
        faceMap[normal].insert(e1);
        faceMap[normal].insert(e2);
        faceMap[normal].insert(e3);
    }
    
    for (const auto& pair : faceMap)
    {
        vector<Edge> edges(pair.second.begin(), pair.second.end());
        Face face{ pair.first, edges };
        _faces.push_back(face);
    }
}

std::shared_ptr<Shape> SphereShape::GetClone()
{
    std::shared_ptr<Shape> clone = std::make_shared<SphereShape>(_radius, _stackCount, _sliceCount);
    clone->UpdateTransform(_transform->_translation, _transform->_rotation);
    return clone;
}

Matrix3x3 SphereShape::GetInertiaTensor(float mass)
{
    float I = (2.0f / 5.0f) * mass * (_radius * _radius);

    return Matrix3x3(
        I, 0.0f, 0.0f,
        0.0f, I, 0.0f,
        0.0f, 0.0f, I
    );
}
