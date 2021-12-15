#include "DirectDefine.h"
#include "D3D11Graphic.h"
#include "KHGraphic.h"

#include "ShaderBase.h"
#include "ShaderManager.h"
#include "ResourceManager.h"
#include "ResourceFactory.h"
#include "RenderManager.h"
#include "RenderPassBase.h"

KHGraphic::KHGraphic()
	:m_ResourceFactory(nullptr), m_RenderManager(nullptr)
{

}

KHGraphic::~KHGraphic()
{

}

void KHGraphic::Initialize(HWND hwnd, int screenWidth, int screenHeight)
{
	// DirectX11 Device ����..
	D3D11Graphic* graphic = new D3D11Graphic(hwnd, screenWidth, screenHeight);

	// Shader Manager ����..
	ShaderManager* shader = new ShaderManager(graphic);

	// Resource Manager ����..
	GraphicResourceManager* resource = new GraphicResourceManager(graphic, shader);

	// Resource Factory ����..
	GraphicResourceFactory* factory = new GraphicResourceFactory(graphic, resource);

	// Render Manager ����..
	RenderManager* renderer = new RenderManager(graphic, factory, resource, shader);

	// Initialize..
	factory->Initialize(screenWidth, screenHeight);
	shader->Initialize();
	resource->Initialize();
	renderer->Initialize(screenWidth, screenHeight);

	// Pointer ����..
	m_ResourceFactory = factory;
	m_RenderManager = renderer;
}

void KHGraphic::BeginRender(UINT& renderOption)
{
	m_RenderManager->BeginRender(renderOption);
}

void KHGraphic::Render(std::queue<MeshData*>* meshList, GlobalData* global)
{
	m_RenderManager->Render(meshList, global);
}

void KHGraphic::ShadowRender(std::queue<MeshData*>* meshList, GlobalData* global)
{
	m_RenderManager->ShadowRender(meshList, global);
}

void KHGraphic::SSAORender(GlobalData* global)
{
	m_RenderManager->SSAORender(global);
}

void KHGraphic::UIRender(std::queue<MeshData*>* meshList, GlobalData* global)
{
	m_RenderManager->UIRender(meshList, global);
}

void KHGraphic::LightRender(GlobalData* global)
{
	m_RenderManager->LightRender(global);
}

void KHGraphic::EndRender()
{
	m_RenderManager->EndRender();
}

void KHGraphic::OnReSize(int screenWidth, int screenheight)
{
	m_RenderManager->OnResize(screenWidth, screenheight);
}

void KHGraphic::Delete()
{

}

Indexbuffer* KHGraphic::CreateIndexBuffer(ParserData::Mesh* mesh)
{
	return m_ResourceFactory->CreateIndexBuffer(mesh);
}

Vertexbuffer* KHGraphic::CreateVertexBuffer(ParserData::Mesh* mesh)
{
	return m_ResourceFactory->CreateVertexBuffer(mesh);
}

Vertexbuffer* KHGraphic::CreateTerrainVertexBuffer(ParserData::Mesh* mesh, std::string maskName)
{
	return m_ResourceFactory->CreateTerrainVertexBuffer(mesh, maskName);
}

TextureBuffer* KHGraphic::CreateTextureBuffer(std::string path)
{
	return m_ResourceFactory->CreateTextureBuffer(path);
}
