#include "GraphicEngineManager.h"
#include "DebugManager.h"
#include "GraphicsEngine.h"
#include "EngineData.h"
#include "ParserData.h"
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

void GraphicEngineManager::Initialize(HWND Hwnd, int WinSizeWidth, int WinSizeHeight)
{
	MultiEngine = MultiRenderEngine::Initialize(Hwnd, WinSizeWidth, WinSizeHeight);
 	int size = MultiEngine->SplitWindow(1, 1);
}

void GraphicEngineManager::Render(std::queue<MeshData*>* meshList, GlobalData* global)
{
	MultiEngine->Render(meshList, global);
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
	//인덱스버퍼 생성
	return MultiEngine->CreateIndexBuffer(mModel);
}

Vertexbuffer* GraphicEngineManager::CreateVertexBuffer(ParserData::Mesh* mModel)
{
	//버텍스 버퍼 생성
	return MultiEngine->CreateVertexBuffer(mModel);
}

TextureBuffer* GraphicEngineManager::CreateTextureBuffer(std::string Name)
{
	//텍스쳐 생성
	return NowEngine->CreateTextureBuffer(Name);
}

void GraphicEngineManager::OnReSize(int Change_Width, int Change_Height)
{
	//사이즈 변경
	//NowEngine->OnReSize(Change_Width, Change_Height);
}

void GraphicEngineManager::PushEngine(GraphicEngine* Engine, std::string Name)
{
	MultiEngine->RegisterRenderer(Engine, Name);
}
