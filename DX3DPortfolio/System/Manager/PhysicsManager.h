#pragma once
using namespace PhysicsType;

class PhysicsManager : public Singleton<PhysicsManager>
{
	friend class Singleton;

	PhysicsManager();
	~PhysicsManager();
public:
	void Update();
	void Render();
	void Debug();

	PhysicalObject* GetSphere(float mass, float rad, UINT stack, UINT slice);
	PhysicalObject* GetBox(float mass, Vector3 size);
	PhysicalObject* GetCapsule(float mass, float height, float rad, UINT stack, UINT slice);
	
	void StartInitial();

	Vector3 GetWindDirection() { return _windDirection; }
	float GetWindSpeed() { return _windSpeed; }
	float GetGravity() { return _gravity; }
	float GetAirDen() { return _airDensity; }

	const unordered_set<int>& GetCollisionSets(int index) { return _collisionSets[index]; }
	CollisionInfo& GetCollisionInfo(int index1, int index2);

	void SetStop(bool val) { _stop = val; }
	float GetDelta() { return _deltaTime; }
private:
	int GetCollisionPairIndex(int index0, int index1);
	void UpdateAABB();
	void CheckCollisions();

	vector<OverlapPair> _collisionPairs;
	unordered_map<int, unordered_set<int>> _collisionSets;
	unordered_map<int, unordered_set<int>> _cashedSets;

	unordered_map<int, CollisionInfo> _collisionInfos;

	queue<PhysicalObject*> _waitingQueue;
	vector<PhysicalObject*> _objects;
	vector<PhysicalObject*> _actives;

	vector<PhysicalCalculator*> _calculators;
	AABBManager* _broadPhase;
	CollisionManager* _narrowPhase;
	SequentialImpulseSolver* _SISolver;

	bool _invisible = false;
	bool _stop = true;
	UINT _indexCounter = 0;

	Vector3 _windDirection = { 0,0,0 };
	float _windSpeed = 0.0f;
	float _airDensity = 1.23f;
	float _gravity = 9.8f;
	float _deltaTime = 0.02f;
	vector<SphereShape*> contacts;

	int _debugIndex = 0;
};

