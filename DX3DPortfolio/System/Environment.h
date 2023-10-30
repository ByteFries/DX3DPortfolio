#pragma once
class Environment :public Singleton<Environment>
{
	friend class Singleton;
	Environment();
	~Environment();
public:

	void SetPerspective();
	
private:
	void CreateProjection();
	void CreateViewport();

	MatrixBuffer* _proj;
	SunBuffer* _sunBuffer;

};

