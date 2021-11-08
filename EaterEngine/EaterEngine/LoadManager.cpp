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
	GEngine		= nullptr;
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

void LoadManager::LoadMesh( std::string Name, bool Scale, bool LoadAnime)
{
	// "../ �̰ſ� .fbx �̰Ÿ� �ٿ��ش�"
	std::string Strtemp = ".fbx";
	std::string FullName = MeshPath + Name + Strtemp;

	ModelData* SaveMesh = new ModelData();


	//�ļ��� ���ؼ� �Ž��� �ε�
	ParserData::Model* temp = EaterParser->LoadModel(FullName,Scale,LoadAnime);
	
	//�Ž� ����
	int MeshCount = (int)temp->m_MeshList.size();
	for (int i = 0; i < MeshCount; i++)
	{
		//����Ʈ�� �Ž� ����
		ParserData::Mesh* mesh = temp->m_MeshList[i];

		//�ֻ��� �Ž��� �ƴ϶�� �ƹ��͵� ��������
		if (mesh->m_TopNode != true){continue;}

		//��͸� ȣ���ϸ鼭 �Ž��� �����ϰ� �������ش� �������� ������ ���� �ֻ��� ������Ʈ
		LoadMeshData* data = CreateMesh(mesh);

		//�̷��� ���� ���ο���� �Ž��������� �ֻ��� ������Ʈ�� ������ �ƴ��� �Ǻ��� ����Ʈ�� �־��ش�
		if (data->Bone_Object == true)
		{	
			SaveMesh->BoneList.push_back(data);
		}
		else
		{
			SaveMesh->MeshList.push_back(data);
		}
	}

	//�ֻ��� ������Ʈ�� ����Ʈ�� �־��ش�
	ModelList.insert({Name,SaveMesh});
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
		TextureList.insert({Name,Tbuffer});
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
}

void LoadManager::DeleteMesh(std::string mMeshName)
{
	//�޸𸮿� �Ҵ��� �Ž��� ������ ������Ŵ

	std::map<std::string, ModelData*>::iterator temp = ModelList.find(mMeshName);
	if (temp == ModelList.end())
	{
		DebugManager::Print(mMeshName, 0, 0, DebugManager::MSG_TYPE::MSG_DELETE,true);
		return;
	}
	else
	{
		DebugManager::Print(mMeshName, 0, 0, DebugManager::MSG_TYPE::MSG_DELETE);
		ModelList.erase(mMeshName);
	}
}

void LoadManager::DeleteMeshAll()
{
	ModelList.clear();
}


LoadMeshData* LoadManager::CreateMesh(ParserData::Mesh* mesh)
{
	LoadMeshData* box = new LoadMeshData();


	//�̸Ž��� �ڽİ�ü ����
	int ChildCount = mesh->m_ChildList.size();

	//�������� �ޱ�
	box->Name		= mesh->m_NodeName;
	box->ParentName = mesh->m_ParentName;
	box->Top_Object = mesh->m_TopNode;
	box->Bone_Object = mesh->m_IsBone;

	//��Ʈ���� ���� �ޱ�
	box->WorldTM =  &mesh->m_WorldTM;
	box->LocalTM =  &mesh->m_LocalTM;
	
	//���͸��� ����
	box->Material	= mesh->m_MaterialData;

	
	if(mesh->m_IsBone == true)
	{
		//���̶�� �� ������ �о�´�
		box->BoneList	= &(mesh->m_BoneMeshList);
		box->BoneTMList = &(mesh->m_BoneTMList);
	}
	else
	{
		//�Ž���� �������� �ε������ۿ� ���ؽ����۸� �о�´�
		box->IB = GEngine->CreateIndexBuffer(mesh);
		box->VB = GEngine->CreateVertexBuffer(mesh);
		box->IB->Count = (int)mesh->m_IndexList.size() * 3;
		box->VB->Count = (int)mesh->m_VertexList.size();
	}

	//�ڽİ�ü�� �ִٸ� �����о��
	for (int i = 0; i < ChildCount; i++)
	{
		LoadMeshData* temp = CreateMesh(mesh->m_ChildList[i]);
		box->Child.push_back(temp);
		temp->Parent = box;
	}

	return box;
}









