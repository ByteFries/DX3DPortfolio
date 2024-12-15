#include "framework.h"
#include "PhysicsCoefficientProvider.h"

const float PhysicsCoefficientProvider::_staticFriction[10] =
{
	 1.0f, // 고무 고무
	 0.2f, // 얼음 얼음
	 0.3f, // 돌   돌
	 0.6f, // 나무 나무
};

const float PhysicsCoefficientProvider::_kineticFriction[10] =
{
	 0.8f, // 고무 고무
	 0.1f, // 얼음 얼음
	 0.2f, // 돌   돌
	 0.5f, // 나무 나무
};

const float PhysicsCoefficientProvider::_restitution[10] =
{
	0.8f, // 고무 고무
	0.3f, // 얼음 얼음
	0.1f, // 돌   돌
	0.5f, // 나무 나무
};

const float PhysicsCoefficientProvider::_dragCoefficient[6] =
{
	0.5f,  // 구 정지
	0.4f,  // 구 이동
	1.05f, // 육면체 정지
	1.0f,   // 육면체 이동
	0.6f,  // 캡슐 정지
	0.5f   // 캡슐 이동
};

float PhysicsCoefficientProvider::_linearDragCoefficient = 0.2f;
float PhysicsCoefficientProvider::_angularDragCoefficient = 0.2f;


float PhysicsCoefficientProvider::GetStaticFriction(MaterialProperty mat1, MaterialProperty mat2)
{
    return _staticFriction[GetIndex(mat1, mat2)];
}

float PhysicsCoefficientProvider::GetKineticFriction(MaterialProperty mat1, MaterialProperty mat2)
{
    return _kineticFriction[GetIndex(mat1, mat2)];
}

float PhysicsCoefficientProvider::GetRestitution(MaterialProperty mat1, MaterialProperty mat2)
{
    return _restitution[GetIndex(mat1, mat2)];
}

float PhysicsCoefficientProvider::GetDragCoefficient(ShapeType type, bool isMoving)
{
	int index = static_cast<int>(type + (isMoving ? 1 : 0));
	return _dragCoefficient[index];
}

int PhysicsCoefficientProvider::GetIndex(MaterialProperty mat1, MaterialProperty mat2)
{
    int index1 = static_cast<int>(mat1);
    int index2 = static_cast<int>(mat2);

    return index1 | index2;
}
