#pragma once
class StaticModel : public ModelBase
{
	friend class ModelFactory;
	StaticModel(string name);
public:
	~StaticModel();

	void Render() override;
private:
	void ReadModelData() override;
};