#include "framework.h"
#include "ModelReader.h"

void ModelReader::ReadModelParts(ModelData& data, string name)
{
	BinaryReader listReader("Actor/Model/Data/" + name + "/Mesh/MeshList.list");
	UINT size = listReader.ReadUINT();

	vector<ModelPart*> parts;

	for (UINT i = 0; i < size; i++)
	{
		string meshName = listReader.ReadString();

		BinaryReader reader("Actor/Model/Data/" + name + "/Mesh/" + meshName +".mesh");

		UINT size = reader.ReadUINT();

		for (int i = 0; i < size; i++)
		{
			ModelPart* part = new ModelPart;

			part->SetName(meshName + to_string(i));

			UINT materialIndex = reader.ReadUINT();
			part->SetMaterialSlot(materialIndex);

			UINT count = reader.ReadUINT();

			vector<ModelVertex> vertices;

			vertices.resize(count);

			void* ptr = vertices.data();
			reader.ReadData(&ptr, sizeof(ModelVertex) * count);
			
			count = reader.ReadUINT();

			vector<UINT> indices;

			indices.resize(count);

			ptr = indices.data();

			reader.ReadData(&ptr, sizeof(UINT) * count);

			part->CreateBuffers(vertices, indices);

			parts.push_back(part);
		}
	}

	{
		BinaryReader reader("Actor/Model/Data/" + name + "/Mesh/Nodes.node");
		UINT size = reader.ReadUINT();
		data.nodes.resize(size);

		for (int i = 0; i < size; i++)
		{
			data.nodes[i].index = reader.ReadInt();
			data.nodes[i].name = reader.ReadString();
			data.nodes[i].parent = reader.ReadInt();
			data.nodes[i].transform = reader.ReadMatrix();
		}
	}

	{
		BinaryReader reader("Actor/Model/Data/" + name + "/Mesh/Bones.bone");

		UINT size = reader.ReadUINT();

		data.bones.resize(size);

		for (int i = 0; i < size; i++)
		{
			data.bones[i].index = reader.ReadInt();
			data.bones[i].name = reader.ReadString();
			data.bones[i].offset = reader.ReadMatrix();

			data.boneMap.emplace(data.bones[i].name, data.bones[i].index);
		}
	}

	data.parts = parts;
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
		KeyFrame* keyFrame = new KeyFrame;
		keyFrame->boneName = reader.ReadString();

		UINT keyTransformCount = reader.ReadUINT();

		if (keyTransformCount > 0)
		{
			keyFrame->transforms.resize(keyTransformCount);

			void* ptr = (void*)keyFrame->transforms.data();
			reader.ReadData(&ptr, sizeof(KeyTransform) * keyTransformCount);
		}

		data.keyFrames.emplace(keyFrame->boneName, keyFrame);
	}
}

void ModelReader::ReadMaterials(ModelData& data, string name)
{
	BinaryReader reader("Actor/Model/Data/" + name + "/Material/MaterialList.list");

	UINT size = reader.ReadUINT();

	vector<Material*> materials;

	for (UINT i = 0; i < size; i++)
	{
		Material* material = new Material();

		string file = "Actor/Model/Data/" + name + "/Material/" + reader.ReadString() + ".mat";
	
		material->Load(file);

		materials.push_back(material);
	}

	data.materials = materials;
}

void ModelReader::ReadModel(ModelData& data, string name)
{
	ReadMaterials(data, name);
	ReadModelParts(data, name);
}