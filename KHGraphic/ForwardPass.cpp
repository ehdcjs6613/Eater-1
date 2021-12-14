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
#include "EngineData.h"
#include "ForwardPass.h"

#include "MathDefine.h"
#include "ResourceFactoryBase.h"
#include "ResourceManagerBase.h"
#include "ShaderManagerBase.h"
#include "ViewPortDefine.h"
#include "ConstantBufferDefine.h"
#include "ShaderResourceBufferDefine.h"
#include "DepthStencilStateDefine.h"
#include "DepthStencilViewDefine.h"
#include "RasterizerStateDefine.h"
#include "BlendStateDefine.h"

#define ALBEDO_MAP 0x00000001
#define NORMAL_MAP 0x00000010

ForwardPass::ForwardPass()
{

}

ForwardPass::~ForwardPass()
{

}

void ForwardPass::Create(int width, int height)
{

}

void ForwardPass::Start(int width, int height)
{
	// Shader ����..
	m_MeshVS = g_Shader->GetShader("Mesh_VS");
	m_SkinVS = g_Shader->GetShader("Skin_VS");
	m_ForwardPS = g_Shader->GetShader("Forward_PS");

	// ViewPort ����..
	m_ScreenViewport = g_Resource->GetViewPort<VP_FullScreen>()->Get();

	// BackBuffer ����..
	m_BackBuffer = g_Resource->GetMainRenderTarget();
	m_BackBufferRTV = m_BackBuffer->GetRTV()->Get();
	m_BackBufferSRV = m_BackBuffer->GetSRV()->Get();

	// DepthStencilView ����..
	m_DepthStencilView = g_Resource->GetDepthStencil<DS_Defalt>()->GetDSV()->Get();

	// Graphic State ����..
	m_DepthStencilState = g_Resource->GetDepthStencilState<DSS_Defalt>()->Get();
	m_RasterizerState = g_Resource->GetRasterizerState<RS_Solid>()->Get();
	m_BlendState = g_Resource->GetBlendState<BS_AlphaBlend>()->Get();

	// Shader Resource ����..
	ShaderResourceView* shadowSRV = g_Resource->GetShaderResourceView<DS_Shadow>();
	m_ForwardPS->SetShaderResourceView<gShadowMap>(shadowSRV->Get());
}

void ForwardPass::OnResize(int width, int height)
{
	// BackBuffer RenderTargetView �缳��..
	m_BackBufferRTV = m_BackBuffer->GetRTV()->Get();

	// BackBuffer ShaderResourceView �缳��..
	m_BackBufferSRV = m_BackBuffer->GetSRV()->Get();

	// DepthStencilView �缳��..
	m_DepthStencilView = g_Resource->GetDepthStencil<DS_Defalt>()->GetDSV()->Get();

	// Shader Resource �缳��..
	ShaderResourceView* shadowSRV = g_Resource->GetShaderResourceView<DS_Shadow>();
	m_ForwardPS->SetShaderResourceView<gShadowMap>(shadowSRV->Get());
}

void ForwardPass::Release()
{

}

void ForwardPass::BeginRender()
{
	g_Context->OMSetRenderTargets(1, &m_BackBufferRTV, m_DepthStencilView);
	g_Context->OMSetDepthStencilState(m_DepthStencilState, 0);
	g_Context->OMSetBlendState(m_BlendState, 0, 0xffffffff);
	g_Context->ClearRenderTargetView(m_BackBufferRTV, reinterpret_cast<const float*>(&DXColors::DeepDarkGray));
	g_Context->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	g_Context->RSSetViewports(1, m_ScreenViewport);
	g_Context->RSSetState(m_RasterizerState);
}

void ForwardPass::Update(MeshData* mesh, GlobalData* global)
{
	Matrix world = mesh->mWorld;
	Matrix view = *global->mCamView;
	Matrix proj = *global->mCamProj;
	Matrix shadowTrans = *global->mLightVPT;
	MaterialBuffer* mat = *mesh->Material_List.begin();

	switch (mesh->ObjType)
	{
	case OBJECT_TYPE::BASE:
	{
		CB_MeshObject objectBuf;
		objectBuf.gWorld = world;
		objectBuf.gWorldView = world * view;
		objectBuf.gWorldViewProj = world * view * proj;
		objectBuf.gShadowTransform = world * shadowTrans;

		m_MeshVS->SetConstantBuffer(objectBuf);

		// Vertex Shader Update..
		m_MeshVS->Update();
	}
		break;
	case OBJECT_TYPE::SKINNING:
	{
		CB_SkinObject objectBuf;
		objectBuf.gWorld = world;
		objectBuf.gWorldView = world * view;
		objectBuf.gWorldViewProj = world * view * proj;
		objectBuf.gShadowTransform = world * shadowTrans;

		for (int i = 0; i < mesh->BoneOffsetTM.size(); i++)
		{
			objectBuf.gBoneTransforms[i] = mesh->BoneOffsetTM[i];
		}

		m_SkinVS->SetConstantBuffer(objectBuf);

		// Vertex Shader Update..
		m_SkinVS->Update();
	}
		break;
	default:
		break;
	}

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

	for (UINT m = 0; m < 5; m++)
	{
		lightBuf.gMaterials[m] = *global->mMatData[m];
	}
	m_ForwardPS->SetConstantBuffer(lightBuf);

	CB_LightSub lightsubBuf;
	lightsubBuf.gEyePosW = *global->mCamPos;

	m_ForwardPS->SetConstantBuffer(lightsubBuf);

	CB_Material materialBuf;
	materialBuf.gMatID = mat->Material_Index;

	if (mat->Albedo)
	{
		materialBuf.gTexID |= ALBEDO_MAP;
		m_ForwardPS->SetShaderResourceView<gDiffuseMap>((ID3D11ShaderResourceView*)mat->Albedo->TextureBufferPointer);
	}
	if (mat->Normal)
	{
		materialBuf.gTexID |= NORMAL_MAP;
		m_ForwardPS->SetShaderResourceView<gNormalMap>((ID3D11ShaderResourceView*)mat->Normal->TextureBufferPointer);
	}

	m_ForwardPS->SetConstantBuffer(materialBuf);

	// Pixel Shader Update..
	m_ForwardPS->Update();
}

void ForwardPass::Render(MeshData* mesh)
{
	ID3D11Buffer* iBuffer = reinterpret_cast<ID3D11Buffer*>(mesh->IB->IndexBufferPointer);
	ID3D11Buffer* vBuffer = reinterpret_cast<ID3D11Buffer*>(mesh->VB->VertexbufferPointer);

	UINT indexCount = mesh->IB->Count;
	UINT stride = mesh->VB->VertexDataSize;
	UINT offset = 0;

	g_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	g_Context->IASetVertexBuffers(0, 1, &vBuffer, &stride, &offset);
	g_Context->IASetIndexBuffer(iBuffer, DXGI_FORMAT_R32_UINT, 0);

	g_Context->DrawIndexed(indexCount, 0, 0);
}