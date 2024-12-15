#pragma once
class GJK_EPA2 : public CollisionDetectionInterface
{
public:

	bool Detection(Shape* s1, Shape* s2, CollisionInfo& info) override;

private:

	void Triangle(Vector3& a, Vector3& b, Vector3& c, Vector3& d, int& simp_dim, Vector3& search_dir);
	bool Tetrahedron(Vector3& a, Vector3& b, Vector3& c, Vector3& d, int& simp_dim, Vector3& search_dir);
	void EPA(Vector3 a, Vector3 b, Vector3 c, Vector3 d, Shape* s1, Shape* s2, CollisionInfo& info);


};

