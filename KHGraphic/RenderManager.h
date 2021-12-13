#pragma once
#include "RenderManagerBase.h"

class RenderPassBase;
class ShadowPass;
class DeferredPass;
class LightPass;
class SSAOPass;
class RenderManager : public IRenderManager
{
public:
	RenderManager(ID3D11Graphic* graphic, IGraphicResourceFactory* factory, IGraphicResourceManager* resource, IShaderManager* shader);
	~RenderManager();

public:
	void Initialize(int width, int height) override;
	void Release() override;

	void Render(std::queue<MeshData*>* meshList, GlobalData* global) override;
	void ShadowRender(std::queue<MeshData*>* meshList, GlobalData* global) override; 
	void SSAORender(GlobalData* global) override;
	void UIRender(std::queue<MeshData*>* meshList, GlobalData* global) override;
	void LightRender(GlobalData* global) override;
	void EndRender() override;

	void OnResize(int width, int height) override;

private:
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain;

private:
	std::vector<RenderPassBase*> m_RenderPassList;

	DeferredPass* m_Deferred;
	LightPass* m_Light;
	ShadowPass* m_Shadow;
	SSAOPass* m_SSAO;
};
