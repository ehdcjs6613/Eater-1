#include "GraphicEngineManager.h"
#include "DebugManager.h"
#include "GraphicsEngine.h"
#include "EngineData.h"
#include "ParserData.h"
#include "ObjectManager.h"
#include "MultiRenderEngine.h"

GraphicEngineManager::GraphicEngineManager()
{
	NowEngine	= nullptr;
	MultiEngine = nullptr;
}

GraphicEngineManager::~GraphicEngineManager()
{
	

}

void GraphicEngineManager::Update()
{
	

}

void GraphicEngineManager::Initialize(HWND Hwnd, int WinSizeWidth, int WinSizeHeight, ObjectManager* GM)
{
	ObjManager = GM;
	MultiEngine = MultiRenderEngine::Initialize(Hwnd, WinSizeWidth, WinSizeHeight);
 	
}

void GraphicEngineManager::Render(std::queue<MeshData*>* meshList, GlobalData* global)
{
	MultiEngine->BeginRender();
	for (int i = 0; i < MultiEngine->GetWindowCount(); i++)
	{
		ObjManager->CreateRenderQueue();
		MultiEngine->Render(i,ObjManager->GetRenderQueue(), global);
	}
	MultiEngine->EndRender();
}

void GraphicEngineManager::ShadowRender(std::queue<MeshData*>* meshList, GlobalData* global)
{
	if (NowEngine != nullptr)
	{
		NowEngine->ShadowRender(meshList, global);
	}
}

void GraphicEngineManager::SSAORender(std::queue<MeshData*>* meshList, GlobalData* global)
{
	if (NowEngine != nullptr)
	{
		NowEngine->SSAORender();
	}
}

void GraphicEngineManager::UIRender(std::queue<MeshData*>* meshList, GlobalData* global)
{
	if (NowEngine != nullptr)
	{
		NowEngine->UIRender(meshList, global);
	}
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
	return NowEngine->CreateTextureBuffer(Name);
}

void GraphicEngineManager::OnReSize(int Change_Width, int Change_Height)
{
	//������ ����
	//NowEngine->OnReSize(Change_Width, Change_Height);
}

void GraphicEngineManager::PushEngine(int Number, GraphicEngine* Engine, std::string Name)
{
	MultiEngine->RegisterRenderer(Engine, Name);
	MultiEngine->SetRenderer(Number, Name);
}

void GraphicEngineManager::SplitWindow(int X, int Y)
{
	MultiEngine->SplitWindow(X, Y);
}
