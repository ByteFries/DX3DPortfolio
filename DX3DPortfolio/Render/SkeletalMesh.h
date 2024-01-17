#pragma once
class SkeletalMesh : public Mesh
{
public:
	SkeletalMesh(string name);
	~SkeletalMesh();

	const vector<class NodeData>& GetNodes() { return _nodes; }
	const vector<class BoneData>& GetBones() { return _bones; }
	const map<string, UINT>& GetBoneMap() { return _boneMap; }

	bool HasBone(string boneName) { return _boneMap.count(boneName) != 0 ? true : false; }

private:
	virtual void ReadMesh() override;

	vector<NodeData> _nodes;
	vector<BoneData> _bones;
	map<string, UINT> _boneMap;
};