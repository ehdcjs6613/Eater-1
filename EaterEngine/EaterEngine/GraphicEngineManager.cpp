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

void GraphicEngineManager::Update()
{
	if (NowEngine == nullptr)
	{
		DebugManager::Print("������ �׷��ȿ����� �����ϴ�", 80, 0, DebugManager::MSG_TYPE::MSG_ERROR);
	}
	else
	{
		std::string temp = "���õ� �׷��� ���� :" + EngineName;
		DebugManager::Print(temp, 80, 0, DebugManager::MSG_TYPE::MSG_ENGINE);
	}

}

void GraphicEngineManager::EngineAllInitialize(HWND Hwnd, int WinSizeWidth, int WinSizeHeight)
{
	//��� ������ �ʱ�ȭ ��Ų��
	std::map<std::string, GraphicEngine*>::iterator it = GEngineList.begin();
	for (it; it != GEngineList.end(); it++) 
	{

		if ((*it).second == nullptr) { continue; }
		(*it).second->Initialize(Hwnd, WinSizeWidth, WinSizeHeight);
	}
}

void GraphicEngineManager::Initialize(HWND Hwnd, int WinSizeWidth, int WinSizeHeight)
{
	NowEngine->Initialize(Hwnd, WinSizeWidth, WinSizeHeight);
}

void GraphicEngineManager::Render(std::queue<MeshData*>* meshList, GlobalData* global)
{
	//������ ���� ������
	if (NowEngine != nullptr)
	{
		NowEngine->Render(meshList, global);
	}
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
	return NowEngine->CreateIndexBuffer(mModel);
}

Vertexbuffer* GraphicEngineManager::CreateVertexBuffer(ParserData::Mesh* mModel)
{
	//���ؽ� ���� ����
	return NowEngine->CreateVertexBuffer(mModel);
}

TextureBuffer* GraphicEngineManager::CreateTextureBuffer(std::string Name)
{
	//�ؽ��� ����
	return NowEngine->CreateTextureBuffer(Name);
}

void GraphicEngineManager::OnReSize(int Change_Width, int Change_Height)
{
	//������ ����
	NowEngine->OnReSize(Change_Width, Change_Height);
}

void GraphicEngineManager::ChoiceEngine(std::string Name)
{
	//�������� ���� ����
	if (GEngineList.find(Name) == GEngineList.end())
	{
		DebugManager::Print("�׷��ȿ����� ã�����߽��ϴ�", 80, 1, DebugManager::MSG_TYPE::MSG_ERROR);
	}
	else
	{
		EngineName = Name;
		NowEngine = GEngineList[Name];
	}
}

void GraphicEngineManager::Delete()
{
	//�׷��� ������ ���� ��Ų��
	std::map<std::string, GraphicEngine*>::iterator it = GEngineList.begin();
	for (it; it != GEngineList.end(); it++)
	{

		if ((*it).second == nullptr) { continue; }
		(*it).second->Delete();
	}
	GEngineList.clear();
}
