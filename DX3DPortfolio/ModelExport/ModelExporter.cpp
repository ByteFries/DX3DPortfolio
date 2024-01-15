#include "Framework.h"
#include "ModelExporter.h"

ModelExporter::ModelExporter(string name)
	:_name(name)
{
	_importer = new Assimp::Importer();

	_importer->SetPropertyBool(AI_CONFIG_IMPORT_FBX_PRESERVE_PIVOTS, false);
	_importer->SetPropertyInteger(AI_CONFIG_PP_RVC_FLAGS, aiComponent_TANGENTS_AND_BITANGENTS);

	_scene = _importer->ReadFile("Actor/Model/Data/FBX/" + name + ".fbx",
		aiProcess_ConvertToLeftHanded | aiProcessPreset_TargetRealtime_MaxQuality);
	
	assert(_scene != nullptr);
}

ModelExporter::~ModelExporter()
{
	delete _importer;
}

void ModelExporter::ExportModel()
{
	ExportMaterial();
	ExportMesh();

	for (UINT i = 0; i < _scene->mNumAnimations; i++)
	{
		ClipData* clip = ReadClip(_scene->mAnimations[i]);

		WriteClip(clip, _name + to_string(i));

		delete clip;
	}
}

void ModelExporter::ExportClip(string file)
{
	_scene = _importer->ReadFile("Actor/Model/Data/" + _name + "/AnimationFBX/" + file + ".fbx",
		aiProcess_ConvertToLeftHanded | aiProcessPreset_TargetRealtime_MaxQuality);

	assert(_scene != nullptr);

	vector<string> clipNames;

	for (UINT i = 0; i < _scene->mNumAnimations; i++)
	{
		ClipData* clip = ReadClip(_scene->mAnimations[i]);

		WriteClip(clip, file + to_string(i));

		clipNames.push_back(clip->name);

		delete clip;
	}

	string savePath = "Actor/Model/Data/" + _name + "/Clip/" + "ClipNames.clip";

	BinaryWriter data(savePath);

	data.WriteData(clipNames.size());

	data.WriteData(clipNames.data(), sizeof(string) * clipNames.size());
}

void ModelExporter::ExportMaterial()
{
	for (UINT i = 0; i < _scene->mNumMaterials; i++)
	{
		aiMaterial* srcMaterial = _scene->mMaterials[i];

		Material* material = new Material();

		material->SetLabel(srcMaterial->GetName().C_Str());

		aiColor3D color;

		srcMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color);
		material->GetMaterialBuffer()->SetDiffuseColor(color.r, color.g, color.b, 1.0f);

		srcMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color);
		material->GetMaterialBuffer()->SetSpecularColor(color.r, color.g, color.b, 1.0f);

		srcMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color);
		material->GetMaterialBuffer()->SetAmbientColor(color.r, color.g, color.b, 1.0f);

		srcMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, color);
		material->GetMaterialBuffer()->SetEmissiveColor(color.r, color.g, color.b, 1.0f);

		int shininess;
		srcMaterial->Get(AI_MATKEY_SHININESS, shininess);

		material->GetMaterialBuffer()->SetShininess(shininess);

		aiString file;

		srcMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &file);
		material->SetDiffuseMap(CreateTexture(file.C_Str()));

		srcMaterial->GetTexture(aiTextureType_SPECULAR, 0, &file);
		material->SetSpecularMap(CreateTexture(file.C_Str()));

		srcMaterial->GetTexture(aiTextureType_NORMALS, 0, &file);
		material->SetNormalMap(CreateTexture(file.C_Str()));

		string savePath = "Actor/Model/Data/" + _name + "/Material/" + material->GetLabel() + ".mat";

		Utility::CreateFolder(savePath);

		material->Save(savePath);

		_materialNames.push_back(material->GetLabel());

		delete material;
	}

	BinaryWriter data("Actor/Model/Data/" + _name + "/Material/MaterialList.list");

	data.WriteData((UINT)_materialNames.size());

	for (string name : _materialNames)
		data.WriteData(name);
}

void ModelExporter::ExportMesh()
{
	ReadNode(_scene->mRootNode, 0, -1);

	ReadMesh(_scene->mRootNode);

	WriteMesh();
}

wstring ModelExporter::CreateTexture(string file)
{
	if (file.length() == 0)
		return L"";

	string fileName = Utility::GetFileName(file);

	const aiTexture* texture = _scene->GetEmbeddedTexture(file.c_str());

	string path = "_Texture/Model/" + _name + "/" + fileName;

	Utility::CreateFolder(path);

	if (PathFileExistsA(path.c_str()))
		return Utility::ToWString(path);

	if (texture == nullptr)
		return L"";

	if (texture->mHeight < 1)
	{
		BinaryWriter data(Utility::ToWString(path));
		data.WriteData(texture->pcData, texture->mWidth);
	}
	else
	{
		Image image;
		image.width      = texture->mWidth;
		image.height     = texture->mHeight;
		image.pixels     = (uint8_t*)texture->pcData;
		image.rowPitch   = image.width * 4;
		image.slicePitch = image.width * image.height * 4;

		SaveToWICFile(image, WIC_FLAGS_NONE, GetWICCodec(WIC_CODEC_PNG), Utility::ToWString(path).c_str());
	}

	return Utility::ToWString(path);
}

void ModelExporter::ReadMesh(aiNode* node)
{
	for (UINT i = 0; i < node->mNumMeshes; i++)
	{
		MeshData* mesh = new MeshData();

		mesh->name = node->mName.C_Str();
		
		vector<string>::iterator iter = find(_meshNames.begin(), _meshNames.end(), mesh->name);
		
		if (iter == _meshNames.end())
			_meshNames.push_back(mesh->name);

		UINT index = node->mMeshes[i];

		aiMesh* srcMesh = _scene->mMeshes[index];

		mesh->materialIndex = srcMesh->mMaterialIndex;

		UINT startVertex = mesh->vertices.size();

		/////////////////////////////////
		vector<VertexWeights> vertexWeights;
		vertexWeights.resize(srcMesh->mNumVertices);
		
		ReadBone(srcMesh, vertexWeights);
		/////////////////////////////////


		mesh->vertices.resize(srcMesh->mNumVertices);

		for (UINT j = 0; j < srcMesh->mNumVertices; j++)
		{
			ModelVertex vertex;

			memcpy(&vertex.pos, &srcMesh->mVertices[j], sizeof(Vector3));
			
			if (srcMesh->HasTextureCoords(0))
				memcpy(&vertex.uv, &srcMesh->mTextureCoords[0][j], sizeof(XMFLOAT2));

			if (srcMesh->HasNormals())
				memcpy(&vertex.normal, &srcMesh->mNormals[j], sizeof(Vector3));

			if (srcMesh->HasTangentsAndBitangents())
				memcpy(&vertex.tangent, &srcMesh->mTangents[j], sizeof(Vector3));

			if (!vertexWeights.empty())
			{
				vertexWeights[j].Normalize();

				vertex.indices.x = vertexWeights[j].indices[0];
				vertex.indices.y = vertexWeights[j].indices[1];
				vertex.indices.z = vertexWeights[j].indices[2];
				vertex.indices.w = vertexWeights[j].indices[3];

				vertex.weights.x = vertexWeights[j].weights[0];
				vertex.weights.y = vertexWeights[j].weights[1];
				vertex.weights.z = vertexWeights[j].weights[2];
				vertex.weights.w = vertexWeights[j].weights[3];
			}


			
			mesh->vertices[j] = vertex;
		}

		for (UINT j = 0; j < srcMesh->mNumFaces; j++)
		{
			aiFace& face = srcMesh->mFaces[j];

			for (UINT k = 0; k < face.mNumIndices; k++)
			{
				mesh->indices.push_back(face.mIndices[k] + startVertex);
			}
		}

		_meshes[mesh->name].push_back(mesh);
	}

	for (UINT i = 0; i < node->mNumChildren; i++)
	{
		ReadMesh(node->mChildren[i]);
	}
}

void ModelExporter::ReadNode(aiNode* node, int index, int parent)
{
	NodeData* nodeData = new NodeData();
	nodeData->index  = index;
	nodeData->parent = parent;
	nodeData->name   = node->mName.C_Str();

	XMMATRIX matrix(node->mTransformation[0]);
	matrix = XMMatrixTranspose(matrix);
	nodeData->transform = matrix;

	_nodes.emplace_back(nodeData);

	for (UINT i = 0; i < node->mNumChildren; i++)
	{
		ReadNode(node->mChildren[i], _nodes.size(), index);
	}
}

void ModelExporter::ReadBone(aiMesh* mesh, vector<VertexWeights>& vertexWeights)
{
	for (UINT i = 0; i < mesh->mNumBones; i++)
	{
		UINT boneIndex = 0;

		string name = mesh->mBones[i]->mName.C_Str();

		if (_boneMap.count(name) == 0)
		{
			boneIndex = _boneCount++;
			
			_boneMap.emplace(name, boneIndex);

			BoneData* boneData = new BoneData();
			boneData->index = boneIndex;
			boneData->name  = name;

			XMMATRIX matrix(mesh->mBones[i]->mOffsetMatrix[0]);
			matrix = XMMatrixTranspose(matrix);
			boneData->offset = matrix;

			_bones.emplace_back(boneData);
		}
		else
		{
			boneIndex = _boneMap[name];
		}

		for (UINT j = 0; j < mesh->mBones[i]->mNumWeights; j++)
		{
			UINT  index  = mesh->mBones[i]->mWeights[j].mVertexId;
			float weight = mesh->mBones[i]->mWeights[j].mWeight;
			
			vertexWeights[index].Add(boneIndex, weight);
		}
	}
}

void ModelExporter::WriteMesh()
{
	string path = "Actor/Model/Data/" + _name + "/Mesh/";

	Utility::CreateFolder(path);

	{
		BinaryWriter listWriter(path + "MeshList.list");
		listWriter.WriteData((UINT)_meshNames.size());

		for (pair<string, vector<MeshData*>> p : _meshes)
		{
			BinaryWriter writer(path + p.first + ".mesh");

			UINT size = p.second.size();

			writer.WriteData(size);

			for (int i = 0; i < size; i++)
			{
				writer.WriteData(p.second[i]->materialIndex);

				writer.WriteData((UINT)p.second[i]->vertices.size());
				writer.WriteData(p.second[i]->vertices.data(), p.second[i]->vertices.size() * sizeof(ModelVertex));

				writer.WriteData((UINT)p.second[i]->indices.size());
				writer.WriteData(p.second[i]->indices.data(), p.second[i]->indices.size() * sizeof(UINT));

				delete p.second[i];
			}

			listWriter.WriteData(p.first);
		}

		_meshes.clear();
		_meshNames.clear();
	}

	{
		BinaryWriter writer(path + "Nodes.node");

		writer.WriteData((UINT)_nodes.size());

		for (NodeData* node : _nodes)
		{
			writer.WriteData(node->index);
			writer.WriteData(node->name);
			writer.WriteData(node->parent);
			writer.WriteData(node->transform);

			delete node;
		}

		_nodes.clear();
	}

	{
		BinaryWriter writer(path + "Bones.bone");

		writer.WriteData((UINT)_bones.size());

		for (BoneData* bone : _bones)
		{
			writer.WriteData(bone->index);
			writer.WriteData(bone->name);
			writer.WriteData(bone->offset);

			delete bone;
		}

		_bones.clear();
	}
}

ModelExporter::ClipData* ModelExporter::ReadClip(aiAnimation* animation)
{
	ClipData* clip = new ClipData();
	clip->name           = animation->mName.C_Str();
	clip->ticksPerSecond = animation->mTicksPerSecond;
	clip->frameCount     = animation->mDuration + 1;
	clip->duration       = 0.0f;

	vector<ClipNode> clipNodes;

	for (UINT i = 0; i < animation->mNumChannels; i++)
	{
		aiNodeAnim* srcNode = animation->mChannels[i];

		ClipNode node;
		node.name = srcNode->mNodeName;

		UINT keyCount = max(max(srcNode->mNumPositionKeys, srcNode->mNumRotationKeys), srcNode->mNumScalingKeys);

		KeyTransform transform;

		for (UINT k = 0; k < keyCount; k++)
		{
			bool isFound = false;

			UINT t = node.keyFrame.size();

			if (k < srcNode->mNumScalingKeys)
			{
				aiVectorKey key = srcNode->mScalingKeys[k];

				if (abs(key.mTime - t) < FLT_EPSILON)
				{
					aiVector3D scale = key.mValue;

					transform.scale.x = scale.x;
					transform.scale.y = scale.y;
					transform.scale.z = scale.z;

					transform.time = key.mTime;

					isFound = true;
				}
			}

			if (k < srcNode->mNumRotationKeys)
			{
				aiQuatKey key = srcNode->mRotationKeys[k];

				if (abs(key.mTime - t) < FLT_EPSILON)
				{
					aiQuaternion rotation = key.mValue;

					transform.rotation.x = rotation.x;
					transform.rotation.y = rotation.y;
					transform.rotation.z = rotation.z;
					transform.rotation.w = rotation.w;

					transform.time = key.mTime;

					isFound = true;
				}
			}

			if (k < srcNode->mNumPositionKeys)
			{
				aiVectorKey key = srcNode->mPositionKeys[k];

				if (abs(key.mTime - t) < FLT_EPSILON)
				{
					aiVector3D position = key.mValue;

					transform.position.x = position.x;
					transform.position.y = position.y;
					transform.position.z = position.z;

					transform.time = key.mTime;

					isFound = true;
				}
			}

			if (isFound)
				node.keyFrame.push_back(transform);
		}

		if (node.keyFrame.size() < clip->frameCount)
		{
			UINT count = clip->frameCount - node.keyFrame.size();
			
			KeyTransform keyTransform;

			if (node.keyFrame.size())
				keyTransform = node.keyFrame.back();

			for (UINT n = 0; n < count; n++)
			{
				node.keyFrame.push_back(keyTransform);
			}
		}

		clip->duration = max(clip->duration, node.keyFrame.back().time);

		clipNodes.push_back(node);
	}

	ReadKeyFrame(clip, _scene->mRootNode, clipNodes);

	return clip;
}

void ModelExporter::WriteClip(ClipData* clip, string file)
{
	string savePath = "Actor/Model/Data/" + _name + "/Clip/" + file + ".clip";

	Utility::CreateFolder(savePath);

	BinaryWriter data(savePath);
	data.WriteData(clip->name);
	data.WriteData(clip->ticksPerSecond);
	data.WriteData(clip->frameCount);
	data.WriteData(clip->duration);

	data.WriteData(clip->keyFrame.size());

	for (KeyFrame* keyFrame : clip->keyFrame)
	{
		data.WriteData(keyFrame->boneName);

		data.WriteData(keyFrame->transforms.size());
		data.WriteData(keyFrame->transforms.data(), sizeof(KeyTransform) * keyFrame->transforms.size());

		delete keyFrame;
	}

	clip->keyFrame.clear();
}

void ModelExporter::ReadKeyFrame(ClipData* clip, aiNode* node, vector<ClipNode>& clipNodes)
{
	KeyFrame* keyFrame = new KeyFrame();

	keyFrame->boneName = node->mName.C_Str();

	for (UINT i = 0; i < clip->frameCount; i++)
	{
		ClipNode* clipNode = nullptr;

		for (ClipNode& temp : clipNodes) 
		{
			if (temp.name == node->mName)
			{
				clipNode = &temp;
				break;
			}
		}

		KeyTransform keyTransform;

		if (clipNode == nullptr)
		{
			XMMATRIX transform(node->mTransformation[0]);
			transform = XMMatrixTranspose(transform);

			XMVECTOR S, R, T;
			XMMatrixDecompose(&S, &R, &T, transform);

			keyTransform.scale    = S;
			XMStoreFloat4(&keyTransform.rotation, R);
			keyTransform.position = T;

			keyTransform.time = i;
		}
		else
		{
			keyTransform = clipNode->keyFrame[i];
		}

		keyFrame->transforms.push_back(keyTransform);
	}

	clip->keyFrame.push_back(keyFrame);

	for (UINT i = 0; i < node->mNumChildren; i++)
	{
		ReadKeyFrame(clip, node->mChildren[i], clipNodes);
	}
}
