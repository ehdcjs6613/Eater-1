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
	//그래픽 엔진 받아오기
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
	// "../ 이거와 .fbx 이거를 붙여준다"
	std::string Strtemp = ".fbx";
	std::string FullName = MeshPath + Name + Strtemp;

	ModelData* SaveMesh = new ModelData();


	//파서를 통해서 매쉬를 로드
	ParserData::Model* temp = EaterParser->LoadModel(FullName,Scale,LoadAnime);
	
	//매쉬 개수
	int MeshCount = (int)temp->m_MeshList.size();
	for (int i = 0; i < MeshCount; i++)
	{
		//리스트에 매쉬 조사
		ParserData::Mesh* mesh = temp->m_MeshList[i];

		//최상위 매쉬가 아니라면 아무것도 하지않음
		if (mesh->m_TopNode != true){continue;}

		//재귀를 호출하면서 매쉬를 생성하고 연결해준다 마지막에 나오는 값은 최상위 오브젝트
		LoadMeshData* data = CreateMesh(mesh);

		//이렇게 나온 서로연결된 매쉬데이터의 최상위 오브젝트가 본인지 아닌지 판별후 리스트에 넣어준다
		if (data->Bone_Object == true)
		{	
			SaveMesh->BoneList.push_back(data);
		}
		else
		{
			SaveMesh->MeshList.push_back(data);
		}
	}

	//최상위 오브젝트의 리스트를 넣어준다
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
		std::string strTemp = "텍스쳐를 로드합니다 :" + Name;
		DebugManager::Print(strTemp, 0, 0, DebugManager::MSG_TYPE::MSG_LOAD);
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


	//이매쉬에 자식객체 개수
	int ChildCount = mesh->m_ChildList.size();

	//계층정보 받기
	box->Name		= mesh->m_NodeName;
	box->ParentName = mesh->m_ParentName;
	box->Top_Object = mesh->m_TopNode;
	box->Bone_Object = mesh->m_IsBone;

	//매트릭스 정보 받기
	box->WorldTM =  &mesh->m_WorldTM;
	box->LocalTM =  &mesh->m_LocalTM;
	
	//메터리얼 정보
	box->Material	= mesh->m_MaterialData;

	
	if(mesh->m_IsBone == true)
	{
		//본이라면 본 정보만 읽어온다
		box->BoneList	= &(mesh->m_BoneMeshList);
		box->BoneTMList = &(mesh->m_BoneTMList);
	}
	else
	{
		//매쉬라면 랜더링할 인덱스버퍼와 버텍스버퍼를 읽어온다
		box->IB = GEngine->CreateIndexBuffer(mesh);
		box->VB = GEngine->CreateVertexBuffer(mesh);
		box->IB->Count = (int)mesh->m_IndexList.size() * 3;
		box->VB->Count = (int)mesh->m_VertexList.size();
	}

	//자식객체가 있다면 정보읽어옴
	for (int i = 0; i < ChildCount; i++)
	{
		LoadMeshData* temp = CreateMesh(mesh->m_ChildList[i]);
		box->Child.push_back(temp);
		temp->Parent = box;
	}

	return box;
}









