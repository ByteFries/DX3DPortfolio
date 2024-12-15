#pragma once
class AssetManager : public Singleton<AssetManager>
{
	friend class Singleton;
	AssetManager();
	~AssetManager();

public:


private:
	map<string, MeshBase*> _meshes;
	map<string, Material*> _materials;

};

