#include "LoadManager.h"
#include "DebugManager.h"
#include "EngineData.h"
#include "GraphicsEngine.h"
#include "ModelParser.h"
#include "Camera.h"
#include "GraphicEngineManager.h"



std::map<std::string, LoadData*> LoadManager::MeshList;
std::map<std::string, TextureBuffer*> LoadManager::TextureList;
LoadManager::LoadManager()
{
	GEngine = nullptr;
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

LoadData* LoadManager::GetMesh(std::string Name)
{
	std::map<std::string, LoadData*>::iterator temp = MeshList.find(Name);
	if (temp == MeshList.end())
	{
		DebugManager::Print(Name, DebugManager::MSG_TYPE::MSG_LOAD, true);
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
		DebugManager::Print(Name, DebugManager::MSG_TYPE::MSG_LOAD, true);
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

	//�ļ��� ���ؼ� �Ž��� �ε�
	 ParserData::Model* temp = EaterParser->LoadModel(FullName,Scale,LoadAnime);
	

	LoadData* data = new LoadData();
	Indexbuffer*	IB = GEngine->CreateIndexBuffer(temp);
	Vertexbuffer*	VB = GEngine->CreateVertexBuffer(temp);

	data->IB = IB;
	data->VB = VB;
	data->indexCount = (int)temp->m_MeshList[0]->m_IndexList.size();
	data->vertexCount = (int)temp->m_MeshList[0]->m_VertexList.size();


	if (data->IB == nullptr)
	{
		std::string strtemp = FullName + "[�ε�������]";
		DebugManager::Print(strtemp, DebugManager::MSG_TYPE::MSG_LOAD, true);
		return;
	}
	else if (data->VB == nullptr) 
	{
		std::string strtemp = FullName + "[���ؽ�����]";
		DebugManager::Print(FullName, DebugManager::MSG_TYPE::MSG_LOAD, true);
		return;
	}
	else
	{
		MeshList.insert({Name,data});
	}
}

void LoadManager::LoadTexture(std::string Name)
{
	std::string TextureName = TexturePath + Name + ".dds";
	TextureBuffer* Tbuffer = GEngine->CreateTextureBuffer(TextureName);

	if (Tbuffer == nullptr || Tbuffer->TextureBufferPointer == nullptr) 
	{
		DebugManager::Print(TextureName, DebugManager::MSG_TYPE::MSG_LOAD, true);
	}
	else
	{
		std::string strTemp = "�ؽ��ĸ� �ε��մϴ� :" + Name;
		DebugManager::Print(strTemp, DebugManager::MSG_TYPE::MSG_LOAD);
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

	std::map<std::string, LoadData*>::iterator temp = MeshList.find(mMeshName);
	if (temp == MeshList.end())
	{
		DebugManager::Print(mMeshName, DebugManager::MSG_TYPE::MSG_DELETE,true);
		return;
	}
	else
	{
		DebugManager::Print(mMeshName, DebugManager::MSG_TYPE::MSG_DELETE);
		MeshList.erase(mMeshName);
	}
}

void LoadManager::DeleteMeshAll()
{
	MeshList.clear();
}

void LoadManager::CreateBuffer(ParserData::Model* mesh)
{
	LoadData* data = new LoadData();
	Indexbuffer*	IB		= GEngine->CreateIndexBuffer(mesh);
	Vertexbuffer*	VB		= GEngine->CreateVertexBuffer(mesh);

	data->IB = IB;
	data->VB = VB;
}






