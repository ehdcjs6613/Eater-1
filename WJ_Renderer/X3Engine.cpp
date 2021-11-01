#include "OneCompile.h"
#include "DirectXDevice.h"
#include "DirectXDeviceContext.h"
#include "X3Engine.h"

X3Engine::X3Engine() : m_pDevice(nullptr), m_pDeviceContext(nullptr)
{
	m_pDevice		 = new DirectXDevice();
	m_pDeviceContext = new DirectXDeviceContext();
}

X3Engine::~X3Engine()
{
}

void X3Engine::Initialize(HWND _hWnd, int screenWidth, int screenHeight)
{
	m_hWnd		= _hWnd;
	m_iWidth	= screenWidth;
	m_iHeight	= screenHeight;



}

Indexbuffer* X3Engine::CreateIndexBuffer(ParserData::Model* mModel)
{
	return nullptr;
}

Vertexbuffer* X3Engine::CreateVertexBuffer(ParserData::Model* mModel)
{
	return nullptr;
}

void X3Engine::CreateTextureBuffer()
{
}

void X3Engine::OnReSize(float Change_Width, float Change_Height)
{
}

void X3Engine::Render(std::queue<MeshData*>* meshList, GlobalData* global)
{
}
