#include "framework.h"
#include "ColorQuad.h"

ColorQuad::ColorQuad(Vector2 size, XMFLOAT4 color, RendererInterface* renderer)
    :ColorShapeRenderer(renderer), _size(size)
{
    CreateResource();
    _cBuffer->SetColor(color);
}

ColorQuad::~ColorQuad()
{
}

void ColorQuad::Render(D3D11_PRIMITIVE_TOPOLOGY type)
{
    ColorShapeRenderer::Render(type);
}

void ColorQuad::SetColor(XMFLOAT4 color)
{
    _cBuffer->SetColor(color);
}

void ColorQuad::CreateResource()
{
    Vector2 halfSize = _size * 0.5f;
    std::vector<VertexLight> vertices;
    
    float L = -halfSize.x;
    float R = +halfSize.x;
    float B = -halfSize.y;
    float T = +halfSize.y;

    vertices =
    {
        {Vector3(L, T, 0.0f), {0, 0, -1}},
        {Vector3(R, T, 0.0f), {0, 0, -1}},
        {Vector3(L, B, 0.0f), {0, 0, -1}},
        {Vector3(R, B, 0.0f), {0, 0, -1}}
    };

    std::vector<UINT> indices =
    {
        0,1,2,
        2,1,3
    };

    _mesh->CreateBuffers(vertices, indices);
}
