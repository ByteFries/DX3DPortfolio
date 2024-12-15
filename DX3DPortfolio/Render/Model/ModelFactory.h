#pragma once
#include <framework.h>
class ModelFactory
{
public:
	static StaticModel* CreateStaticModel(const string& modelName)
	{
		StaticModel* model = new StaticModel(modelName);
		model->ReadModelData();

		return model;
	}

	static SkeletalModel* CreateSkeletalModel(const string& modelName) 
	{
		SkeletalModel* model = new SkeletalModel(modelName);
		model->ReadModelData();

		return model;
	}
};