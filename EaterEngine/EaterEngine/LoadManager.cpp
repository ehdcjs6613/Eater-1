#include "LoadManager.h"
#include "DebugManager.h"
#include "EngineData.h"
#include "GraphicsEngine.h"
#include "ModelParser.h"
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

	LoadData* Data = new LoadData();

	//일단 로드 한 데이터를 순서상관없이 리스트에 담아둔다
	std::vector<ParserData::Bone*> Temp_Bone_List;
	std::vector<ParserData::Mesh*> Temp_Mesh_List;

	
	//파서를 통해서 매쉬를 로드
	ParserData::Model* temp = EaterParser->LoadModel(FullName,Scale,LoadAnime);
	//매쉬 개수
	int MeshCount = (int)temp->m_MeshList.size();
	
	//한개의 매쉬에 대한 데이터를 저장
	for (int i = 0; i < MeshCount; i++)
	{
		ParserData::Mesh* OneMesh = temp->m_MeshList[i];
		//본 매쉬라면

		//OneMesh->m_BoneMeshList[0];
		if (OneMesh->m_IsBone == true)
		{
			//Temp_Bone_List.push_back(OneMesh->m_BoneMeshList)
		}
		else //아니라면 그냥매쉬를
		{
			LoadData* data = new LoadData();
			data = CreateMesh(OneMesh);


			MeshList.insert({ Name,data });
		}
	}


	


	int num = 0;
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

Bone* LoadManager::CreateBone(ParserData::Mesh* mesh)
{
	Bone* bone = new Bone();

	bone->ParentName	= mesh->m_ParentName;
	bone->MyName		= mesh->m_NodeName;
	bone->isTop			= mesh->m_TopNode;


	return bone;
}

LoadData* LoadManager::CreateMesh(ParserData::Mesh* mesh)
{
	LoadData* box = new LoadData();

	//box->ParentName = mesh->m_ParentName;
	//box->MyName		= mesh->m_NodeName;
	//box->isTop		= mesh->m_TopNode;

	//버퍼 넣어줌
	box->IB = GEngine->CreateIndexBuffer(mesh);
	box->VB = GEngine->CreateVertexBuffer(mesh);
	box->IB->Count = (int)mesh->m_IndexList.size() * 3;
	box->VB->Count = (int)mesh->m_VertexList.size();

	if (box->IB == nullptr)
	{
		DebugManager::Print("인덱스 버퍼", DebugManager::MSG_TYPE::MSG_LOAD, true);
		delete box;
		return nullptr;
	}
	else if (box->VB == nullptr)
	{
		DebugManager::Print("버텍스 버퍼", DebugManager::MSG_TYPE::MSG_LOAD, true);
		delete box;
		return nullptr;
	}
	else 
	{
		return box;
	}
}








