#pragma once
class EditorScene : public Scene
{
public:
	EditorScene();
	~EditorScene();

	// Scene을(를) 통해 상속됨
	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;
	void Debug() override;

private:
	TextureSphere* sphere;
	BrickPlatform* brick;
	Transform* transform;
	StaticModel* model;
	SkySphere* sky;
	Light* light;

	MeshRO* render;

	InstancedRenderer* renderer;
	vector<InstanceDataBase*> instanceDatas;
};

