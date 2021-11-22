#include "DirectDefine.h"
#include "RenderPassBase.h"
#include "ShaderBase.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ViewPort.h"
#include "Texture2D.h"
#include "DepthStencilView.h"
#include "RenderTargetBase.h"
#include "BasicRenderTarget.h"
#include "MathDefine.h"
#include "EngineData.h"
#include "ShadowPass.h"

#include "VertexDefine.h"
#include "ConstantBufferDefine.h"
#include "ShaderResourceBufferDefine.h"
#include "ResourceFactoryBase.h"
#include "ResourceManagerBase.h"
#include "ShaderManagerBase.h"

ShadowPass::ShadowPass()
	:m_ShadowDSV(nullptr), m_ShadowSRV(nullptr)
{
}

ShadowPass::~ShadowPass()
{

}

void ShadowPass::Initialize(int width, int height)
{
	// Shader ����..
	m_MeshShadowVS = g_Shader->GetShader("ShadowMeshVS");
	m_SkinShadowVS = g_Shader->GetShader("ShadowSkinVS");
	m_ForwardPS = g_Shader->GetShader("ForwardPS");

	m_RasterizerState = g_Resource->GetRasterizerState(eRasterizerState::DEPTH);

	// ViewPort ����..
	m_ShadowViewport = g_Factory->CreateViewPort(0.0f, 0.0f, (float)width, (float)height, 4.0f, 4.0f);

	// DepthStencilView ����..
	D3D11_TEXTURE2D_DESC texDesc;
	ZeroMemory(&texDesc, sizeof(texDesc));
	texDesc.Width = width * 4;
	texDesc.Height = height * 4;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	//texDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	texDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	texDesc.CPUAccessFlags = 0;
	texDesc.MiscFlags = 0;

	// Texture 2D ����..
	Microsoft::WRL::ComPtr<ID3D11Texture2D> tex2D = nullptr;
	g_Factory->CreateTexture2D(&texDesc, tex2D.GetAddressOf());

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	dsvDesc.Flags = 0;
	dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;

	// Shadow DepthStencilView ����..
	g_Factory->CreateDSV(tex2D.Get(), &dsvDesc, nullptr);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = texDesc.MipLevels;
	srvDesc.Texture2D.MostDetailedMip = 0;

	// ShaderResourceView ����..
	g_Factory->CreateSRV(tex2D.Get(), &srvDesc, &m_ShadowSRV);

	// RenderTarget ����..
	m_ShadowRT = g_Factory->CreateBasicRenderTarget(nullptr, &m_ShadowSRV);
	m_ShadowRT->SetRatio(4.0f, 4.0f);

	m_ShadowDepthStencilView = g_Resource->GetDepthStencilView(eDepthStencilView::SHADOW);
	m_ShadowDepthStencilView->SetRatio(4.0f, 4.0f);

	// Shadow DepthStencilView ����..
	m_ShadowDSV = m_ShadowDepthStencilView->GetDSV();

	// Shadow Map ���..
	m_ForwardPS->SetShaderResourceView<gShadowMap>(&m_ShadowSRV);

	// Texture2D Resource Reset..
	RESET_COM(tex2D);
}

void ShadowPass::OnResize(int width, int height)
{
	// Shadow DepthStencilView �缳��..
	m_ShadowDSV = m_ShadowDepthStencilView->GetDSV();

	// Shadow ShaderResourceView �缳��..
	m_ShadowSRV = m_ShadowRT->GetSRV();

	// Shadow Map ���..
	m_ForwardPS->SetShaderResourceView<gShadowMap>(&m_ShadowSRV);
}

void ShadowPass::Release()
{

}

void ShadowPass::BeginRender()
{
	g_Context->OMSetBlendState(0, 0, 0xffffffff);
	g_Context->RSSetViewports(1, m_ShadowViewport);

	// �׸��⸸ �� ���̹Ƿ� null Render Target ����..
	// ���� ����, null Rendering ����� �����ϸ� ���� ���Ⱑ ��Ȱ��ȭ �ȴ�..
	g_Context->OMSetRenderTargets(0, nullptr, m_ShadowDSV);
	g_Context->ClearDepthStencilView(m_ShadowDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);
	g_Context->RSSetState(m_RasterizerState);
}

void ShadowPass::Update(MeshData* mesh, GlobalData* global)
{
	Matrix world = mesh->mWorld;
	Matrix view = *global->mLightViewMX;
	Matrix proj = *global->mLightProj;

	switch (mesh->ObjType)
	{
	case OBJECT_TYPE::Base:
	{
		CB_ShadowObject shadowBuf;
		shadowBuf.gWorldViewProj = world * view * proj;

		m_MeshShadowVS->SetConstantBuffer(shadowBuf);

		m_MeshShadowVS->Update();
	}
	break;
	case OBJECT_TYPE::Skinning:
	{
		CB_ShadowObject shadowBuf;
		shadowBuf.gWorldViewProj = world * view * proj;

		CB_Skinned skinBuf;
		for (int i = 0; i < mesh->BoneOffsetTM.size(); i++)
		{
			skinBuf.gBoneTransforms[i] = mesh->BoneOffsetTM[i];
		}

		m_SkinShadowVS->SetConstantBuffer(shadowBuf);
		m_SkinShadowVS->SetConstantBuffer(skinBuf);

		m_SkinShadowVS->Update();
	}
	break;
	default:
		break;
	}
}

void ShadowPass::Render(MeshData* mesh)
{
	/// ���� ������ �߰�
	ID3D11Buffer* iBuffer = reinterpret_cast<ID3D11Buffer*>(mesh->IB->IndexBufferPointer);
	ID3D11Buffer* vBuffer = reinterpret_cast<ID3D11Buffer*>(mesh->VB->VertexbufferPointer);

	UINT indexCount = mesh->IB->Count;
	UINT stride = mesh->VB->VertexDataSize;
	UINT offset = 0;

	g_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	g_Context->IASetVertexBuffers(0, 1, &vBuffer, &stride, &offset);
	g_Context->IASetIndexBuffer(iBuffer, DXGI_FORMAT_R32_UINT, 0);
	
	// Draw..
	g_Context->DrawIndexed(indexCount, 0, 0);
}
