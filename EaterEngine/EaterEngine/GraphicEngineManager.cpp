#include "GraphicEngineManager.h"
#include "DebugManager.h"
#include "GraphicsEngine.h"
#include "EngineData.h"
#include "ParserData.h"

GraphicEngineManager::GraphicEngineManager()
{
	NowEngine = nullptr;
}

GraphicEngineManager::~GraphicEngineManager()
{
	
}

void GraphicEngineManager::EngineAllInitialize(HWND Hwnd, int WinSizeWidth, int WinSizeHeight)
{
	//모든 엔진을 초기화 시킨다
	std::map<std::string, GraphicEngine*>::iterator it = GEngineList.begin();
	for (it; it != GEngineList.end(); it++) 
	{

		if ((*it).second == nullptr) { continue; }
		(*it).second->Initialize(Hwnd, WinSizeWidth, WinSizeHeight);
	}
}

void GraphicEngineManager::Initialize(HWND Hwnd, int WinSizeWidth, int WinSizeHeight)
{
	if (NowEngine == nullptr)
	{
		DebugManager::Print("선택한 그래픽엔진이 없습니다", DebugManager::MSG_TYPE::MSG_ERROR);
	}
	else
	{
		NowEngine->Initialize(Hwnd, WinSizeWidth, WinSizeHeight);
	}
}

void GraphicEngineManager::Render(std::queue<MeshData*>* meshList, GlobalData* global)
{
	if (NowEngine == nullptr)
	{
		DebugManager::Print("선택한 그래픽엔진이 없습니다", DebugManager::MSG_TYPE::MSG_ERROR);
	}
	else
	{
		NowEngine->Render(meshList, global);
	}
}

Indexbuffer* GraphicEngineManager::CreateIndexBuffer(ParserData::Model* mModel)
{
	return NowEngine->CreateIndexBuffer(mModel);
}

Vertexbuffer* GraphicEngineManager::CreateVertexBuffer(ParserData::Model* mModel)
{
	return NowEngine->CreateVertexBuffer(mModel);
}

TextureBuffer* GraphicEngineManager::CreateTextureBuffer(std::string Name)
{
	return NowEngine->CreateTextureBuffer(Name);
}

void GraphicEngineManager::OnReSize(float Change_Width, float Change_Height)
{
	NowEngine->OnReSize(Change_Width, Change_Height);
}

void GraphicEngineManager::ChoiceEngine(std::string Name)
{
	if (GEngineList.find(Name) == GEngineList.end())
	{
		DebugManager::Print("그래픽엔진을 찾지못했습니다", DebugManager::MSG_TYPE::MSG_ERROR);
	}
	else
	{
		std::string temp = "선택된 그래픽 엔진 :" + Name;
		DebugManager::Print(temp, DebugManager::MSG_TYPE::MSG_ERROR);
		NowEngine = GEngineList[Name];
	}
}

void GraphicEngineManager::Delete()
{
	//그래픽 엔진을 종료 시킨다
	std::map<std::string, GraphicEngine*>::iterator it = GEngineList.begin();
	for (it; it != GEngineList.end(); it++)
	{

		if ((*it).second == nullptr) { continue; }
		(*it).second->Delete();
	}
	GEngineList.clear();
}
