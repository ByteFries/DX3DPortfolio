#pragma once

namespace MaterialNamespace
{
	enum class MaterialProperty
	{
		RUBBER = 0,
		ICE = 1 << 0,
		STONE = 1 << 1,
		WOOD = 1 << 2
	};
}

using namespace MaterialNamespace;
using namespace ShapeNamespace;

class PhysicsCoefficientProvider
{
public:
	static float GetStaticFriction(MaterialProperty mat1, MaterialProperty mat2);
	static float GetKineticFriction(MaterialProperty mat1, MaterialProperty mat2);
	static float GetRestitution(MaterialProperty mat1, MaterialProperty mat2);
	
	static float GetLinearDrag() { return _linearDragCoefficient; }
	static float GetAngularDrag() { return _angularDragCoefficient; }
	static float GetDragCoefficient(ShapeType type, bool isMoving);
private:
	static int GetIndex(MaterialProperty mat1, MaterialProperty mat2);

	static float _linearDragCoefficient;
	static float _angularDragCoefficient;
	static const float _staticFriction[10];
	static const float _kineticFriction[10];
	static const float _restitution[10];
	static const float _dragCoefficient[6];

};