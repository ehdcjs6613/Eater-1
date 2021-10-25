#include "MeshFilter.h"
#include "DebugManager.h"
#include "LoadManager.h"
#include "DH3DEngine.h"
#include "KHParser.h"

extern LoadManager* gLoadManager;

HWND MeshFilter::hWnd;

MeshFilter::MeshFilter()
{
	MeshFilterData = nullptr;
	MeshName = "";
}

MeshFilter::~MeshFilter()
{

}

void MeshFilter::Awake()
{
	DebugManager::GM()->Print("MeshFilter Awake 함수 실행 \n");
	//MeshData 불러오기
	MeshFilterData = gLoadManager->GetMesh(MeshName);
	if (MeshFilterData == nullptr)
	{
		DebugManager::GM()->Print("Mesh불러오기 실패 \n");
	}
	pTest_Engine = new DH3DEngine();


	/// <summary>
	/// 테스트용 원래 여기있으면 안됨...
	/// </summary>

	pTest_Engine = new DH3DEngine();
	pTest_Engine->Initialize(hWnd, 1920, 1080);
	pTest_Engine->SetDebug(true);

	pTest_OFD = new OneFrameData;
	pTest_OFD->View_Matrix = DirectX::SimpleMath::Matrix
	(
		0.993068516, -0.0513942279, -0.105705619, 0.f,
		1.49011612e-08, 0.899335980, -0.437258303, 0.f,
		0.117537417, 0.434227467, 0.893102169, 0.00000000,
		-0.991111338, -0.756038189, 2.71574593, 1.f
	);
	pTest_OFD->Projection_Matrix = DirectX::SimpleMath::Matrix
	(
		1.35799503, 0.f, 0.f, 0.f,
		0.f, 2.41421342, 0.f, 0.f,
		0.f, 0.f, 1.00000012, 1.f,
		0.f, 0.f, -0.000100000012, 0.f
	);
	// 테스트용 카메라 위치
	pTest_OFD->World_Eye_Position = DirectX::SimpleMath::Vector3(10.f, 8.f, -10.f);
	pTest_OFD->Main_Position = DirectX::SimpleMath::Vector3(0.f, 0.f, 0.f);

	pTest_SRD = new SharedRenderData;

	pTest_Mesh = new DHParser::Mesh;
	pTest_Mesh->Texture_Key = 0;

	pTest_Mesh->Vcount = MeshFilterData->m_MeshList[0]->m_Final_Vertex.size();
	pTest_Mesh->Tcount = MeshFilterData->m_MeshList[0]->m_MeshFace.size();

	pTest_Mesh->Local_TM = MeshFilterData->m_MeshList[0]->m_WorldTM;
	pTest_Mesh->World_TM = pTest_Mesh->Local_TM;


	
	//버텍스 정보 넘겨주기
	for (int i = 0; i < pTest_Mesh->Vcount; i++)
	{
		float x = MeshFilterData->m_MeshList[0]->m_Final_Vertex[i]->m_Pos.x;
		float y = MeshFilterData->m_MeshList[0]->m_Final_Vertex[i]->m_Pos.y;
		float z = MeshFilterData->m_MeshList[0]->m_Final_Vertex[i]->m_Pos.z;

		float N_x = MeshFilterData->m_MeshList[0]->m_Final_Vertex[i]->m_Normal.x;
		float N_y = MeshFilterData->m_MeshList[0]->m_Final_Vertex[i]->m_Normal.y;
		float N_z = MeshFilterData->m_MeshList[0]->m_Final_Vertex[i]->m_Normal.z;


		DHParser::Vertex m_TestVertex;
		m_TestVertex.Pos = DirectX::SimpleMath::Vector3(x, y, z);
		m_TestVertex.Normal = DirectX::SimpleMath::Vector3(N_x, N_y, N_z);

		pTest_Mesh->Optimize_Vertex.push_back(m_TestVertex);
	}


	for (int j = 0; j < MeshFilterData->m_MeshList[0]->m_MeshFace.size(); j++)
	{
		int x = MeshFilterData->m_MeshList[0]->m_MeshFace[j]->m_VertexIndex[0];
		int y =MeshFilterData->m_MeshList[0]->m_MeshFace[j]->m_VertexIndex[1];
		int z =MeshFilterData->m_MeshList[0]->m_MeshFace[j]->m_VertexIndex[2];


		pTest_Mesh->Optimize_Index.push_back(x);
		pTest_Mesh->Optimize_Index.push_back(y);
		pTest_Mesh->Optimize_Index.push_back(z);
	}


	pTest_SRD->Render_Mesh_List = new std::vector<DHParser::Mesh>;
	pTest_SRD->Render_Mesh_List->push_back(*pTest_Mesh);
}

void MeshFilter::Start()
{
	///일단 동혁이 랜더링으로 값을 넘겨준다
	///테스트용으로 지금은 값을 맞춰서 넘겨주지만
	///실제로 내꺼나 규황이나 우진이꺼를붙일땐 이렇게하면안됨






}

void MeshFilter::Update()
{
	DebugManager::GM()->Print("MeshFilter Update 함수 실행 \n");

	
	/// <summary>
	/// 테스트용 원래 여기있으면 안됨...
	/// </summary>
	pTest_Engine->BeginDraw();
	
	pTest_Engine->TextDraw({ (int)(1920 - 350), 10 }, 500, 0, 1, 0, 1, 30, L"카메라 모드 변경 : C");

	pTest_Engine->RenderDraw(pTest_OFD, pTest_SRD);

	pTest_Engine->EndDraw();
}

void MeshFilter::SetMeshName(std::string mMeshName)
{
	MeshName = mMeshName;
}

EATER_ENGINEDLL void MeshFilter::SetBuffer(FBXModel* Model)
{
	MeshFilterData = Model;
}




