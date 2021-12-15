#include "DirectDefine.h"
#include "RenderPassBase.h"
#include "ShaderBase.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "GraphicState.h"
#include "GraphicView.h"
#include "Texture2D.h"
#include "DepthStencil.h"
#include "RenderTarget.h"
#include "VertexDefine.h"
#include "BufferData.h"
#include "EngineData.h"
#include "LightPass.h"

#include "MathDefine.h"
#include "ResourceFactoryBase.h"
#include "ResourceManagerBase.h"
#include "ShaderManagerBase.h"
#include "ConstantBufferDefine.h"
#include "ShaderResourceBufferDefine.h"
#include "DepthStencilStateDefine.h"
#include "DepthStencilViewDefine.h"
#include "RenderTargetDefine.h"
#include "ViewPortDefine.h"
#include "BufferDataDefine.h"

LightPass::LightPass()
{

}

LightPass::~LightPass()
{

}

void LightPass::Create(int width, int height)
{
}

void LightPass::Start(int width, int height)
{
	// Shader ����..
	m_LightVS = g_Shader->GetShader("Light_VS");
	m_LightPS = g_Shader->GetShader("Light_PS_Option0");

	// Buffer ����..
	m_ScreenBuffer = g_Resource->GetBuffer<BD_FullScreen>();

	// BackBuffer ����..
	m_BackBuffer = g_Resource->GetMainRenderTarget();
	m_BackBufferRTV = m_BackBuffer->GetRTV()->Get();

	// ViewPort ����..
	m_ScreenViewport = g_Resource->GetViewPort<VP_FullScreen>()->Get();

	// DepthStencilView ����..
	m_DepthStencilView = g_Resource->GetDepthStencil<DS_Defalt>()->GetDSV()->Get();

	// Multi RenderTarget ����..
	m_AlbedoRT = g_Resource->GetRenderTarget<RT_Deffered_Albedo>();
	m_NormalRT = g_Resource->GetRenderTarget<RT_Deffered_Normal>();
	m_PositionRT = g_Resource->GetRenderTarget<RT_Deffered_Position>();
	m_ShadowRT = g_Resource->GetRenderTarget<RT_Deffered_Shadow>();

	// ShaderResource ����..
	m_LightPS->SetShaderResourceView<gAlbedoRT>(m_AlbedoRT->GetSRV()->Get());
	m_LightPS->SetShaderResourceView<gNormalRT>(m_NormalRT->GetSRV()->Get());
	m_LightPS->SetShaderResourceView<gPositionRT>(m_PositionRT->GetSRV()->Get());
	m_LightPS->SetShaderResourceView<gShadowRT>(m_ShadowRT->GetSRV()->Get());

	// Sub Resource ����..
	ShaderResourceView* ssaoSRV = g_Resource->GetShaderResourceView<RT_SSAO_Main>();
	ShaderResourceView* shadowSRV = g_Resource->GetShaderResourceView<DS_Shadow>();

	// ShaderResource ����..
	m_LightPS->SetShaderResourceView<gShadowMap>(shadowSRV->Get());
	m_LightPS->SetShaderResourceView<gSsaoMap>(ssaoSRV->Get());
}

void LightPass::OnResize(int width, int height)
{
	// BackBuffer RenderTargetView �缳��..
	m_BackBufferRTV = m_BackBuffer->GetRTV()->Get();
	
	// DepthStencilView �缳��..
	m_DepthStencilView = g_Resource->GetDepthStencil<DS_Defalt>()->GetDSV()->Get();
	
	// ShaderResource �缳��..
	m_LightPS->SetShaderResourceView<gAlbedoRT>(m_AlbedoRT->GetSRV()->Get());
	m_LightPS->SetShaderResourceView<gNormalRT>(m_NormalRT->GetSRV()->Get());
	m_LightPS->SetShaderResourceView<gPositionRT>(m_PositionRT->GetSRV()->Get());
	m_LightPS->SetShaderResourceView<gShadowRT>(m_ShadowRT->GetSRV()->Get());

	// Sub Resource �缳��..
	ShaderResourceView* ssaoSRV = g_Resource->GetShaderResourceView<RT_SSAO_Main>();
	ShaderResourceView* shadowSRV = g_Resource->GetShaderResourceView<DS_Shadow>();

	m_LightPS->SetShaderResourceView<gShadowMap>(m_ShadowRT->GetSRV()->Get());
	m_LightPS->SetShaderResourceView<gSsaoMap>(ssaoSRV->Get());
}

void LightPass::Release()
{

}

void LightPass::SetOption(const char* shaderName)
{
	m_LightPS = g_Shader->GetShader(shaderName);
}

void LightPass::Reset()
{
	g_Context->ClearRenderTargetView(m_BackBufferRTV, reinterpret_cast<const float*>(&DXColors::DeepDarkGray));

	// ShaderResource �缳��..
	m_LightPS->SetShaderResourceView<gAlbedoRT>(m_AlbedoRT->GetSRV()->Get());
	m_LightPS->SetShaderResourceView<gNormalRT>(m_NormalRT->GetSRV()->Get());
	m_LightPS->SetShaderResourceView<gPositionRT>(m_PositionRT->GetSRV()->Get());
	m_LightPS->SetShaderResourceView<gShadowRT>(m_ShadowRT->GetSRV()->Get());

	// Sub Resource �缳��..
	ShaderResourceView* ssaoSRV = g_Resource->GetShaderResourceView<RT_SSAO_Main>();
	ShaderResourceView* shadowSRV = g_Resource->GetShaderResourceView<DS_Shadow>();

	m_LightPS->SetShaderResourceView<gShadowMap>(m_ShadowRT->GetSRV()->Get());
	m_LightPS->SetShaderResourceView<gSsaoMap>(ssaoSRV->Get());
}

void LightPass::BeginRender()
{
	g_Context->OMSetRenderTargets(1, &m_BackBufferRTV, m_DepthStencilView);
	g_Context->ClearRenderTargetView(m_BackBufferRTV, reinterpret_cast<const float*>(&DXColors::DeepDarkGray));
	g_Context->RSSetViewports(1, m_ScreenViewport);
}

void LightPass::Render(GlobalData* global)
{
	Matrix view = *global->mCamView;
	Matrix proj = *global->mCamProj;
	LightData* lightData = global->mLightData;
	
	CB_Light lightBuf;
	lightBuf.gPointLightCount = lightData->gPointLightCount;
	lightBuf.gSpotLightCount = lightData->gSpotLightCount;

	lightBuf.gDirLights = *lightData->DirLights[0];

	for (UINT p = 0; p < lightBuf.gPointLightCount; p++)
	{
		lightBuf.gPointLights[p] = *lightData->PointLights[p];
	}
	for (UINT s = 0; s < lightBuf.gSpotLightCount; s++)
	{
		lightBuf.gSpotLights[s] = *lightData->SpotLights[s];
	}

	for (UINT m = 0; m < global->mMatData.size(); m++)
	{
		lightBuf.gMaterials[m] = *global->mMatData[m];
	}

	CB_LightSub lightsubBuf;
	lightsubBuf.gEyePosW = *global->mCamPos;
	lightsubBuf.gViewProjTex = view * proj * Matrix(
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 1.0f);

	m_LightPS->SetConstantBuffer(lightBuf);
	m_LightPS->SetConstantBuffer(lightsubBuf);

	// Vertex Shader Update..
	m_LightVS->Update();

	// Pixel Shader Update..
	m_LightPS->Update();

	g_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	g_Context->IASetVertexBuffers(0, 1, m_ScreenBuffer->VB.GetAddressOf(), &m_ScreenBuffer->Stride, &m_ScreenBuffer->Offset);
	g_Context->IASetIndexBuffer(m_ScreenBuffer->IB.Get(), DXGI_FORMAT_R32_UINT, 0);

	g_Context->DrawIndexed(m_ScreenBuffer->IndexCount, 0, 0);
}
