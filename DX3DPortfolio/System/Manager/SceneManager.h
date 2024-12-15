#pragma once
class SceneManager :public Singleton<SceneManager>
{
	friend class Singleton;

public:
	void Update();
	void Render();
	void PostRender();
	void Debug();
private:
	SceneManager();
	~SceneManager();

	vector<Scene*> _scenese;
	vector<Scene*> _activeScene;
};