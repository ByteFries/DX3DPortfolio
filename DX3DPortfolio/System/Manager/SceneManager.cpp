#include "framework.h"
#include "../Scene/TestScene.h"
#include "../Scene/GridScene.h"
#include "../Scene/EditorScene.h"
#include "SceneManager.h"

SceneManager::SceneManager()
{
	_scenese.push_back(new GridScene);
	_scenese.push_back(new EditorScene);
	//_scenese.push_back(new TestScene);

	_activeScene.push_back(_scenese[0]);
	_activeScene.push_back(_scenese[1]);
}

SceneManager::~SceneManager()
{
	for (Scene* scene : _scenese)
		delete scene;

	_scenese.clear();
}

void SceneManager::Update()
{
	for (Scene* scene : _activeScene)
		scene->Update();
}

void SceneManager::Render()
{
	for (Scene* scene : _activeScene)
		scene->Render();
}

void SceneManager::PostRender()
{
	for (Scene* scene : _activeScene)
		scene->PostRender();
}

void SceneManager::Debug()
{
	for (Scene* scene : _activeScene)
		scene->Debug();
}
