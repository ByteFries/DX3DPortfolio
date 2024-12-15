#include "framework.h"
#include "Bunny.h"

Bunny::Bunny()
{
	//ImportModelData("Bunny");
	_transform->_scale *= 0.001f;
	ClipData data;
	data.savePath = "Actor/Model/Data/Bunny/Clip/Bunny1.clip";
	ModelReader::ReadClip(data);
}

Bunny::~Bunny()
{
}


//void Bunny::ImportModelData(string path)
//{
//	ModelData data;
//	data.modelName = "Bunny";
//	ModelReader::ReadModel(data);
//	//_renderable->Render
//	//_mesh = new Mesh("Bunny");
//	//_mesh->SetModelParts(data.parts);
//
//	//_materials = data.materials;
//	//_materials[0]->SetDiffuseMap(L"Actor/Model/Data/Bunny/Texture/Bunny_BaseColor.png");
//	//_materials[0]->SetSpecularMap(L"Actor/Model/Data/Bunny/Texture/Bunny_Roughtness.png");
//}
