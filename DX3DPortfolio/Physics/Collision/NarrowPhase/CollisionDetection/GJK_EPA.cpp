#include "framework.h"
#include "GJK_EPA.h"

void GJK_EPA::EPA(CollisionInfo& info)
{
	vector<Vector3> polytope(_simplex.Begin(), _simplex.End());
	vector<size_t> faces =
	{
		0, 1, 2,
		0, 3, 1,
		0, 2, 3,
		1, 3, 2
	};

	vector<Vector4> normals;
	size_t minFace;

	auto normal_minFace = GetFaceNormals(polytope, faces);

	normals = normal_minFace.first;
	minFace = normal_minFace.second;

	Vector3 minNormal;
	float minDistance = FLT_MAX;

	while (minDistance == FLT_MAX)
	{
		minNormal = normals[minFace].xyz();
		minDistance = normals[minFace].w;

		minNormal.Normalize();
		Vector3 supportPoint = Support(minNormal);
		float sDistance = Vector3::Dot(minNormal, supportPoint);

		if (sDistance > minDistance + FLT_EPSILON)
		{
			minDistance = FLT_MAX;

			std::vector<std::pair<size_t, size_t>> uniqueEdges;

			for (size_t i = 0; i < normals.size(); i++) 
			{
				float outSideDistance = Vector3::Dot(supportPoint - polytope[faces[i * 3]], normals[i].xyz());

				if (outSideDistance > 0)
				{					
					//Vector3::Dot(normals[i].xyz(), supportPoint) >
					//Vector3::Dot(normals[i].xyz(), (polytope[faces[i * 3]])))
					
					size_t f = i * 3;

					AddIfUniqueEdge(uniqueEdges, faces, f, f + 1);
					AddIfUniqueEdge(uniqueEdges, faces, f + 1, f + 2);
					AddIfUniqueEdge(uniqueEdges, faces, f + 2, f);

					faces[f + 2] = faces.back(); faces.pop_back();
					faces[f + 1] = faces.back(); faces.pop_back();
					faces[f] = faces.back(); faces.pop_back();

					normals[i] = normals.back();
					normals.pop_back();

					i--;
				}
			}

			std::vector<size_t> newFaces;
			for (pair<size_t, size_t> p : uniqueEdges)
			{
				newFaces.push_back(p.first);
				newFaces.push_back(p.second);
				newFaces.push_back(polytope.size());
			}

			polytope.push_back(supportPoint);

			normal_minFace = GetFaceNormals(polytope, newFaces);

			vector<Vector4> newNormals = normal_minFace.first;
			size_t newMinFace = normal_minFace.second;

			float oldMinDistance = FLT_MAX;

			for (size_t i = 0; i < normals.size(); i++) {
				if (normals[i].w < oldMinDistance) {
					oldMinDistance = normals[i].w;
					minFace = i;
				}
			}

			if (newNormals.size() == 0)
				PHYSICS->SetStop(true);

			else if (newNormals[newMinFace].w < oldMinDistance) {
				minFace = newMinFace + normals.size();
			}

			faces.insert(faces.end(), newFaces.begin(), newFaces.end());
			normals.insert(normals.end(), newNormals.begin(), newNormals.end());
		}
	}

	info.collisionNormal = minNormal;

	Vector3 bToa = _s2->GetWorldPos() - _s1->GetWorldPos();

	if (Vector3::Dot(bToa, info.collisionNormal) < 0)
		info.collisionNormal = -info.collisionNormal;

	info.penetrationDepth = minDistance;
}

pair<vector<Vector4>, size_t> GJK_EPA::GetFaceNormals(
	const vector<Vector3>& polytope,
	const vector<size_t>& faces)
{
	vector<Vector4> normals;
	size_t minTriangle = 0;
	float minDistance = FLT_MAX;

	for (size_t i = 0; i < faces.size(); i += 3)
	{
		Vector3 a = polytope[faces[i    ]];
		Vector3 b = polytope[faces[i + 1]];
		Vector3 c = polytope[faces[i + 2]];
	
		Vector3 normal = Vector3::Cross(b-a, c-a).GetNormalized();
		float distance = Vector3::Dot(normal, a);
	
		if (distance < 0)
		{
			  normal *= -1;
			distance *= -1;
		}
	
		normals.emplace_back(normal, distance);
	
		if (distance < minDistance)
		{
			minTriangle = i / 3;
			minDistance = distance;
		}
	}

	return { normals, minTriangle };
}

void GJK_EPA::AddIfUniqueEdge(vector<pair<size_t, size_t>>& edges, const vector<size_t>& faces, size_t a, size_t b)
{
	auto reverse = std::find(                       
		edges.begin(),                              
		edges.end(),                                
		std::make_pair(faces[b], faces[a]) 
	);

	if (reverse != edges.end()) 
	{
		edges.erase(reverse);
	}
	else 
	{
		edges.emplace_back(faces[a], faces[b]);
	}
}

bool GJK_EPA::Line(Simplex& simplex, Vector3& direction)
{
	Vector3 a = simplex[0];
	Vector3 b = simplex[1];

	Vector3 ab = b - a;
	Vector3 ao = -a;

	if (SameDirection(ab, ao))
	{
		direction = Vector3::Cross(Vector3::Cross(ab, ao), ab);
		
		if (direction == Vector3(0, 0, 0))
		{
			direction = Vector3::Cross(ab, { 1,0,0 });
			if (direction == Vector3(0, 0, 0))
				direction = Vector3::Cross(ab, { 0,0,-1 });
		}
	}
	else
	{
		simplex = { a };
		direction = ao;
	} 

	return false;
}

bool GJK_EPA::Triangle(Simplex& simplex, Vector3& direction)
{
	Vector3 a = simplex[0];
	Vector3 b = simplex[1];
	Vector3 c = simplex[2];

	//Vector3 ab = b - a;  
	//Vector3 ac = c - a;  
	//Vector3 ao = -a;
	//Vector3 cb = b - c;
	//Vector3 ca = a - c;
	//Vector3 co = -c;

	//if (SameDirection(Vector3::Cross(Vector3::Cross(cb, ca), ca), co))
	//{
	//	simplex = {a, c};
	//	direction = Vector3::Cross(Vector3::Cross(ac, ao), ac);
	//	return false;
	//}
	//else if (SameDirection(Vector3::Cross(Vector3::Cross(ca, cb), cb), co))
	//{
	//	simplex = {a, b};
	//	direction = Vector3::Cross(Vector3::Cross(ab, ao), ab);
	//	return false;
	//}
	//
	//Vector3 faceNormal = Vector3::Cross(ab, ac);
	//
	//if (SameDirection(faceNormal, ao)) {
	//	direction = faceNormal;
	//}
	//else {
	//	// 원점이 삼각형의 반대쪽에 있는 경우
	//	simplex = { a, c, b };
	//	direction = -faceNormal;
	//}

	Vector3 n = Vector3::Cross(b - c, a - c); // 삼각형의 법선
	Vector3 co = -c; // 원점 방향 벡터

	if (Vector3::Dot(Vector3::Cross(b - c, n), co) > 0) { // 가장 가까운 edge가 CB일 때
		a = c;
		direction = Vector3::Cross(Vector3::Cross(b - c, co), b - c);
		return false;
	}
	if (Vector3::Dot(Vector3::Cross(n, a - c), co) > 0) { // 가장 가까운 edge가 CA일 때
		b = c;
		direction = Vector3::Cross(Vector3::Cross(a - c, co), a - c);
		return false;
	}

	if (Vector3::Dot(n, co) > 0) { // 삼각형 위에 있을 때
		
		_simplex = {c, a, b};
		//d = a;
		a = b;
		b = c;
		direction = n;
		return false;
	}
	// 삼각형 아래에 있을 때
	//d = b;
	b = c;
	direction = -n;

	return false;
}

bool GJK_EPA::Tetrahedron(Simplex& simplex, Vector3& direction)
{
	//Vector3 a = simplex[0];
	//Vector3 b = simplex[1];
	//Vector3 c = simplex[2];
	//Vector3 d = simplex[3];
	//
	//Vector3 ab = b - a;
	//Vector3 ac = c - a;
	//Vector3 ad = d - a;
	//Vector3 bd = d - b;
	//Vector3 ao = -a;
	//
	//Vector3 abc = Vector3::Cross(ab, ac);
	//Vector3 acd = Vector3::Cross(ac, ad);
	//Vector3 adb = Vector3::Cross(ad, ab);
	//
	//
	//if (SameDirection(abc, ao)) {
	//	return Triangle(simplex = { a, b, c }, direction);
	//}
	//
	//if (SameDirection(acd, ao)) {
	//	return Triangle(simplex = { a, c, d }, direction);
	//}
	//
	//if (SameDirection(adb, ao)) {
	//	return Triangle(simplex = { a, d, b }, direction);
	//}
	Vector3 a = simplex[0];
	Vector3 b = simplex[1];
	Vector3 c = simplex[2];
	Vector3 d = simplex[3];

	// AO 벡터
	Vector3 ao = -a;

	// 사면체의 각 삼각형 면을 검사하여, 원점이 위치한 면을 선택합니다.
	Vector3 abcNormal = Vector3::Cross(b - a, c - a);
	if (SameDirection(abcNormal, ao)) {
		// 원점이 ABC 면에 존재
		simplex = { a, b, c };
		direction = abcNormal;
		return false;
	}

	Vector3 acdNormal = Vector3::Cross(c - a, d - a);
	if (SameDirection(acdNormal, ao)) {
		// 원점이 ACD 면에 존재
		simplex = { a, c, d };
		direction = acdNormal;
		return false;
	}

	Vector3 adbNormal = Vector3::Cross(d - a, b - a);
	if (SameDirection(adbNormal, ao)) {
		// 원점이 ADB 면에 존재
		simplex = { a, d, b };
		direction = adbNormal;
		return false;
	}
	return true;
}

Vector3 GJK_EPA::Support(Vector3 direction)
{
	direction.Normalize();
	Vector3 convex1 = _s1->FindFurthestPoint(direction);
	Vector3 convex2 = _s2->FindFurthestPoint(-direction);
	Vector3 support = convex1 - convex2;

	_simplex.Push_front(support);

	return support;
}

bool GJK_EPA::NextSimplex(Simplex& simplex, Vector3& direction)
{
	switch (simplex.size())
	{
	case 2:
		return Line(simplex, direction);
	case 3: 
		return Triangle(simplex, direction);
	case 4: 
		return Tetrahedron(simplex, direction);
	}

	return false;
}

bool GJK_EPA::SameDirection(const Vector3& direction, const Vector3& ao)
{
	return Vector3::Dot(direction, ao) > 0;
}

bool GJK_EPA::Detection(Shape* s1,Shape* s2, CollisionInfo& info)
{
	count = 0;
	_simplex.Clear();

	_s1 = s1;
	_s2 = s2;

	_v1 = _s1->GetWorldVertices();
	_v2 = _s2->GetWorldVertices();


	Vector3 supportPoint = Support(Vector3(1, 0, 0));
	Vector3 direction = -supportPoint;

	while (count < 100000)
	{
		count++;
		supportPoint = Support(direction);
		float dot = Vector3::Dot(supportPoint, direction);
		if (Vector3::Dot(supportPoint, direction) <= 0)
			return false;

		if (NextSimplex(_simplex, direction))
		{
			EPA(info);
			return true;
		}
	}

	if (count >= 100000)
	{
		_simplex.Clear();

		Vector3 supportPoint = Support(Vector3(1, 0, 0));
		Vector3 direction = -supportPoint;

		while (true)
		{
			supportPoint = Support(direction);
			float dot = Vector3::Dot(supportPoint, direction);
			if (Vector3::Dot(supportPoint, direction) <= 0)
				return false;

			if (NextSimplex(_simplex, direction))
			{
				EPA(info);
				return true;
			}
		}
	}

	return false;
}


