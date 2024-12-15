#pragma once
#define GJK_SIMPLEX2_EPS (0.0f)
#define GJK_SIMPLEX3_EPS (0.0f)
#define GJK_SIMPLEX4_EPS (0.0f)

class GJK_EPA : public CollisionDetectionInterface
{
	struct Face
	{
		Vector3 v[3];
		Vector3 normal;
	};

public:
	GJK_EPA() {}
	~GJK_EPA() {}

	bool Detection(Shape* s1, Shape* s2, CollisionInfo& info) override;

private:
	void EPA(CollisionInfo& info);
	const Simplex& GetSimplex() { return _simplex; }

	pair<vector<Vector4>, size_t> GetFaceNormals(const vector<Vector3>& polytope, const vector<size_t>& faces);
	void AddIfUniqueEdge(vector<pair<size_t, size_t>>& edges, const vector<size_t>& faces, size_t a, size_t b);

	bool Line(Simplex& simplex, Vector3& direction);
	bool Triangle(Simplex& simplex, Vector3& direction);
	bool Tetrahedron(Simplex& simplex, Vector3& direction);

	Vector3 Support(Vector3 direction);
	bool NextSimplex(Simplex& simplex, Vector3& direction);

	bool SameDirection(const Vector3& direction, const Vector3& ao);

	Shape* _s1;
	Shape* _s2;
	vector<Vector3> _v1, _v2;
	Simplex _simplex;

	UINT count;
};

