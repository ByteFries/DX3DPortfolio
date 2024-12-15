#pragma once
class SkeletalModel : public ModelBase
{
	friend class ModelFactory;
	SkeletalModel(string name);
public:
	~SkeletalModel();

	void Render() override;

private:
	void ReadModelData() override;

	vector<BoneData> _bones;
	map<string, UINT> _boneMap;
};

