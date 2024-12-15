#include "framework.h"
#include "CapsuleShape.h"

CapsuleShape::CapsuleShape(float height, float radius, int stack, int slice)
    :_height(height), _radius(radius), _stackCount(stack), _sliceCount(slice)
{
    CreateResource();
    CreateFaces();

    _shapeType = CAPSULE;
    _surfaceArea = 2.0f * XM_PI * radius * height + 6.0f * XM_PI * radius * radius;;
}

float CapsuleShape::GetFrontalArea(Vector3 direction)
{
	return 0.0f;
}

void CapsuleShape::CreateResource()
{
    float halfHeight = _height * 0.5f; // 캡슐 중심에서 절반 높이

    Vector3 topPole = Vector3(0.0f, halfHeight + _radius, 0.0f);
    _vertices.push_back(topPole);
    // 위쪽 반구 정점 생성
    for (int lat = 1; lat <= _stackCount; ++lat) { // lat = 1부터 시작
        float theta = XM_PI * 0.5f * (float(lat) / _stackCount);
        float sinTheta = sinf(theta);
        float cosTheta = cosf(theta);

        for (int lon = 0; lon <= _sliceCount; ++lon) {
            float phi = XM_2PI * (float(lon) / _sliceCount);
            float sinPhi = sinf(phi);
            float cosPhi = cosf(phi);

            Vector3 vertex = Vector3(_radius * cosPhi * sinTheta, halfHeight + _radius * cosTheta, _radius * sinPhi * sinTheta);
            _vertices.push_back(vertex);
        }
    }

    // 원통 부분 정점 생성
    for (int i = 0; i <= 1; ++i) {
        float y = (i == 0 ? halfHeight : -halfHeight);

        for (int lon = 0; lon <= _sliceCount; ++lon) {
            float phi = XM_2PI * (float(lon) / _sliceCount);
            float sinPhi = sinf(phi);
            float cosPhi = cosf(phi);

            Vector3 vertex = Vector3(_radius * cosPhi, y, _radius * sinPhi);
            _vertices.push_back(vertex);
        }
    }

    // 아래쪽 반구 정점 생성
    for (int lat = _stackCount; lat >= 1; --lat) { // lat = _stackCount부터 1까지 감소
        float theta = XM_PI * 0.5f * (float(lat) / _stackCount);
        float sinTheta = sinf(theta);
        float cosTheta = cosf(theta);

        for (int lon = 0; lon <= _sliceCount; ++lon) {
            float phi = XM_2PI * (float(lon) / _sliceCount);
            float sinPhi = sinf(phi);
            float cosPhi = cosf(phi);

            Vector3 vertex = Vector3(_radius * cosPhi * sinTheta, -halfHeight - _radius * cosTheta, _radius * sinPhi * sinTheta);
            _vertices.push_back(vertex);
        }
    }

    // 아래쪽 극점 추가
    Vector3 bottomPole = Vector3(0.0f, -halfHeight - _radius, 0.0f);
    _vertices.push_back(bottomPole);

    
    int baseIndex = 1; // 위쪽 극점 바로 다음 정점부터 시작

    for (int lon = 0; lon < _sliceCount; ++lon) {
        _indices.push_back(0); // 위쪽 극점
        _indices.push_back(baseIndex + lon);
    }

    // 위쪽 반구의 나머지 라인 생성
    for (int lat = 0; lat < _stackCount - 1; ++lat) { // 극점 제외
        for (int lon = 0; lon < _sliceCount; ++lon) {
            int current = baseIndex + lat * (_sliceCount + 1) + lon;
            int next = current + _sliceCount + 1;
    
            // 세로 라인
            _indices.push_back(current);
            _indices.push_back(next);
    
            // 가로 라인
            _indices.push_back(current);
            _indices.push_back(current + 1);
        }
    }
    
    //// 원통 부분 라인 인덱스 생성
    int offset = baseIndex + _stackCount * (_sliceCount + 1);

    for (int i = 0; i < _sliceCount; ++i) {
        int top1 = offset + i;
        int top2 = offset + (i + 1) % (_sliceCount + 1);
        int bottom1 = top1 + _sliceCount + 1;
        int bottom2 = top2 + _sliceCount + 1;
    
        // 원통 부분의 세로 라인
        _indices.push_back(top1);
        _indices.push_back(bottom1);
    
        // 원통 부분의 가로 라인 (상단)
        _indices.push_back(top1);
        _indices.push_back(top2);
    
        // 원통 부분의 가로 라인 (하단)
        _indices.push_back(bottom1);
        _indices.push_back(bottom2);
    }
    
   // 아래쪽 반구 라인 인덱스 생성
    offset += 2 * (_sliceCount + 1);

    for (int lat = 0; lat < _stackCount; ++lat) {
        for (int lon = 0; lon < _sliceCount; ++lon) {
            int current = offset + lat * (_sliceCount + 1) + lon;
            int next = current + 1;
    
            // 아래쪽 반구 라인 (수평)
            _indices.push_back(current);
            _indices.push_back(next);
    
            // 아래쪽 반구 라인 (수직)
            if (lat < _stackCount - 1) {
                int below = current + _sliceCount + 1;
                _indices.push_back(current);
                _indices.push_back(below);
            }
        }
    }
    
    // 아래쪽 극점과의 연결
    int bottomPoleIndex = static_cast<int>(_vertices.size() - 1);
    int lastRingStartIndex = _vertices.size() - 1 - _sliceCount; // 마지막 링의 시작 인덱스
    
    for (int lon = 0; lon < _sliceCount; ++lon) {
        int lastRingIndex = lastRingStartIndex + lon; // 마지막 링의 정점
        _indices.push_back(lastRingIndex); // 마지막 링의 정점
        _indices.push_back(bottomPoleIndex); // 아래쪽 극점
    }

    _mesh->CreateBuffers(_vertices, _indices);
    _worldVertices.resize(_vertices.size());
}

void CapsuleShape::CreateFaces()
{
    vector<UINT> indices;
    //// 인덱스 생성 - 위쪽 반구, 원통, 아래쪽 반구 연결
    // 
    // 위쪽 반구 인덱스
    for (int i = 1; i <= _sliceCount; i++)
    {
        indices.push_back(0);
        indices.push_back(i + 1);
        indices.push_back(i);
    }

    int baseIndex = 1;
    int ringVertexCount = _sliceCount + 1; // 각 위도에서 생성되는 정점의 수

    for (int i = 0; i < _stackCount - 1; ++i) {
        for (int j = 0; j < _sliceCount; ++j) {
            indices.push_back(baseIndex + i * ringVertexCount + j);
            indices.push_back(baseIndex + i * ringVertexCount + j + 1);
            indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);

            indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);
            indices.push_back(baseIndex + i * ringVertexCount + j + 1);
            indices.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);
        }
    }

    // 원통 부분 인덱스 생성
    baseIndex = (_stackCount + 1) * (_sliceCount + 1) + 1;
    for (int i = 0; i < _sliceCount; ++i) {
        int topCurrent = 1 + (_stackCount - 1) * (_sliceCount + 1) + i;
        int topNext = topCurrent + 1;
        int bottomCurrent = baseIndex + i;
        int bottomNext = bottomCurrent + 1;

        indices.push_back(topCurrent);
        indices.push_back(topNext);
        indices.push_back(bottomCurrent);

        indices.push_back(topNext);
        indices.push_back(bottomNext);
        indices.push_back(bottomCurrent);
    }

    // 아래쪽 반구 인덱스 생성
    baseIndex = (_stackCount + 1) * (_sliceCount + 1) + 1; // 원통 부분 아래쪽 첫 정점 인덱스

    for (int i = 0; i < _stackCount; ++i) {
        for (int j = 0; j < _sliceCount; ++j) {
            int topCurrent = baseIndex + i * (_sliceCount + 1) + j;
            int topNext = topCurrent + 1;
            int bottomCurrent = baseIndex + (i + 1) * (_sliceCount + 1) + j;
            int bottomNext = bottomCurrent + 1;

            indices.push_back(topCurrent);
            indices.push_back(topNext);
            indices.push_back(bottomCurrent);

            indices.push_back(topNext);
            indices.push_back(bottomNext);
            indices.push_back(bottomCurrent);
        }
    }

    int southPoleIndex = _vertices.size() - 1;

    // 아래쪽 반구 마지막 위도에 있는 정점의 시작 인덱스
    baseIndex = (_stackCount + 1) * (_sliceCount + 1) + 1 + (_stackCount - 1) * (_sliceCount + 1);

    for (int i = 0; i < _sliceCount; ++i) {
        int current = baseIndex + i;
        int next = baseIndex + i + 1;

        indices.push_back(southPoleIndex);
        indices.push_back(current);
        indices.push_back(next);
    }

    unordered_map<Vector3, unordered_set<Edge, Edge::Hash>, hash<Vector3>> faceMap;
    
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

std::shared_ptr<Shape> CapsuleShape::GetClone()
{
    std::shared_ptr<Shape> clone = std::make_shared<CapsuleShape>(_height, _radius, _stackCount, _sliceCount);
    clone->UpdateTransform(_transform->_translation, _transform->_rotation);

    return clone;
}

Matrix3x3 CapsuleShape::GetInertiaTensor(float mass)
{
    float Izz_sphere = (2.0f / 5.0f) * (mass / 2.0f) * (_radius * _radius); // 구의 Izz
    float Izz_cylinder = (1.0f / 12.0f) * (mass / 2.0f) * (3 * _radius * _radius + _height * _height); // 원기둥의 Izz
    float Izz = Izz_sphere + Izz_cylinder; // z축에 대한 총 관성

    float Ixy_sphere = Izz_sphere; // 구에 대해 x,y축 회전 관성
    float Ixy_cylinder = (1.0f / 4.0f) * (mass / 2.0f) * (_radius * _radius) + (1.0f / 12.0f) * (mass / 2.0f) * (_height * _height); // 원기둥의 x,y축 회전 관성
    float Ixy = Ixy_sphere + Ixy_cylinder; // x, y축에 대한 총 관성

    return Matrix3x3(
        Ixy, 0.0f, 0.0f,   // 첫 번째 행: Ixx, 0, 0
        0.0f, Ixy, 0.0f,   // 두 번째 행: 0, Iyy, 0
        0.0f, 0.0f, Izz    // 세 번째 행: 0, 0, Izz
    );
}
