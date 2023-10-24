#pragma once
class Environment :public Singleton<Environment>
{
	friend class Singleton;
	Environment();
	~Environment();
public:

private:
	void CreateProjection();
	void CreateViewport();

	MatrixBuffer* _proj;

};

