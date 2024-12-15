#pragma once
class AABBManager
{
public:
	AABBManager();
	AABBManager(const vector<AABB>& boxes);
	~AABBManager();

	void Render();
	void Debug();

	void Initialize(const vector<PhysicalObject*>& objs);
	AABB Get(UINT index) { return _boxes[index]; };
	void Update();
	void UpdateAABB(PhysicalObject* obj);

	void Add(PhysicalObject* obj);
	void Remove(int index);

	const unordered_set<OverlapPair, OverlapPair::Hash>& GetOverlaps() { return _overlaps; }
private:
	void UpdateLookupTable();

	void Update(vector<EndPoint>& endpoints, vector<UINT> lookup);

	bool Overlapping(AABB b0, AABB b1);

	vector<PhysicalObject*> _objs;

	vector<BoxShape*> _shapes;

	vector<AABB> _boxes;
	vector<EndPoint> _xEndpoints, _yEndpoints, _zEndpoints;
	unordered_set<OverlapPair, OverlapPair::Hash> _overlaps;
	vector<UINT> _xLookup, _yLookup, _zLookup;

	bool _invisible = true;
};

