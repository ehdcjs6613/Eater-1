#include "GraphicEngineManager.h"
#include "DebugManager.h"
#include "GraphicsEngine.h"
#include "EngineData.h"
#include "ParserData.h"
#include "ObjectManager.h"
#include "MultiRenderEngine.h"

GraphicEngineManager::GraphicEngineManager()
{
	MultiEngine = nullptr;
}

GraphicEngineManager::~GraphicEngineManager()
{
	

}

void GraphicEngineManager::Initialize(HWND Hwnd, int WinSizeWidth, int WinSizeHeight, ObjectManager* GM)
{
	//��Ƽ ���� �ʱ�ȭ
	ObjManager = GM;
	MultiEngine = MultiRenderEngine::Initialize(Hwnd, WinSizeWidth, WinSizeHeight);
}

void GraphicEngineManager::Render(std::queue<MeshData*>* meshList, GlobalData* global)
{
	//��Ƽ ���� ������ ���� 
	MultiEngine->BeginRender();

	//���ø��� ���� ��ŭ ����
	for (int i = 0; i < MultiEngine->GetWindowCount(); i++)
	{
		//�ϳ��� ������ ���������� ReQueue�� ����� ��� �־��ش�
		ObjManager->CreateRenderQueue();
		//�ش� ������ ������
		MultiEngine->Render(i,ObjManager->GetRenderQueue(), global);
	}

	//��Ƽ ���� ������ ����
	MultiEngine->EndRender();
}

void GraphicEngineManager::ShadowRender(std::queue<MeshData*>* meshList, GlobalData* global)
{
	//���ø��� ���� ��ŭ ����
	for (int i = 0; i < MultiEngine->GetWindowCount(); i++)
	{
		//�ϳ��� ������ ���������� ReQueue�� ����� ��� �־��ش�
		ObjManager->CreateRenderQueue();
		//�ش� ������ ������
		MultiEngine->ShadowRender(i, ObjManager->GetRenderQueue(), global);
	}
}

void GraphicEngineManager::SSAORender(std::queue<MeshData*>* meshList, GlobalData* global)
{
	//if (NowEngine != nullptr)
	//{
	//	NowEngine->SSAORender();
	//}
}

void GraphicEngineManager::UIRender(std::queue<MeshData*>* meshList, GlobalData* global)
{
	//if (NowEngine != nullptr)
	//{
	//	NowEngine->UIRender(meshList, global);
	//}
}

Indexbuffer* GraphicEngineManager::CreateIndexBuffer(ParserData::Mesh* mModel)
{
	//�ε������� ����
	return MultiEngine->CreateIndexBuffer(mModel);
}

Vertexbuffer* GraphicEngineManager::CreateVertexBuffer(ParserData::Mesh* mModel)
{
	//���ؽ� ���� ����
	return MultiEngine->CreateVertexBuffer(mModel);
}

TextureBuffer* GraphicEngineManager::CreateTextureBuffer(std::string Name)
{
	//�ؽ��� ����
	return MultiEngine->CreateTextureBuffer(Name);
}

void GraphicEngineManager::OnReSize(int Change_Width, int Change_Height)
{
	//������ ����
	MultiEngine->OnResize(Change_Width, Change_Height);
}

void GraphicEngineManager::PushEngine(int Number, GraphicEngine* Engine, std::string Name)
{
	//������ �о� �־��ְ� ���� �ѹ��� ������ ��Ī �����ش�
	MultiEngine->RegisterRenderer(Engine, Name);
	MultiEngine->SetRenderer(Number, Name);
}

void GraphicEngineManager::SplitWindow(int X, int Y)
{
	//������ ������ŭ ������
	MultiEngine->SplitWindow(X, Y);
}
