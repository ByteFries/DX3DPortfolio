#include "framework.h"
#include "ColorSphere.h"

ColorSphere::ColorSphere(float rad, UINT stack, UINT slice, XMFLOAT4 color)
	:_radius(rad), _stackCount(stack), _sliceCount(slice)
{
	CreateResource();
	SetColor(color);
}

void ColorSphere::CreateResource()
{
    vector<VertexLight> vertices;

    VertexLight vertex;
    vertex.pos = {0, _radius, 0};
    vertex.normal = {0, 1, 0};
    vertices.push_back(vertex);

    float phiStep = XM_PI / _stackCount;
    float thetaStep = XM_2PI / _sliceCount;

    for (int i = 1; i < _stackCount; ++i) {
        float phi = i * phiStep;

        for (int j = 0; j <= _sliceCount; ++j) {

            float theta = j * thetaStep;

            vertex.pos = {
                (_radius * sin(phi) * cos(theta)),
                (_radius * cos(phi)),
                (_radius * sin(phi) * sin(theta))
            };
            vertex.normal = vertex.pos.GetNormalized();
            vertices.push_back(vertex);
        }
    }

    vertex.pos = { 0, -_radius, 0 };
    vertex.normal = { 0, -1, 0 };

    vertices.push_back(vertex);

    vector<UINT> indices;

    for (int i = 0; i < _sliceCount; ++i) {
        indices.push_back(0);
        indices.push_back((i + 1) % _sliceCount + 1);
        indices.push_back(i + 1);
    }

    for (int i = 0; i < _stackCount - 2; ++i)
    {
        for (int j = 0; j < _sliceCount; ++j)
        {
            int current = i * (_sliceCount + 1) + j + 1;
            int next = current + _sliceCount + 1;
    
            indices.push_back(current);
            indices.push_back(current + 1);
            indices.push_back(next);
    
            indices.push_back(current + 1);
            indices.push_back(next + 1);
            indices.push_back(next);
        }
    }

    int southPoleIndex = vertices.size() - 1;
    int baseIndex = southPoleIndex - _sliceCount;

    Vector3 pos1 = vertices[baseIndex].pos;
    Vector3 pos2 = vertices[1].pos;

    for (int i = 0; i < _sliceCount; ++i) {
        indices.push_back(baseIndex + i);               
        indices.push_back(baseIndex + ((i + 1) % _sliceCount));
        indices.push_back(southPoleIndex);   
    }

    _mesh->CreateBuffers(vertices, indices);
}