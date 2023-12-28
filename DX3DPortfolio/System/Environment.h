#pragma once
class Environment :public Singleton<Environment>
{
	friend class Singleton;
	Environment();
	~Environment();
public:
	void SetPerspective();

	XMMATRIX GetPersMatrix() { return _persMatrix; }

	void SetViewport(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);

	void SetEnvironment();
private:
	void CreateProjection();
	void CreateViewport();

	XMMATRIX _persMatrix;
	MatrixBuffer* _pers;
	LightBuffer* _lBuffer;
};

