#include "LoadManager.h"
#include "DebugManager.h"
#include "EngineData.h"
#include "GraphicsEngine.h"
#include "ModelParser.h"
#include "GraphicEngineManager.h"

using namespace ParserData;

std::map<std::string, ModelData*> LoadManager::ModelList;
std::map<std::string, TextureBuffer*> LoadManager::TextureList;
std::map<std::string, OneAnimation*> LoadManager::AnimationList;
LoadManager::LoadManager()
{
	GEngine = nullptr;
	EaterParser = nullptr;
}

LoadManager::~LoadManager()
{

}

void LoadManager::Initialize(GraphicEngineManager* Graphic)
{
	//�׷��� ���� �޾ƿ���
	GEngine = Graphic;
	EaterParser = ModelParser::Create(ModelParser::FBX);

	EaterParser->Initialize();
}

ModelData* LoadManager::GetMesh(std::string Name)
{
	std::map<std::string, ModelData*>::iterator temp = ModelList.find(Name);
	if (temp == ModelList.end())
	{
		DebugManager::Print(Name, 0, 0, DebugManager::MSG_TYPE::MSG_LOAD, true);
		return nullptr;
	}
	else
	{
		return temp->second;
	}

}

TextureBuffer* LoadManager::GetTexture(std::string Name)
{
	std::map<std::string, TextureBuffer*>::iterator temp = TextureList.find(Name);
	if (temp == TextureList.end())
	{
		DebugManager::Print(Name, 0, 0, DebugManager::MSG_TYPE::MSG_LOAD, true);
		return nullptr;
	}
	else
	{
		return temp->second;
	}
}

void LoadManager::LoadMesh(std::string Name, bool Scale, bool LoadAnime)
{
	// "../ �̰ſ� .fbx �̰Ÿ� �ٿ��ش�"
	std::string Strtemp = ".fbx";
	std::string FullName = MeshPath + Name + Strtemp;

	ModelData* SaveMesh = new ModelData();

	//�ļ��� ���ؼ� �Ž��� �ε�
	ParserData::Model* temp = EaterParser->LoadModel(FullName, Scale, LoadAnime);

	//�������� TM�� ������Ʈ�� �����о�������� 
	int MeshCount = temp->m_MeshList.size();
	for (int i = 0; i < MeshCount; i++)
	{
		//����Ʈ�� �Ž� ����
		ParserData::Mesh* mesh = temp->m_MeshList[i];

		//�ֻ��� �Ž��� �ƴ϶�� �ƹ��͵� ��������
		if (mesh->m_TopNode != true) { continue; }

		//�Ž��̰� ��Ű�� ������Ʈ���
		if (mesh->m_IsBone == false && mesh->m_IsSkinningObject == true)
		{
			//���� ������ ������ �о�� ������ �ؿ��� 
			SaveMesh->BoneOffsetList = &mesh->m_BoneTMList;
			SaveMesh->BoneList = &mesh->m_BoneMeshList;
		}

		//�Ž��̰� ž ������Ʈ���
		if (mesh->m_IsBone == false && mesh->m_TopNode)
		{
			LoadMeshData* TopMesh = CreateMeshObjeect(mesh);
			SaveMesh->TopMeshList.push_back(TopMesh);
		}
	}

	//�о�� BoneOffset �� ����Ʈ�� ������� �����ϰ� �������� ������ �ֻ������̾ƿ´�
	LoadMeshData* TopBone = CreateBoneObjeect(SaveMesh);
	if (TopBone != nullptr) { SaveMesh->TopBoneList.push_back(TopBone); }




	//�ֻ��� ������Ʈ�� ����Ʈ�� �־��ش�
	ModelList.insert({ Name,SaveMesh });
}

void LoadManager::LoadTexture(std::string Name)
{
	std::string TextureName = TexturePath + Name;


	TextureBuffer* Tbuffer = GEngine->CreateTextureBuffer(TextureName);
	
	if (Tbuffer == nullptr || Tbuffer->TextureBufferPointer == nullptr)
	{
		DebugManager::Print(TextureName, 0, 0, DebugManager::MSG_TYPE::MSG_LOAD, true);
	}
	else
	{
		//�̸��� .dds , .png �� ���� �����Ѵ�
		std::string::size_type End = Name.rfind('.');
		std::string::size_type start = 0;
		std::string SaveName = Name.substr(start, End);

		TextureList.insert({ SaveName,Tbuffer });
	}
}

void LoadManager::LoadPrefap(std::string Name)
{
	///���߿� ����
}

void LoadManager::LoadMeshPath(std::string mPath)
{
	//�� ��� �Է�
	MeshPath = mPath;
}

void LoadManager::LoadTexturePath(std::string mPath)
{
	//�ؽ��� ��� �Է�
	TexturePath = mPath;
	ModelParser::SetTextureRoute(TexturePath);
}

void LoadManager::DeleteMesh(std::string mMeshName)
{
	//�޸𸮿� �Ҵ��� �Ž��� ������ ������Ŵ
	std::map<std::string, ModelData*>::iterator temp = ModelList.find(mMeshName);
	if (temp == ModelList.end())
	{
		return;
	}
	else
	{
		ModelList.erase(mMeshName);
	}
}

void LoadManager::DeleteMeshAll()
{
	ModelList.clear();
}

LoadMeshData* LoadManager::CreateMeshObjeect(ParserData::Mesh* mesh)
{
	//�������� �ޱ�
	LoadMeshData* box = new LoadMeshData();

	SetData(box, mesh);

	//���۰� �о����
	box->IB = GEngine->CreateIndexBuffer(mesh);
	box->IB->Count = (int)mesh->m_IndexList.size() * 3;

	box->VB = GEngine->CreateVertexBuffer(mesh);
	box->VB->Count = (int)mesh->m_VertexList.size();

	//�ڽİ�ü�� �ִٸ� �����о��
	int ChildCount = mesh->m_ChildList.size();
	for (int i = 0; i < ChildCount; i++)
	{
		LoadMeshData* temp = CreateMeshObjeect(mesh->m_ChildList[i]);
		box->Child.push_back(temp);
		temp->Parent = box;
	}

	return box;
}

LoadMeshData* LoadManager::CreateBoneObjeect(ModelData* SaveData)
{
	///�о�� �� ����Ʈ�� ���� �����ϰ� BoneOffset�� ��������
	if (SaveData->BoneList == nullptr) { return nullptr; }

	std::vector<LoadMeshData*> TempBoneList;
	//���� ������ŭ ���� ������Ŵ
	int boneCount = SaveData->BoneList->size();
	for (int i = 0; i < boneCount; i++)
	{
		//�Ѱ��� ��������
		ParserData::Mesh* mesh = (*SaveData->BoneList)[i];
		LoadMeshData* data = new LoadMeshData();
		SetData(data, mesh);
		data->BoneOffset = &(*SaveData->BoneOffsetList)[i];
		TempBoneList.push_back(data);
	}

	///������ ������ �θ��ڽİ���� ��ũ������
	LoadMeshData* TOP_BONE = nullptr;
	for (int i = 0; i < boneCount; i++)
	{
		for (int j = 0; j < boneCount; j++)
		{
			//�ڱ� �ڽŰ��� �˻������ʴ´�
			if (TempBoneList[i] == TempBoneList[j]) { continue; }

			LoadMeshData* Front = TempBoneList[i];
			LoadMeshData* Back = TempBoneList[j];

			//���� �θ��̸��� �ڱ��ڽ��� �̸��϶� ����
			if (Front->ParentName == Back->Name)
			{
				Front->Parent = Back;
				Back->Child.push_back(Front);
			}

			if (Front->Top_Object == true)
			{
				TOP_BONE = Front;
			}
		}
	}

	///��� ����� ���¿��� �ֻ��� ������Ʈ�� �������ش�
	return TOP_BONE;
}

void LoadManager::SetData(LoadMeshData* MeshData, ParserData::Mesh* LoadData)
{
	MeshData->Name = LoadData->m_NodeName;
	MeshData->ParentName = LoadData->m_ParentName;
	MeshData->Top_Object = LoadData->m_TopNode;
	MeshData->Bone_Object = LoadData->m_IsBone;
	MeshData->Skinning_Object = LoadData->m_IsSkinningObject;
	MeshData->BoneIndex = LoadData->m_BoneIndex;

	//���� ������ �׳� �о��
	MeshData->Animation = LoadData->m_Animation;
	MeshData->Material = LoadData->m_MaterialData;
	
	// Texture Buffer ����..
	CMaterial* mat = LoadData->m_MaterialData;
	if (mat != nullptr)
	{
		if (mat->m_IsDiffuseMap == true)
		{
			MeshData->Diffuse = GEngine->CreateTextureBuffer(mat->m_DiffuseMap->m_BitMap);
		}
		if (mat->m_IsBumpMap == true)
		{
			MeshData->Normal = GEngine->CreateTextureBuffer(mat->m_BumpMap->m_BitMap);
		}
	}

	//��Ʈ���� ���� �ޱ�
	MeshData->WorldTM = &LoadData->m_WorldTM;
	MeshData->LocalTM = &LoadData->m_LocalTM;

	MeshData->BoneOffset;
}











