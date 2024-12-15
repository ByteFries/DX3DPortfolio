#include "framework.h"
#include "AABBManager.h"

AABBManager::AABBManager()
{
}

AABBManager::AABBManager(const vector<AABB>& boxes)
{
	_boxes = boxes;

	_xEndpoints.resize(_boxes.size() * 2);
	_yEndpoints.resize(_boxes.size() * 2);
	_zEndpoints.resize(_boxes.size() * 2);

	for (int i = 0; i < _boxes.size(); ++i)
	{
		_xEndpoints[i * 2 + 0].type = EndPoint::BEGIN;
		_xEndpoints[i * 2 + 0].value = _boxes[i].xEnd[0];
		_xEndpoints[i * 2 + 0].index = i;

		_yEndpoints[i * 2 + 0].type = EndPoint::BEGIN;
		_yEndpoints[i * 2 + 0].value = _boxes[i].yEnd[0];
		_yEndpoints[i * 2 + 0].index = i;
		
		_zEndpoints[i * 2 + 0].type = EndPoint::BEGIN;
		_zEndpoints[i * 2 + 0].value = _boxes[i].zEnd[0];
		_zEndpoints[i * 2 + 0].index = i;

		_xEndpoints[i * 2 + 1].type = EndPoint::END;
		_xEndpoints[i * 2 + 1].value = _boxes[i].xEnd[1];
		_xEndpoints[i * 2 + 1].index = i;
							
		_yEndpoints[i * 2 + 1].type = EndPoint::END;
		_yEndpoints[i * 2 + 1].value = _boxes[i].yEnd[1];
		_yEndpoints[i * 2 + 1].index = i;
							
		_zEndpoints[i * 2 + 1].type = EndPoint::END;
		_zEndpoints[i * 2 + 1].value = _boxes[i].zEnd[1];
		_zEndpoints[i * 2 + 1].index = i;
	}

	sort(_xEndpoints.begin(), _xEndpoints.end());
	sort(_yEndpoints.begin(), _yEndpoints.end());
	sort(_zEndpoints.begin(), _zEndpoints.end());

	UpdateLookupTable();

	set<int> active;

	for (int i = 0; i < _xEndpoints.size(); ++i)
	{
		EndPoint end = _xEndpoints[i];
		int index = end.index;
		if (end.type == EndPoint::BEGIN)
		{
			for (int activeIndex : active)
			{
				AABB box0 = _boxes[activeIndex];
				AABB box1 = _boxes[index];
				if (Overlapping(box0, box1))
					_overlaps.insert(OverlapPair(activeIndex, index));
			}
		}
		else
		{
			active.erase(index);
		}
	}
}

AABBManager::~AABBManager()
{
	for (BoxShape* shape : _shapes)
	{
		delete shape;
	}

	_shapes.clear();
}

void AABBManager::Render()
{
	if (_invisible) return;

	for (BoxShape* shape : _shapes)
		shape->Render();
}

void AABBManager::Debug()
{
	if (ImGui::TreeNode("AABB Manager"))
	{
		ImGui::Checkbox("invisible", &_invisible);

		ImGui::TreePop();
	}
}

void AABBManager::Initialize(const vector<PhysicalObject*>& objs)
{
	_boxes.resize(objs.size());
	for (int i = 0; i < objs.size(); ++i)
	{
		AABB objAABB = objs[i]->GetShape()->GetAABB();
		Vector3 size;
		AABB box;
		box.xEnd[0] = objAABB.xEnd[0];
		box.xEnd[1] = objAABB.xEnd[1];

		box.yEnd[0] = objAABB.yEnd[0];
		box.yEnd[1] = objAABB.yEnd[1];

		box.zEnd[0] = objAABB.zEnd[0];
		box.zEnd[1] = objAABB.zEnd[1];

		_boxes[i] = box;
	}

	_xEndpoints.resize(_boxes.size() * 2);
	_yEndpoints.resize(_boxes.size() * 2);
	_zEndpoints.resize(_boxes.size() * 2);

	for (int i = 0; i < _boxes.size(); ++i)
	{
		_xEndpoints[i * 2 + 0].type = EndPoint::BEGIN;
		_xEndpoints[i * 2 + 0].value = _boxes[i].xEnd[0];
		_xEndpoints[i * 2 + 0].index = objs[i]->GetIndex();

		_yEndpoints[i * 2 + 0].type = EndPoint::BEGIN;
		_yEndpoints[i * 2 + 0].value = _boxes[i].yEnd[0];
		_yEndpoints[i * 2 + 0].index = objs[i]->GetIndex();

		_zEndpoints[i * 2 + 0].type = EndPoint::BEGIN;
		_zEndpoints[i * 2 + 0].value = _boxes[i].zEnd[0];
		_zEndpoints[i * 2 + 0].index = objs[i]->GetIndex();

		_xEndpoints[i * 2 + 1].type = EndPoint::END;
		_xEndpoints[i * 2 + 1].value = _boxes[i].xEnd[1];
		_xEndpoints[i * 2 + 1].index = objs[i]->GetIndex();

		_yEndpoints[i * 2 + 1].type = EndPoint::END;
		_yEndpoints[i * 2 + 1].value = _boxes[i].yEnd[1];
		_yEndpoints[i * 2 + 1].index = objs[i]->GetIndex();

		_zEndpoints[i * 2 + 1].type = EndPoint::END;
		_zEndpoints[i * 2 + 1].value = _boxes[i].zEnd[1];
		_zEndpoints[i * 2 + 1].index = objs[i]->GetIndex();
	}

	sort(_xEndpoints.begin(), _xEndpoints.end());
	sort(_yEndpoints.begin(), _yEndpoints.end());
	sort(_zEndpoints.begin(), _zEndpoints.end());

	_xLookup.resize(_xEndpoints.size());
	_yLookup.resize(_yEndpoints.size());
	_zLookup.resize(_zEndpoints.size());

	for (int i = 0; i < _xEndpoints.size(); ++i)
	{
		int index = _xEndpoints[i].index;
		int type = _xEndpoints[i].type;
		int sum = index + type;
		_xLookup[_xEndpoints[i].index * 2 + _xEndpoints[i].type] = i;
		_yLookup[_yEndpoints[i].index * 2 + _yEndpoints[i].type] = i;
		_zLookup[_zEndpoints[i].index * 2 + _zEndpoints[i].type] = i;
	}

	set<int> active;

	for (int i = 0; i < _xEndpoints.size(); ++i)
	{
		EndPoint end = _xEndpoints[i];
		int index = end.index;
		if (end.type == EndPoint::BEGIN)
		{
			for (int activeIndex : active)
			{
				AABB box0 = _boxes[activeIndex];
				AABB box1 = _boxes[index];
				if (Overlapping(box0, box1))
					_overlaps.insert(OverlapPair(activeIndex, index));
			}
			active.insert(index);
		}
		else
		{
			active.erase(index);
		}
	}
}

void AABBManager::Update()
{
	Update(_yEndpoints, _yLookup);
	Update(_xEndpoints, _xLookup);
	Update(_zEndpoints, _zLookup);
}

void AABBManager::UpdateAABB(PhysicalObject* obj)
{
	int index = obj->GetIndex();

	AABB box = obj->GetShape()->GetAABB();
	_boxes[obj->GetIndex()] = box;

	_xEndpoints[_xLookup[index * 2 + 0]].value = box.xEnd[0];
	_xEndpoints[_xLookup[index * 2 + 0]].type = EndPoint::BEGIN;
	_xEndpoints[_xLookup[index * 2 + 1]].value = box.xEnd[1];
	_xEndpoints[_xLookup[index * 2 + 1]].type = EndPoint::END;

	_yEndpoints[_yLookup[index * 2 + 0]].value = box.yEnd[0];
	_yEndpoints[_yLookup[index * 2 + 0]].type = EndPoint::BEGIN;
	_yEndpoints[_yLookup[index * 2 + 1]].value = box.yEnd[1];
	_yEndpoints[_yLookup[index * 2 + 1]].type = EndPoint::END;

	_zEndpoints[_zLookup[index * 2 + 0]].value = box.zEnd[0];
	_zEndpoints[_zLookup[index * 2 + 0]].type = EndPoint::BEGIN;
	_zEndpoints[_zLookup[index * 2 + 1]].value = box.zEnd[1];
	_zEndpoints[_zLookup[index * 2 + 1]].type = EndPoint::END;
}

void AABBManager::Add(PhysicalObject* obj)
{
	AABB box = obj->GetShape()->GetAABB();

	_boxes.push_back(box);

	int index = obj->GetIndex();

	EndPoint beginX, endX, beginY, endY, beginZ, endZ;

	beginX.type = EndPoint::BEGIN;
	beginX.value = box.xEnd[0];
	beginX.index = index;

	endX.type = EndPoint::END;
	endX.value = box.xEnd[1];
	endX.index = index;

	beginY.type = EndPoint::BEGIN;
	beginY.value = box.yEnd[0];
	beginY.index = index;

	endY.type = EndPoint::END;
	endY.value = box.yEnd[1];
	endY.index = index;

	beginZ.type = EndPoint::BEGIN;
	beginZ.value = box.zEnd[0];
	beginZ.index = index;

	endZ.type = EndPoint::END;
	endZ.value = box.zEnd[1];
	endZ.index = index;

	_xEndpoints.push_back(beginX);
	_xEndpoints.push_back(endX);
	_yEndpoints.push_back(beginY);
	_yEndpoints.push_back(endY);
	_zEndpoints.push_back(beginZ);
	_zEndpoints.push_back(endZ);
	

	while (_xLookup.size() <= index * 2 + 1) {
		_xLookup.push_back(_xLookup.size());
		_yLookup.push_back(_yLookup.size());
		_zLookup.push_back(_zLookup.size());
	}

	_xLookup[index * 2 + EndPoint::BEGIN] = _xEndpoints.size() - 2;
	_xLookup[index * 2 + EndPoint::END] = _xEndpoints.size() - 1;
	_yLookup[index * 2 + EndPoint::BEGIN] = _yEndpoints.size() - 2;
	_yLookup[index * 2 + EndPoint::END] = _yEndpoints.size() - 1;
	_zLookup[index * 2 + EndPoint::BEGIN] = _zEndpoints.size() - 2;
	_zLookup[index * 2 + EndPoint::END] = _zEndpoints.size() - 1;
}

void AABBManager::Remove(int index)
{
	auto xBeginPos = std::find_if(_xEndpoints.begin(), _xEndpoints.end(),
		[index](const EndPoint& ep) { return ep.index == index && ep.type == EndPoint::BEGIN; });
	auto xEndPos = std::find_if(_xEndpoints.begin(), _xEndpoints.end(),
		[index](const EndPoint& ep) { return ep.index == index && ep.type == EndPoint::END; });
	
	_xEndpoints.erase(xBeginPos);
	_xEndpoints.erase(xEndPos);

	auto yBeginPos = std::find_if(_yEndpoints.begin(), _yEndpoints.end(),
		[index](const EndPoint& ep) { return ep.index == index && ep.type == EndPoint::BEGIN; });
	auto yEndPos = std::find_if(_yEndpoints.begin(), _yEndpoints.end(),
		[index](const EndPoint& ep) { return ep.index == index && ep.type == EndPoint::END; });

	_yEndpoints.erase(yBeginPos);
	_yEndpoints.erase(yEndPos);

	auto zBeginPos = std::find_if(_zEndpoints.begin(), _zEndpoints.end(),
		[index](const EndPoint& ep) { return ep.index == index && ep.type == EndPoint::BEGIN; });
	auto zEndPos = std::find_if(_zEndpoints.begin(), _zEndpoints.end(),
		[index](const EndPoint& ep) { return ep.index == index && ep.type == EndPoint::END; });

	_zEndpoints.erase(zBeginPos);
	_zEndpoints.erase(zEndPos);

	UpdateLookupTable();

	auto overlapIt = _overlaps.begin();
	while (overlapIt != _overlaps.end()) {
		if (overlapIt->index0 == index || overlapIt->index1 == index) {
			overlapIt = _overlaps.erase(overlapIt);
		}
		else {
			++overlapIt;
		}
	}
}

void AABBManager::UpdateLookupTable()
{
	_xLookup.resize(_xEndpoints.size());
	_yLookup.resize(_yEndpoints.size());
	_zLookup.resize(_zEndpoints.size());

	for (int i = 0; i < _xEndpoints.size(); ++i)
	{
		_xLookup[_xEndpoints[i].index * 2 + _xEndpoints[i].type] = i;
		_yLookup[_yEndpoints[i].index * 2 + _yEndpoints[i].type] = i;
		_zLookup[_zEndpoints[i].index * 2 + _zEndpoints[i].type] = i;
	}
}

void AABBManager::Update(vector<EndPoint>& endpoints, vector<UINT> lookup)
{
	for (int i = 1; i < endpoints.size(); ++i)
	{
		EndPoint key = endpoints[i];

		int j = i - 1;

		while (j >= 0 && key < endpoints[j])
		{
			EndPoint end0 = endpoints[j + 0];
			EndPoint end1 = endpoints[j + 1];

			if (end0.type == EndPoint::BEGIN)
			{ 
				if (end1.type == EndPoint::END)
					_overlaps.erase(OverlapPair(end0.index, end1.index));
			}
			else
			{
				if (end1.type == EndPoint::BEGIN)
				{
					AABB b0 = _boxes[end0.index];
					AABB b1 = _boxes[end1.index];

					if (Overlapping(b0, b1))
						_overlaps.insert(OverlapPair(end0.index, end1.index));
				}
			}
			endpoints[j] = end1;
			endpoints[j + 1] = end0;
			lookup[end1.index * 2 + end1.type] = j;
			lookup[end0.index * 2 + end0.type] = j + 1;
			--j;
		}
		endpoints[j + 1] = key;
		lookup[key.index * 2 + key.type] = j + 1;
	}
}

bool AABBManager::Overlapping(AABB b0, AABB b1)
{
	if ((b0.xEnd[1] < b1.xEnd[0]) || (b0.xEnd[0] > b1.xEnd[1]))
		return false;

	if ((b0.yEnd[1] < b1.yEnd[0]) || (b0.yEnd[0] > b1.yEnd[1]))
		return false;

	if ((b0.zEnd[1] < b1.zEnd[0]) || (b0.zEnd[0] > b1.zEnd[1]))
		return false;

	return true;
}

