#pragma once
class ModelInterface
{
public:
	virtual ~ModelInterface() {}

	virtual void Render() abstract;
protected:
	virtual void ReadModelData() abstract;
};
