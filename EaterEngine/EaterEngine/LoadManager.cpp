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
	//그래픽 엔진 받아오기
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
	// "../ 이거와 .fbx 이거를 붙여준다"
	std::string Strtemp = ".fbx";
	std::string FullName = MeshPath + Name + Strtemp;

	//파서를 통해서 매쉬를 로드
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
		std::string strtemp = FullName + "[인덱스버퍼]";
		DebugManager::Print(strtemp, DebugManager::MSG_TYPE::MSG_LOAD, true);
		return;
	}
	else if (data->VB == nullptr) 
	{
		std::string strtemp = FullName + "[버텍스버퍼]";
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
		std::string strTemp = "텍스쳐를 로드합니다 :" + Name;
		DebugManager::Print(strTemp, DebugManager::MSG_TYPE::MSG_LOAD);
		TextureList.insert({Name,Tbuffer});
	}
}

void LoadManager::LoadPrefap(std::string Name)
{
	///나중에 구현
}

void LoadManager::LoadMeshPath(std::string mPath)
{
	//모델 경로 입력
	MeshPath = mPath;
}

void LoadManager::LoadTexturePath(std::string mPath)
{
	//텍스쳐 경로 입력
	TexturePath = mPath;
}

void LoadManager::DeleteMesh(std::string mMeshName)
{
	//메모리에 할당한 매쉬의 정보를 삭제시킴

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






