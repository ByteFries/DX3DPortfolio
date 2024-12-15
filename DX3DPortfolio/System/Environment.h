#pragma once
class Environment : public Singleton<Environment>
{
	friend class Singleton;
	Environment();
	~Environment();
public:
	void SetEnvrionment();
	void SetViewport(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);
	void Debug();
private:
	void CreateProjection();
	void CreateViewport();

	XMMATRIX _persMatrix;

	MatrixBuffer* _persBuffer;

	CameraBuffer* _camBuffer;
};

