#include "framework.h"
#include "ModelReader.h"

ModelReader::ModelReader(string name)
	:_name(name)
{
	ReadMaterials();
	ReadMeshes();
}

ModelReader::~ModelReader()
{
	for (ModelMesh* mesh : _meshes)
		delete mesh;

	for (Material* material : _materials)
		delete material;

	_materials.clear();
	_meshes.clear();
}

void ModelReader::SetShader(wstring file)
{
}

void ModelReader::Render()
{
	for (ModelMesh* mesh : _meshes)
	{
		mesh->Render();
	}
}

void ModelReader::RenderInstanced(UINT instanceCount)
{
}

void ModelReader::Debug()
{
}

void ModelReader::ReadMeshes()
{
	BinaryReader listReader("Model/Data/" + _name + "/Mesh/MeshList.list");
	UINT size = listReader.ReadUINT();

	for (UINT i = 0; i < size; i++)
	{
		string meshName = listReader.ReadString();

		BinaryReader reader("Model/Data/" + _name + "/Mesh/" + meshName +".mesh");
		ModelMesh* mesh = new ModelMesh;
		mesh->SetName(reader.ReadString());

		UINT materialIndex = reader.ReadUINT();
		mesh->SetMaterial(_materials[materialIndex]);

		{
			UINT count = reader.ReadUINT();

			vector<ModelVertex>& vertices = mesh->GetVertices();
			
			vertices.resize(count);

			void* ptr = vertices.data();

			reader.ReadData(&ptr, sizeof(ModelVertex) * count);
		}

		{
			UINT count = reader.ReadUINT();

			vector<UINT>& indices = mesh->GetIndices();

			void* ptr = indices.data();

			reader.ReadData(&ptr, sizeof(UINT) * count);
		}

		mesh->Create();

		_meshes.push_back(mesh);
	}
}

void ModelReader::ReadMaterials()
{
	BinaryReader data("Model/Data/" + _name + "/Material/MaterialList.list");

	UINT size = data.ReadUINT();

	for (UINT i = 0; i < size; i++)
	{
		Material* material = new Material();

		string file = "Model/Data/" + _name + "/Material/" + data.ReadString() + ".mat";
	
		material->Load(file);

		_materials.push_back(material);
	}
}
