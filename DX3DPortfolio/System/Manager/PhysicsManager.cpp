#include "framework.h"
#include "PhysicsManager.h"

#define CollisionPair OverlapPair

PhysicsManager::PhysicsManager()
{
	_broadPhase = new AABBManager();
	_narrowPhase = new CollisionManager();
	_SISolver = new SequentialImpulseSolver();

	_calculators.push_back(new CalculatorStatic);
	_calculators.push_back(new CalculatorLinearBasic);
	_calculators.push_back(new CalculatorAngularBasic);
	_calculators.push_back(new CalculatorLABasic);
	contacts.push_back(new SphereShape(0.1, 5, 5));
	contacts.push_back(new SphereShape(0.1, 5, 5));
	contacts.push_back(new SphereShape(0.1, 5, 5));
	contacts.push_back(new SphereShape(0.1, 5, 5));
	contacts.push_back(new SphereShape(0.1, 5, 5));
	contacts.push_back(new SphereShape(0.1, 5, 5));
	contacts.push_back(new SphereShape(0.1, 5, 5));
}

PhysicsManager::~PhysicsManager()
{
	for (PhysicalCalculator* calculator : _calculators)
		delete calculator;

	_calculators.clear();

	delete _broadPhase;
	delete _narrowPhase;
	delete _SISolver;

	for (PhysicalObject* p : _objects)
		delete p;

	_objects.clear();

	while (!_waitingQueue.empty())
	{
		PhysicalObject* obj = _waitingQueue.front();
		_waitingQueue.pop();
		delete obj;
	}

	for (int i = 0; i < contacts.size(); i++)
		delete contacts[i];
}


void PhysicsManager::Render()
{
	if (_invisible)
		return;

	for (const PhysicalObject* obj : _objects)
		obj->GetShapeConst()->Render();

	for (OverlapPair pair : _collisionPairs)
	{
		int index = GetCollisionPairIndex(pair.index0, pair.index1);
		auto info = _collisionInfos[index];

		for (int i = 0; i < info.contactPoints.size(); i++)
		{
			if (i >= contacts.size())
				continue;
			contacts[i]->UpdateTransform(info.contactPoints[i].pos, {0,0,0});
			contacts[i]->Render();
		}
	}

}

void PhysicsManager::Debug()
{
	if (ImGui::TreeNode("Physics"))
	{
#pragma region Main
		if (ImGui::TreeNode("Main"))
		{
			ImGui::Checkbox("Invisible", &_invisible);
			ImGui::Checkbox("Stop", &_stop);
			ImGui::TreePop();
		}
#pragma endregion


#pragma region Environment
		if (ImGui::TreeNode("Envirionment"))
		{
			ImGui::SliderFloat("DeltaTime", &_deltaTime, 0, 1.0f);
			ImGui::SliderFloat("AirDensity", &_airDensity, 0, 5.0f);
			ImGui::SliderFloat("Gravity", &_gravity, 0, 20.0f);
			ImGui::SliderFloat("WindDirX", &_windDirection.x, 0, 360.0f);
			ImGui::SliderFloat("WindDiry", &_windDirection.y, 0, 360.0f);
			ImGui::SliderFloat("WindDirz", &_windDirection.z, 0, 360.0f);
			ImGui::SliderFloat("WindSpeed", &_windSpeed, 0, 100.0f);

			ImGui::TreePop();
		}
#pragma endregion


#pragma region Object Properties
		if (ImGui::TreeNode("Object Properties"))
		{
			ImGui::InputInt("Index = ", &_debugIndex);

			if (ImGui::TreeNode("Object"))
			{
				auto obj = _objects[_debugIndex];

				auto force = obj->GetForce();
				auto vel = obj->GetVelocity();
				auto angvel = obj->GetAngularVelocity();
				auto eul = obj->GetEular();
				auto pos = obj->GetPos();

				ImGui::Text("Force.x : %f", force.x);
				ImGui::Text("Force.y : %f", force.y);
				ImGui::Text("Force.z : %f", force.z);

				ImGui::Text("Velocity.x : %f", vel.x);
				ImGui::Text("Velocity.y : %f", vel.y);
				ImGui::Text("Velocity.z : %f", vel.z);

				ImGui::Text("AngularVel.x : %f", angvel.x);
				ImGui::Text("AngularVel.y : %f", angvel.y);
				ImGui::Text("AngularVel.z : %f", angvel.z);

				ImGui::Text("pos.x : %f", pos.x);
				ImGui::Text("pos.y : %f", pos.y);
				ImGui::Text("pos.z : %f", pos.z);

				ImGui::Text("eul.x : %f", eul.x);
				ImGui::Text("eul.y : %f", eul.y);
				ImGui::Text("eul.z : %f", eul.z);

				ImGui::TreePop();
			}

			ImGui::TreePop();
		}
#pragma endregion

#pragma region CollisionPairs
		if (ImGui::TreeNode("CollisionPairs"))
		{
			for (int i = 0; i < _collisionPairs.size(); i++)
			{
				ImGui::Text("%d, %d", _collisionPairs[i].index0, _collisionPairs[i].index1);
			}

			ImGui::TreePop();
		}
#pragma endregion
		_SISolver->Debug();

		ImGui::TreePop();
	}

}

void PhysicsManager::Update()
{
	if (_stop)
		return;

	for (PhysicalObject* obj : _actives)
	{
		int motionBehavior = obj->GetBehaviorFlag();
	
		_calculators[motionBehavior]->Calculate(obj);

		obj->UpdateWithForce();
	}
	
	CheckCollisions();
	_SISolver->Resolve(_objects, _collisionPairs);

	for (PhysicalObject* obj : _actives)
	{
		obj->UpdatePosAndRotation();
		//obj->ApplyDamping();
	}

}

void PhysicsManager::CheckCollisions()
{
	for (PhysicalObject* obj : _actives)
	{
		_broadPhase->UpdateAABB(obj);
	}

	_broadPhase->Update();
	unordered_set<OverlapPair, OverlapPair::Hash> overlaps = _broadPhase->GetOverlaps();

	_cashedSets = _collisionSets;
	_collisionSets.clear();
	_collisionPairs.clear();
	ContactPointFinderInterface::ResetCounter();

	for (OverlapPair pair : overlaps)
	{
		CollisionInfo info;

		PhysicalObject* o1 = _objects[pair.index0];
		PhysicalObject* o2 = _objects[pair.index1];

		if (pair.index0 == pair.index1)
			continue;

		bool bothStatic = (o1->IsStatic()) && (o2->IsStatic());

		if (bothStatic)
			continue;

		if (pair.index0 == 1 && pair.index1 == 2)
			o2->IsBehaviorFlagSet(STATIC);
		
		if (_narrowPhase->CheckCollsion(o1, o2, info))
		{
			_collisionPairs.push_back(pair);
			_collisionSets[pair.index0].insert(pair.index1);
			_collisionSets[pair.index1].insert(pair.index0);

			int pairIndex = GetCollisionPairIndex(pair.index0, pair.index1);

			_collisionInfos[pairIndex] = info;
		}
	}
}

CollisionInfo& PhysicsManager::GetCollisionInfo(int index1, int index2)
{
	int index = GetCollisionPairIndex(index1, index2);
	return _collisionInfos[index];
}

PhysicalObject* PhysicsManager::GetSphere(float mass, float rad, UINT stack, UINT slice)
{
	if (_indexCounter > OBJECT_MAX_COUNT)
		return nullptr;

	PhysicalObject* obj = new PhysicalObject(_indexCounter++, mass);

	Shape* shape = new SphereShape(rad, stack, slice);

	obj->SetShape(shape);

	_waitingQueue.push(obj);

	return obj;
}

PhysicalObject* PhysicsManager::GetBox(float mass, Vector3 size)
{
	if (_indexCounter > OBJECT_MAX_COUNT)
		return nullptr;

	PhysicalObject* obj = new PhysicalObject(_indexCounter++, mass);

	Shape* shape = new BoxShape(size);

	obj->SetShape(shape);

	_waitingQueue.push(obj);

	return obj;
}

PhysicalObject* PhysicsManager::GetCapsule(float mass, float height, float rad, UINT stack, UINT slice)
{
	if (_indexCounter > OBJECT_MAX_COUNT)
		return nullptr;

	PhysicalObject* obj = new PhysicalObject(_indexCounter++, mass);

	Shape* shape = new CapsuleShape(height, rad, stack, slice);

	obj->SetShape(shape);

	_waitingQueue.push(obj);

	return obj;
}

void PhysicsManager::StartInitial()
{
	if (_waitingQueue.empty())
		return;

	while (!_waitingQueue.empty())
	{
		PhysicalObject* obj = _waitingQueue.front();
		_waitingQueue.pop();

		obj->Update(P_DELTA);

		_objects.push_back(obj);
		_actives.push_back(obj);
	}

	_broadPhase->Initialize(_objects);
}

int PhysicsManager::GetCollisionPairIndex(int index0, int index1)
{
	return (index0 << OBJECT_MAX_BIT) | index1;
}

void PhysicsManager::UpdateAABB()
{
	for (PhysicalObject* obj : _actives)
	{
		//움직임 유무 확인 함수 필요
		_broadPhase->UpdateAABB(obj);
	}

	while (!_waitingQueue.empty())
	{
		PhysicalObject* obj = _waitingQueue.front();
		_waitingQueue.pop();

		obj->Update(P_DELTA);

		_objects.push_back(obj);
		_actives.push_back(obj);

		_broadPhase->Add(obj);
	}
}

