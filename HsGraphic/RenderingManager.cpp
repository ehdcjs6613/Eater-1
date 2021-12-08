#include "RenderingManager.h"
#include "ShaderManager.h"
#include "BufferData.h"
#include "GraphicDebugManager.h"
#include "EngineData.h"
#include "TextureBase.h"


RenderingManager::RenderingManager()
{
	Device			= nullptr;
	DeviceContext	= nullptr;

	mShaderManager = nullptr;

	mWireframe	= nullptr;
	mSolid		= nullptr;

	BasicSampler = nullptr;
}

RenderingManager::~RenderingManager()
{
	Device = nullptr;
	DeviceContext = nullptr;
}

void RenderingManager::Initialize(ID3D11Device* mDeviece, ID3D11DeviceContext* mDeviceContext,
	ShaderManager* SM, GraphicDebugManager* DM)
{
	Device			= mDeviece;
	DeviceContext	= mDeviceContext;
	
	mShaderManager	= SM;
	mDebugManager	= DM;
	CreateTexture();
	CreateRenderState();
	GetShader();
}

void RenderingManager::CreateTexture()
{
	//����Ʈ ���μ��� ���� �ؽ��� ����
	//Post = new TextureBase();
	//Post->Create();
}

void RenderingManager::CameraUpdate(GlobalData* data)
{
	//ī�޶� ���� ������Ʈ
	ID3D11Buffer* buffer = mShaderManager->GetConstantBuffer("CameraBuffer");
	CameraBuffer temp;
	temp.view = DirectX::XMMatrixTranspose(*data->mViewMX);
	temp.proj = DirectX::XMMatrixTranspose(*data->mProj);

	DeviceContext->UpdateSubresource(buffer, 0, nullptr, &temp, 0, 0);
	DeviceContext->VSSetConstantBuffers(0, 1, &buffer);
	DeviceContext->PSSetConstantBuffers(0, 1, &buffer);
}

void RenderingManager::SkinningUpdate(MeshData* data)
{
	///������Ʈ ���� ������Ʈ
	if (data->Albedo != nullptr)
	{
		ID3D11ShaderResourceView* SRV = reinterpret_cast<ID3D11ShaderResourceView*>(data->Albedo->TextureBufferPointer);
		DeviceContext->PSSetShaderResources(0, 1, &SRV);
		//DeviceContext->VSSetShaderResources(0, 1, &SRV);
	}


	XMFLOAT4X4 offet =
	{
		1			,0			,0			,0,
		0			,1			,0			,0,
		0			,0			,1			,0,
		0			,0			,0			,1
	};
	XMMATRIX offetMT = XMLoadFloat4x4(&offet);


	///��Ű�� ������Ʈ ���� ������Ʈ
	ID3D11Buffer* buffer = mShaderManager->GetConstantBuffer("SkinningBuffer");
	//���� ������Ʈ
	SkinningBuffer mbuffer;
	mbuffer.world = DirectX::XMMatrixTranspose(data->mWorld); //HLSL������
	mbuffer.TexMatrix = DirectX::XMMatrixTranspose(offetMT);


	int OffsetSize = (int)data->BoneOffsetTM.size();
	for (int i = 0; i < OffsetSize; i++)
	{
		mbuffer.BoneOffset[i] = (data->BoneOffsetTM)[i];
	}
	

	DeviceContext->UpdateSubresource(buffer, 0, nullptr, &mbuffer, 0, 0);
	DeviceContext->VSSetConstantBuffers(2, 1, &buffer);
	DeviceContext->PSSetConstantBuffers(2, 1, &buffer);
}

void RenderingManager::MeshUpdate(MeshData* data)
{
	///������Ʈ ���� ������Ʈ
	if (data->Albedo != nullptr)
	{
		ID3D11ShaderResourceView* SRV = reinterpret_cast<ID3D11ShaderResourceView*>(data->Albedo->TextureBufferPointer);
		DeviceContext->PSSetShaderResources(0, 1, &SRV);
		DeviceContext->VSSetShaderResources(0, 1, &SRV);
	}

	XMFLOAT4X4 offet =
	{
		1			,0			,0			,0,
		0			,1			,0			,0,
		0			,0			,1			,0,
		0			,0			,0			,1
	};
	XMMATRIX offetMT = XMLoadFloat4x4(&offet);



	ID3D11Buffer* buffer = mShaderManager->GetConstantBuffer("ObjectBuffer");
	//���� ������Ʈ
	ObjectBuffer mbuffer;
	mbuffer.world		= DirectX::XMMatrixTranspose(data->mWorld); //HLSL������
	mbuffer.TexMatrix	= DirectX::XMMatrixTranspose(offetMT);
	DeviceContext->UpdateSubresource(buffer, 0, nullptr, &mbuffer, 0, 0);
	DeviceContext->VSSetConstantBuffers(1, 1, &buffer);
	DeviceContext->PSSetConstantBuffers(1, 1, &buffer);
}

void RenderingManager::BoneUpdate(MeshData* Meshdata)
{
	XMVECTOR pos;
	XMVECTOR rot;
	XMVECTOR scl;
	DirectX::XMMatrixDecompose(&scl, &rot, &pos, Meshdata->mWorld);

	XMFLOAT3 _pos;
	XMStoreFloat3(&_pos, pos);


	ID3D11Buffer* buffer = mShaderManager->GetConstantBuffer("ObjectBuffer");
	//���� ������Ʈ
	ObjectBuffer mbuffer;
	mbuffer.world = DirectX::XMMatrixTranspose(Meshdata->mWorld); //HLSL������
	mbuffer.TexMatrix = DirectX::XMMatrixTranspose(XMMatrixIdentity());
	DeviceContext->UpdateSubresource(buffer, 0, nullptr, &mbuffer, 0, 0);
	DeviceContext->VSSetConstantBuffers(1, 1, &buffer);
	DeviceContext->PSSetConstantBuffers(1, 1, &buffer);



	BufferData* data = mDebugManager->GetBoneBuffer();

	UINT stride = data->VertexDataSize;
	UINT offset = 0;

	///void* �� ���۷� Ÿ�Ժ�ȯ
	ID3D11Buffer* IBuffer = data->IB;
	ID3D11Buffer* VBuffer = data->VB;

	///������ ����
	DeviceContext->IASetVertexBuffers(0, 1, &VBuffer, &stride, &offset);
	DeviceContext->IASetIndexBuffer(IBuffer, DXGI_FORMAT_R32_UINT, 0);


	///�׸��� ��� ����
	DeviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
	DeviceContext->RSSetState(mWireframe);


	///���̴� ����
	DeviceContext->IASetInputLayout(DebugMesh_SH.Layout);
	DeviceContext->VSSetShader(DebugMesh_SH.VertexShader, NULL, 0);
	DeviceContext->PSSetShader(DebugMesh_SH.PixelShader, NULL, 0);

	///���÷� ����
	DeviceContext->PSSetSamplers(0, 1, &BasicSampler);
	DeviceContext->VSSetSamplers(0, 1, &BasicSampler);

	///�׸���
	DeviceContext->DrawIndexed(data->IndexCount, 0, 0);
}


void RenderingManager::DebugUpdate()
{
	ID3D11Buffer* buffer = mShaderManager->GetConstantBuffer("ObjectBuffer");
	//���� ������Ʈ
	ObjectBuffer mbuffer;
	mbuffer.world = DirectX::XMMatrixTranspose(XMMatrixIdentity()); //HLSL������
	mbuffer.TexMatrix = DirectX::XMMatrixTranspose(XMMatrixIdentity());
	DeviceContext->UpdateSubresource(buffer, 0, nullptr, &mbuffer, 0, 0);
	DeviceContext->VSSetConstantBuffers(1, 1, &buffer);
	DeviceContext->PSSetConstantBuffers(1, 1, &buffer);



	BufferData* data = mDebugManager->GetGridBuffer();

	UINT stride = data->VertexDataSize;
	UINT offset = 0;

	///void* �� ���۷� Ÿ�Ժ�ȯ
	ID3D11Buffer* IBuffer = data->IB;
	ID3D11Buffer* VBuffer = data->VB;

	///������ ����
	DeviceContext->IASetVertexBuffers(0, 1, &VBuffer, &stride, &offset);
	DeviceContext->IASetIndexBuffer(IBuffer, DXGI_FORMAT_R32_UINT, 0);


	///�׸��� ��� ����
	DeviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
	DeviceContext->RSSetState(mWireframe);


	///���̴� ����
	DeviceContext->IASetInputLayout(DebugMesh_SH.Layout);
	DeviceContext->VSSetShader(DebugMesh_SH.VertexShader, NULL, 0);
	DeviceContext->PSSetShader(DebugMesh_SH.PixelShader, NULL, 0);

	///���÷� ����
	DeviceContext->PSSetSamplers(0, 1, &BasicSampler);
	DeviceContext->VSSetSamplers(0, 1, &BasicSampler);

	///�׸���
	DeviceContext->DrawIndexed(data->IndexCount, 0, 0);
}

void RenderingManager::Rendering(MeshData* data, ShaderType type)
{
	///���ؽ� ���۸� ���� �ڷ��� ������
	UINT stride = data->VB->VertexDataSize;
	UINT offset = 0;

	///void* �� ���۷� Ÿ�Ժ�ȯ
	ID3D11Buffer* IBuffer = reinterpret_cast<ID3D11Buffer*>(data->IB->IndexBufferPointer);
	ID3D11Buffer* VBuffer = reinterpret_cast<ID3D11Buffer*>(data->VB->VertexbufferPointer);

	///������ ����
	DeviceContext->IASetVertexBuffers(0, 1, &VBuffer, &stride, &offset);
	DeviceContext->IASetIndexBuffer(IBuffer, DXGI_FORMAT_R32_UINT, 0);


	///�׸��� ��� ����
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DeviceContext->RSSetState(mSolid);

	
	ShaderData Shaderdata;
	switch (type)
	{
	case RenderingManager::ShaderType::BASIC:
		Shaderdata = BasicMesh_SH;
		break;
	case RenderingManager::ShaderType::SKINNING:
		Shaderdata = SknningMesh_SH;
		break;
	}

	///���̴� ����
	DeviceContext->IASetInputLayout(Shaderdata.Layout);
	DeviceContext->VSSetShader(Shaderdata.VertexShader, NULL, 0);
	DeviceContext->PSSetShader(Shaderdata.PixelShader, NULL, 0);

	///���÷� ����
	DeviceContext->VSSetSamplers(0, 1, &BasicSampler);
	DeviceContext->PSSetSamplers(0, 1, &BasicSampler);

	///�׸���
	DeviceContext->DrawIndexed(data->IB->Count, 0, 0);
}

void RenderingManager::CreateRenderState()
{
	D3D11_RASTERIZER_DESC solidDesc;
	ZeroMemory(&solidDesc, sizeof(D3D11_RASTERIZER_DESC));
	solidDesc.FillMode = D3D11_FILL_SOLID;
	solidDesc.CullMode = D3D11_CULL_BACK;
	solidDesc.FrontCounterClockwise = false;
	solidDesc.DepthClipEnable = true;

	Device->CreateRasterizerState(&solidDesc, &mSolid);


	D3D11_RASTERIZER_DESC wireframeDesc;
	ZeroMemory(&wireframeDesc, sizeof(D3D11_RASTERIZER_DESC));
	wireframeDesc.FillMode = D3D11_FILL_WIREFRAME;
	wireframeDesc.CullMode = D3D11_CULL_BACK;
	wireframeDesc.FrontCounterClockwise = false;
	wireframeDesc.DepthClipEnable = true;

	Device->CreateRasterizerState(&wireframeDesc, &mWireframe);
}

void RenderingManager::GetShader()
{
	///���̴� �̸� ��������
	BasicMesh_SH	= mShaderManager->GetShader("texture");
	SknningMesh_SH	= mShaderManager->GetShader("Skinning");
	DebugMesh_SH	= mShaderManager->GetShader("Debug");


	///���÷� ��������
	BasicSampler = mShaderManager->GetSampler("Basic");

}

