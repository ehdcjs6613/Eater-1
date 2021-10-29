#include "LoadManager.h"
#include "DebugManager.h"
#include "EngineData.h"
#include "GraphicsEngine.h"
#include "ModelParser.h"
#include "Camera.h"
#include "DH3DEngine.h"
#include "atlstr.h"


std::map<std::string, LoadData*> LoadManager::MeshList;
LoadManager::LoadManager()
{
	//EATER_Parser = nullptr;
}

LoadManager::~LoadManager()
{

}

void LoadManager::Initialize(GraphicEngine* Graphic)
{
	//�׷��� ���� �޾ƿ���
	GEngine = Graphic;
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
		std::string temp = "[Find]���� ������ �Ž��� ã�����߽��ϴ� ->" + Name;
		return nullptr;
	}

	return temp->second;
}

void LoadManager::GetTexture(std::string Name)
{

}

void LoadManager::LoadMesh( std::string Name, bool Scale, bool LoadAnime)
{
	// "../ �̰ſ� .fbx �̰Ÿ� �ٿ��ش�"
	std::string Strtemp = ".fbx";
	std::string FullName = MeshPath + Name + Strtemp;


	//�ļ��� ���ؼ� �Ž��� �ε�
	 ParserData::Model* temp = EaterParser->LoadModel(FullName,Scale,LoadAnime);
	
	 ///�׽�Ʈ��
	 ////////////////////////////////////////////////////////////////////////////////////
	 //�ε��� �����͸� �׷��ȿ������� �Ѱܼ� �ε������۳� �������۵��� �����ϰ� ����Ʈ�� �־��ش�
	 Test_DHData(temp, Name);
	 //////////////////////////////////////////////////////////////////////////////////////
	


	 //�׷��� ������ �ٰԵǸ��̰ɷ�
	 //void CreateBuffer(ParserData::Model * mesh);
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
		std::string temp = "[Delete]���� ������ �Ž��� ã�����߽��ϴ� ->" + mMeshName;
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
	///������ �׽�Ʈ�ϱ����� �����̵����ͷ� �����Ų��
	pTest_SRD = new SharedRenderData();
	pTest_Mesh = new DHParser::Mesh;
	
	// �׽�Ʈ�� ī�޶� ��ġ



	pTest_Mesh->Texture_Key = 0;
	pTest_Mesh->Vcount = mModel->m_MeshList[0]->m_VertexList.size();
	pTest_Mesh->Tcount = mModel->m_MeshList[0]->m_IndexList.size();
	pTest_Mesh->Local_TM = mModel->m_MeshList[0]->m_WorldTM;
	pTest_Mesh->World_TM = pTest_Mesh->Local_TM;


	//���ؽ� �������
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
	std::string t = "ABCD";
	texture->Texture_Path = t.c_str();
	pTest_SRD->Ambient_Texture.insert({0,texture });

	
	//�ε��� ���ۿ� ���ؽ� ���۸� �������..
	DHEngine->CreateIndexBuffer(pTest_Mesh);
	DHEngine->CreateVertexBuffer(pTest_Mesh);
	DHEngine->SetTextureSRV(pTest_SRD);
	

	//�̰��� ���� ���Ǳ���ü�� �°� �ٽú���..
	LoadData* temp = new LoadData();
	temp->IB = new Indexbuffer();
	temp->VB = new Vertexbuffer();

	temp->IB->IndexBufferPointer = pTest_Mesh->Index_Buffer;
	temp->VB->VertexbufferPointer = pTest_Mesh->Vertex_Buffer;


	temp->indexCount = mModel->m_MeshList[0]->m_IndexList.size();
	temp->vertexCount = mModel->m_MeshList[0]->m_VertexList.size();

	
	
	//�׸��� ����...
	MeshList.insert({ Name ,temp });

	delete pTest_Mesh;
}







