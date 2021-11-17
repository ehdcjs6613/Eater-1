#include "LoadManager.h"
#include "DebugManager.h"
#include "EngineData.h"
#include "GraphicsEngine.h"
#include "ModelParser.h"
#include "GraphicEngineManager.h"



std::map<std::string, ModelData*> LoadManager::ModelList;
std::map<std::string, TextureBuffer*> LoadManager::TextureList;
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
			SaveMesh->BoneOffsetList = &mesh->m_BoneTMList;
			SaveMesh->BoneList = &mesh->m_BoneMeshList;
		}
	}


	for (int i = 0; i < MeshCount; i++)
	{
		//����Ʈ�� �Ž� ����
		ParserData::Mesh* mesh = temp->m_MeshList[i];
		//�ֻ��� �Ž��� �ƴ϶�� �ƹ��͵� ��������
		if (mesh->m_TopNode != true) { continue; }


		if (mesh->m_IsBone == true)
		{
			LoadMeshData* temp = CreateBoneObjeect(mesh, SaveMesh);
			SaveMesh->TopBoneList.push_back(temp);
		}
		else
		{
			LoadMeshData* temp = CreateMeshObjeect(mesh);
			SaveMesh->TopMeshList.push_back(temp);
		}
	}


	//�ֻ��� ������Ʈ�� ����Ʈ�� �־��ش�
	ModelList.insert({ Name,SaveMesh });
}

void LoadManager::LoadTexture(std::string Name)
{
	std::string TextureName = TexturePath + Name + ".dds";
	TextureBuffer* Tbuffer = GEngine->CreateTextureBuffer(TextureName);

	if (Tbuffer == nullptr || Tbuffer->TextureBufferPointer == nullptr)
	{
		DebugManager::Print(TextureName, 0, 0, DebugManager::MSG_TYPE::MSG_LOAD, true);
	}
	else
	{
		std::string strTemp = "�ؽ��ĸ� �ε��մϴ� :" + Name;
		DebugManager::Print(strTemp, 0, 0, DebugManager::MSG_TYPE::MSG_LOAD);
		TextureList.insert({ Name,Tbuffer });
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

	// Texture Buffer ����..
	CMaterial* mat = mesh->m_MaterialData;

	if (mat)
	{
		if (mat->m_IsDiffuseMap)
		{
			box->Diffuse = GEngine->CreateTextureBuffer(mat->m_DiffuseMap->m_BitMap);
		}
		if (mat->m_IsBumpMap)
		{
			box->Normal = GEngine->CreateTextureBuffer(mat->m_BumpMap->m_BitMap);
		}
	}

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

LoadMeshData* LoadManager::CreateBoneObjeect(ParserData::Mesh* mesh, ModelData* SaveData)
{
	LoadMeshData* box = nullptr;
	int size = SaveData->BoneList->size();

	//������Ʈ�� �����Ͱ�������������� ���������ʴ´�
	for (int i = 0; i < size; i++)
	{
		if (mesh == (*SaveData->BoneList)[i])
		{
			//�������� �ޱ�
			box = new LoadMeshData();
			box->BoneNumber = (*SaveData->BoneList)[i];
			box->BoneOffset = &(*SaveData->BoneOffsetList)[i];

			SetData(box, mesh);

			//�ڽİ�ü�� �ִٸ� �����о��
			int ChildCount = mesh->m_ChildList.size();
			for (int i = 0; i < ChildCount; i++)
			{
				LoadMeshData* temp = CreateBoneObjeect(mesh->m_ChildList[i], SaveData);

				if (temp != nullptr)
				{
					box->Child.push_back(temp);
					temp->Parent = box;
				}
			}
		}
	}

	return box;
}

void LoadManager::SetData(LoadMeshData* MeshData, ParserData::Mesh* LoadData)
{
	MeshData->Name = LoadData->m_NodeName;
	MeshData->ParentName = LoadData->m_ParentName;
	MeshData->Top_Object = LoadData->m_TopNode;
	MeshData->Bone_Object = LoadData->m_IsBone;
	MeshData->Skinning_Object = LoadData->m_IsSkinningObject;

	//���� ������ �׳� �о��
	MeshData->Animation = LoadData->m_Animation;
	MeshData->Material = LoadData->m_MaterialData;

	//��Ʈ���� ���� �ޱ�
	MeshData->WorldTM = &LoadData->m_WorldTM;
	MeshData->LocalTM = &LoadData->m_LocalTM;

	MeshData->BoneOffset;
}











