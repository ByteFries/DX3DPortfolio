#include "framework.h"
#include "TextureSphere.h"

TextureSphere::TextureSphere(float rad, UINT stack, UINT slice, RendererInterface* renderer)
    :TextureShapeRenderer(renderer), _radius(rad), _stackCount(stack), _sliceCount(slice)
{
    CreateResource();
}

TextureSphere::TextureSphere(float rad, UINT stack, UINT slice, wstring path, RendererInterface* renderer)
    : TextureShapeRenderer(renderer), _radius(rad), _stackCount(stack), _sliceCount(slice)
{
    CreateResource();
    SetTexture(path);
}

void TextureSphere::CreateResource()
{
    vector<VertexTextureLight> vertices;

    VertexTextureLight vertex;
    vertex.pos = { 0, _radius, 0 };
    vertex.normal = { 0, 1, 0 };
    vertex.uv = { 0.5f, 0 };  // 북극의 UV 좌표 (0.5, 0)
    vertex.tangent = { 1, 0, 0 };  
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

            vertex.uv = {
                (float)j / _sliceCount,               // U: 경도에 해당하는 값 (0 ~ 1)
                (float)i / _stackCount               // V: 위도에 해당하는 값 (0 ~ 1)
            };

            Vector3 tangent;
            float cosTheta = cos(theta);
            float sinTheta = sin(theta);

            tangent = { -sinTheta, 0.0f, cosTheta };  // 구 표면의 탄젠트 벡터 (U 방향)
            vertex.tangent = tangent.GetNormalized(); // 정규화

            vertices.push_back(vertex);
        }
    }

    vertex.pos = { 0, -_radius, 0 };
    vertex.normal = { 0, -1, 0 };
    vertex.uv = { 0.5f, 1.0f };
    vertex.tangent = { 1, 0, 0 };
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



void TextureSphere::SetTexture(wstring path)
{
    _material->SetTexture(path);
}
