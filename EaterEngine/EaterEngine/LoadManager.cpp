#include "LoadManager.h"
#include "DebugManager.h"
#include "EngineData.h"
#include "GraphicsEngine.h"
#include "ModelParser.h"
#include "Camera.h"
#include "DH3DEngine.h"
#include "GraphicEngineManager.h"



std::map<std::string, LoadData*> LoadManager::MeshList;
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

void LoadManager::Initialize(DH3DEngine* Graphic)
{
	DHEngine = Graphic;

	EaterParser = ModelParser::Create(ModelParser::FBX);
	EaterParser->Initialize();
}

LoadData* LoadManager::GetMesh(std::string Name)
{
	std::map<std::string, LoadData*>::iterator temp = MeshList.find(Name);
	if (temp == MeshList.end())
	{
		std::string temp = "[Find]다음 내용의 매쉬를 찾지못했습니다 ->" + Name;
		return nullptr;
	}

	return temp->second;
}

void LoadManager::GetTexture(std::string Name)
{
	
}

void LoadManager::LoadMesh( std::string Name, bool Scale, bool LoadAnime)
{
	// "../ 이거와 .fbx 이거를 붙여준다"
	std::string Strtemp = ".fbx";
	std::string FullName = MeshPath + Name + Strtemp;


	//파서를 통해서 매쉬를 로드
	 ParserData::Model* temp = EaterParser->LoadModel(FullName,Scale,LoadAnime);
	

	 LoadData* data = new LoadData();

	 ///테스트용
	 ////////////////////////////////////////////////////////////////////////////////////
	 //로드한 데이터를 그래픽엔진으로 넘겨서 인덱스버퍼나 각종버퍼들을 생성하고 리스트에 넣어준다
	 //Test_DHData(temp, Name);
	 //////////////////////////////////////////////////////////////////////////////////////
	Indexbuffer*	IB = GEngine->CreateIndexBuffer(temp);
	Vertexbuffer*	VB = GEngine->CreateVertexBuffer(temp);

	data->IB = IB;
	data->VB = VB;
	data->indexCount = temp->m_MeshList[0]->m_IndexList.size();
	data->vertexCount = temp->m_MeshList[0]->m_VertexList.size();


	MeshList.insert({Name,data});
}

void LoadManager::LoadTexture(std::string Name)
{
	GEngine->CreateTextureBuffer(Name);
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
		std::string temp = "[Delete]다음 내용의 매쉬를 찾지못했습니다 ->" + mMeshName;
		return;
	}
	MeshList.erase(mMeshName);
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

void LoadManager::Test_DHData(ParserData::Model* mModel,std::string Name)
{
	///랜더링 테스트하기위해 동혁이데이터로 변경시킨다
	pTest_SRD = new SharedRenderData();
	pTest_Mesh = new DHParser::Mesh;
	
	// 테스트용 카메라 위치



	pTest_Mesh->Texture_Key = 0;
	pTest_Mesh->Vcount = mModel->m_MeshList[0]->m_VertexList.size();
	pTest_Mesh->Tcount = mModel->m_MeshList[0]->m_IndexList.size();
	pTest_Mesh->Local_TM = mModel->m_MeshList[0]->m_WorldTM;
	pTest_Mesh->World_TM = pTest_Mesh->Local_TM;


	//버텍스 만들어줌
	for (int i = 0; i < pTest_Mesh->Vcount; i++)
	{
		float x = mModel->m_MeshList[0]->m_VertexList[i]->m_Pos.x;
		float y = mModel->m_MeshList[0]->m_VertexList[i]->m_Pos.y;
		float z = mModel->m_MeshList[0]->m_VertexList[i]->m_Pos.z;

		float N_x = mModel->m_MeshList[0]->m_VertexList[i]->m_Normal.x;
		float N_y = mModel->m_MeshList[0]->m_VertexList[i]->m_Normal.y;
		float N_z = mModel->m_MeshList[0]->m_VertexList[i]->m_Normal.z;

		
		DHParser::Vertex m_TestVertex;
		m_TestVertex.Pos = DirectX::SimpleMath::Vector3(x, y, z);
		m_TestVertex.Normal = DirectX::SimpleMath::Vector3(N_x, N_y, N_z);

		pTest_Mesh->Optimize_Vertex.push_back(m_TestVertex);
	}

	for (int j = 0; j < mModel->m_MeshList[0]->m_IndexList.size(); j++)
	{
		int x = mModel->m_MeshList[0]->m_IndexList[j]->m_Index[0];
		int y = mModel->m_MeshList[0]->m_IndexList[j]->m_Index[1];
		int z = mModel->m_MeshList[0]->m_IndexList[j]->m_Index[2];

		pTest_Mesh->Optimize_Index.push_back(x);
		pTest_Mesh->Optimize_Index.push_back(y);
		pTest_Mesh->Optimize_Index.push_back(z);
	}

	
	



	pTest_SRD->Render_Mesh_List = new std::vector<DHParser::Mesh>;
	pTest_SRD->Render_Mesh_List->push_back(*pTest_Mesh);
	DHRENDER::TexturePathAndSRV* texture = new DHRENDER::TexturePathAndSRV();
	std::wstring t = L"ABCD";
	texture->Texture_Path = t.c_str();
	pTest_SRD->Ambient_Texture.insert({0,texture });

	
	//인덱스 버퍼와 버텍스 버퍼를 만들었다..
	DHEngine->CreateIndexBuffer(pTest_Mesh);
	DHEngine->CreateVertexBuffer(pTest_Mesh);
	DHEngine->SetTextureSRV(pTest_SRD);
	

	//이것을 이제 나의구조체에 맞게 다시변형..
	LoadData* temp = new LoadData();
	temp->IB = new Indexbuffer();
	temp->VB = new Vertexbuffer();

	temp->IB->IndexBufferPointer = pTest_Mesh->Index_Buffer;
	temp->VB->VertexbufferPointer = pTest_Mesh->Vertex_Buffer;


	temp->indexCount = mModel->m_MeshList[0]->m_IndexList.size();
	temp->vertexCount = mModel->m_MeshList[0]->m_VertexList.size();

	
	
	//그리고 저장...
	MeshList.insert({ Name ,temp });

	delete pTest_Mesh;
}







