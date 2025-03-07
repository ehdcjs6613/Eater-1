#pragma once
#include "GraphicsEngine.h"
#include "GraphicDLL.h"

interface IRenderManager;
interface IGraphicResourceManager;
interface IGraphicResourceFactory;

class KHGraphic : public GraphicEngine
{
public:
	GRAPHIC_DLL KHGraphic();
	~KHGraphic();

public:
	GRAPHIC_DLL void Initialize(HWND hwnd, int screenWidth, int screenHeight) override;

	GRAPHIC_DLL void Render(std::queue<MeshData*>* meshList, GlobalData* global) override;
	GRAPHIC_DLL void ShadowRender(std::queue<MeshData*>* meshList, GlobalData* global) override;
	GRAPHIC_DLL void SSAORender() override;
	GRAPHIC_DLL void UIRender(std::queue<MeshData*>* meshList, GlobalData* global) override;
	GRAPHIC_DLL void OnReSize(int screenWidth, int screenheight) override;
	GRAPHIC_DLL void Delete() override;

	GRAPHIC_DLL Indexbuffer* CreateIndexBuffer(ParserData::Mesh* mesh) override;
	GRAPHIC_DLL Vertexbuffer* CreateVertexBuffer(ParserData::Mesh* mesh) override;
	GRAPHIC_DLL TextureBuffer* CreateTextureBuffer(std::string path) override;

	GRAPHIC_DLL void SetViewPort(void* VPT, int Change_Width, int Change_Height) override;
	GRAPHIC_DLL void SetDevice(void* Devie, void* DevieContext) override;
private:
	IGraphicResourceFactory* m_ResourceFactory;

	IRenderManager* m_RenderManager;
};

