#pragma once
class SkeletalMesh : public StaticMesh
{
public:
	SkeletalMesh();
	~SkeletalMesh();

	virtual void Render(D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST) override;

	virtual void Update() override;

	const vector<class NodeData>& GetNodes() { return _nodes; }
	const vector<class BoneData>& GetBones() { return _bones; }
	const map<string, UINT>& GetBoneMap() { return _boneMap; }

	bool HasBone(string boneName) { return _boneMap.count(boneName) != 0 ? true : false; }

private:
	//Animation

	vector<NodeData> _nodes;
	vector<BoneData> _bones;
	map<string, UINT> _boneMap;

};