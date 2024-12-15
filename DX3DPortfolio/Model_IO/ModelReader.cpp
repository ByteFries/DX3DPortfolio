#include "framework.h"
#include "ModelReader.h"

void ModelReader::ReadMeshes(ModelData& data)
{
	BinaryReader listReader(MODEL_IO_PATH + data.modelName + "/Mesh/MeshList.list");
	UINT listSize = listReader.ReadUINT();

	vector<MeshBase*> meshes;

	for (UINT i = 0; i < listSize; i++)
	{
		string meshName = listReader.ReadString();

		BinaryReader reader(MODEL_IO_PATH + data.modelName + "/Mesh/" + meshName + ".mesh");
		
		UINT materialIndex = reader.ReadUINT();
		data.materialIndices.push_back(materialIndex);

		int hasBone = reader.ReadInt();
		UINT numVertex = reader.ReadUINT();

		MeshBase* mesh;

		if (hasBone)
		{
			mesh = new SkeletalMesh();
			vector<SkeletalMeshVertex> vertices;
			vertices.resize(numVertex);
			void* ptr = vertices.data();
			reader.ReadData(&ptr, sizeof(SkeletalMeshVertex) * numVertex);

			UINT numIndex = reader.ReadUINT();
			vector<UINT> indices;
			indices.resize(numIndex);
			ptr = indices.data();
			reader.ReadData(&ptr, sizeof(UINT) * numIndex);

			mesh->CreateBuffers(vertices, indices);
		}
		else
		{
			mesh = new StaticMesh();
			vector<StaticMeshVertex> vertices;
			vertices.resize(numVertex);
			void* ptr = vertices.data();
			reader.ReadData(&ptr, sizeof(StaticMeshVertex) * numVertex);

			UINT numIndex = reader.ReadUINT();
			vector<UINT> indices;
			indices.resize(numIndex);
			ptr = indices.data();
			reader.ReadData(&ptr, sizeof(UINT) * numIndex);

			mesh->CreateBuffers(vertices, indices);
		}

		mesh->SetName(meshName);

		meshes.push_back(mesh);
	}

	{
		BinaryReader reader(MODEL_IO_PATH + data.modelName + "/Mesh/Nodes.node");
		UINT size = reader.ReadUINT();
		data.nodes.resize(size);

		for (int i = 0; i < size; i++)
		{
			data.nodes[i].index = reader.ReadInt();
			data.nodes[i].name = reader.ReadString();
			data.nodes[i].parent = reader.ReadInt();
			data.nodes[i].transform = reader.ReadXMMATRIX();
		}
	}

	{
		BinaryReader reader(MODEL_IO_PATH + data.modelName + "/Mesh/Bones.bone");
		UINT size = reader.ReadUINT();
		data.bones.resize(size);

		for (int i = 0; i < size; i++)
		{
			data.bones[i].index = reader.ReadInt();
			data.bones[i].name = reader.ReadString();
			data.bones[i].offset = reader.ReadXMMATRIX();

			data.boneMap.emplace(data.bones[i].name, data.bones[i].index);
		}
	}

	data.meshes = meshes;
}

void ModelReader::ReadClip(ClipData& data)
{
	BinaryReader reader(data.savePath);

	data.name = reader.ReadString();
	data.ticksPerSecond = reader.ReadFloat();
	data.frameCount = reader.ReadUINT();
	data.duration = reader.ReadFloat();

	UINT keyFrameCount = reader.ReadUINT();

	for (UINT i = 0; i < keyFrameCount; i++)
	{
		string boneName = reader.ReadString();

		UINT keyTransformCount = reader.ReadUINT();

		vector<KeyTransform> transforms;

		if (keyTransformCount > 0)
		{
			transforms.resize(keyTransformCount);

			void* ptr = (void*)transforms.data();
			reader.ReadData(&ptr, sizeof(KeyTransform) * keyTransformCount);
		}

		data.keyTransforms[boneName] = transforms;
	}
}

void ModelReader::ReadMaterials(ModelData& data)
{
	BinaryReader reader(MODEL_IO_PATH + data.modelName + "/Material/MaterialList.list");

	UINT size = reader.ReadUINT();

	vector<Material*> materials;

	for (UINT i = 0; i < size; i++)
	{
		Material* material = new Material();

		string file = MODEL_IO_PATH + data.modelName + "/Material/" + reader.ReadString() + ".mat";

		material->Load(file);

		material->SetShader(L"Model");

		materials.push_back(material);
	}

	data.materials = materials;
}

void ModelReader::ReadModel(ModelData& data)
{
	ReadMeshes(data);
	ReadMaterials(data);
}