#pragma once
struct AABB;

struct Edge
{
	Edge() {}
	//Edge(Vector3 v1, Vector3 v2)
	//	:v1(v1), v2(v2) {}
	Edge(const Vector3& v1, const Vector3& v2) : v1(v1), v2(v2) {}

	bool operator==(const Edge& other) const 
	{
		return (v1 == other.v1 && v2 == other.v2) ||
			(v1 == other.v2 && v2 == other.v1);
	}

	struct Hash
	{
		std::size_t operator()(const Edge& edge) const
		{
			std::size_t h1 = std::hash<Vector3>()(edge.v1);
			std::size_t h2 = std::hash<Vector3>()(edge.v2);

			return h1 ^ h2;
		}
	};

	Vector3 v1, v2;
};

struct Face
{
	Face() {}
	Face(Vector3 normal, vector<Edge> edges) :normal(normal), edges(edges) {}

	Vector3 normal;
	vector<Edge> edges;
};

namespace ShapeNamespace
{
	enum ShapeType
	{
		SPHERE = 1 << 0,
		BOX = 1 << 1,
		CAPSULE = 1 << 2
	};

	enum ShapeCombination
	{
		SPHERE_SPHERE = (SPHERE | SPHERE),     
		BOX_BOX = (BOX | BOX),          
		CAPSULE_CAPSULE = (CAPSULE | CAPSULE),    
		SPHERE_BOX = (SPHERE | BOX),        
		SPHERE_CAPSULE = (SPHERE | CAPSULE),   
		BOX_CAPSULE = (BOX | CAPSULE),
		COMBINATION_COUNT = 6
	};
}

using namespace ShapeNamespace;

class Shape
{
public:

	Shape();
	virtual ~Shape();

	virtual std::shared_ptr<Shape> GetClone() abstract;

	void UpdateWorldVertices();
	void UpdateTransform(Vector3 pos, Vector3 eular);
	void Render();

	void SetColor(XMFLOAT4 color) { _cBuffer->SetColor(color); }
	
	float GetSurfaceArea() { return _surfaceArea;}

	virtual Matrix3x3 GetInertiaTensor(float mass) abstract;
	virtual float GetFrontalArea(Vector3 direction) abstract;

	Vector3 GetWorldPos() const { return _transform->GetWorldPos(); }
	virtual Vector3 FindFurthestPoint(const Vector3& direction);
	Vector3 GetClosestPoint(const Vector3& pos);

	const vector<Vector3>& GetVertices() const { return _vertices; }
	const vector<UINT>& GetIndices() const { return _indices; }
	vector<Vector3> GetWorldVertices();
	vector<Edge> GetWorldEdges();
	vector<Face> GetWorldFaces();
	const vector<Face>& GetFaces() { return _faces; }
	ShapeType GetShapeType() const { return _shapeType; }
	AABB GetAABB();
protected:
	virtual void CreateResource() abstract;
	virtual void CreateFaces() abstract;
	
	Transform* _transform;

	vector<Vector3> _worldVertices;
	vector<Vector3> _vertices;
	vector<UINT> _indices;
	StaticMesh* _mesh;
	VertexShader* _vShader;
	PixelShader* _pShader;
	ColorBuffer* _cBuffer;

	ShapeType _shapeType;

	vector<Face> _faces; // 노멀, 평면의 정점 중 하나
	vector<Edge> _edges;

	float _surfaceArea;

	bool _needToUpdate = true;
};