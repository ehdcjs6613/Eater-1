//#include "Transform.h"
#include "DirectXDefine.h"
#include "d3dx11effect.h"
#include "Effects.h"
#include "XVertex.h"
#include "XShader.h"
#include "OneCompile.h"
#include "ViewGrid.h"

BOOL ViewGrid::Initialize(ID3D11Device* _pDevice, ID3D11DeviceContext* _pDeviceContext, ID3D11RasterizerState* _pRSS)
	
{
	m_d3dDevice = (_pDevice);
	m_d3dImmediateContext = (_pDeviceContext);
	m_pRenderstate = (_pRSS);

	BuildGeometry();
	BuildFX();
	BuildLayout();

	return 0;
}

BOOL ViewGrid::BuildGeometry()
{
	// 정점 버퍼를 생성한다. 
	// 40개의 정점을 만들었다.
	XVertexGrid vertices[40];
	for (int i = 0; i < 40; i++)
	{
		vertices[i].Pos = DirectX::XMFLOAT3((float)(i % 10) - 5.0f, 0.0f, (float)(i / 10) - 5.0f);
		vertices[i].Color = DirectX::XMFLOAT4((const float*)&DirectX::Colors::DarkGray);	// (어두운 회색)
	}

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(XVertexGrid) * 40;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = vertices;
	HR(m_d3dDevice->CreateBuffer(&vbd, &vinitData, &m_VB));


	// 인덱스 버퍼를 생성한다.
	// 역시 40개의 라인을 나타내도록 했다.
	UINT indices[40];
	for (int i = 0; i < 10; i++)
	{
		indices[i * 2] = i;
		indices[i * 2 + 1] = i + 90;
	}

	for (int i = 0; i < 10; i++)
	{
		indices[20 + (i * 2)] = i * 10;
		indices[20 + (i * 2) + 1] = i * 10 + 9;
	}

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * 40;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = indices;
	HR(m_d3dDevice->CreateBuffer(&ibd, &iinitData, &m_IB));

	return 0;
}

BOOL ViewGrid::BuildFX()
{
	std::ifstream fin("../Resources/Shader/LWJ/color.cso", std::ios::binary);

	fin.seekg(0, std::ios_base::end);
	int size = (int)fin.tellg();
	fin.seekg(0, std::ios_base::beg);
	std::vector<char> compiledShader(size);

	fin.read(&compiledShader[0], size);
	fin.close();

	D3DX11CreateEffectFromMemory(&compiledShader[0], size,
		0, m_d3dDevice, &m_FX);

	mTech = m_FX->GetTechniqueByName("ColorTech");
	mfxWorldViewProj = m_FX->GetVariableByName("gWorldViewProj")->AsMatrix();

	return 0;
}

BOOL ViewGrid::BuildLayout()
{
	// Create the vertex input layout.
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	// Create the input layout
	D3DX11_PASS_DESC passDesc;
	mTech->GetPassByIndex(0)->GetDesc(&passDesc);
	HR(m_d3dDevice->CreateInputLayout(vertexDesc, 2, passDesc.pIAInputSignature,
		passDesc.IAInputSignatureSize, &mInputLayout));

	return 0;
}



BOOL ViewGrid::Update( const DirectX::SimpleMath::Matrix* view, const DirectX::SimpleMath::Matrix* proj)
{
	
	m_View = *view;
	m_Projection = *proj;

	return 0;
}

BOOL ViewGrid::Destroy()
{
	return 0;
}

ViewGrid::ViewGrid()
{
}
ViewGrid::ViewGrid(const ViewGrid& _pViewGrid)
{
}

ViewGrid::~ViewGrid()
{
}
void ViewGrid::Render()
{
	// 입력 배치 객체 셋팅
	m_d3dImmediateContext->IASetInputLayout(mInputLayout);
	m_d3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	// 인덱스버퍼와 버텍스버퍼 셋팅
	UINT stride = sizeof(XVertexGrid);
	UINT offset = 0;
	m_d3dImmediateContext->IASetVertexBuffers(0, 1, &m_VB, &stride, &offset);
	m_d3dImmediateContext->IASetIndexBuffer(m_IB, DXGI_FORMAT_R32_UINT, 0);

	/// WVP TM등을 셋팅
	// Set constants
	DirectX::XMMATRIX worldViewProj = m_World * m_View * m_Projection;
	mfxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProj));

	// 렌더스테이트
	m_d3dImmediateContext->RSSetState(m_pRenderstate);

	// 테크닉은...
	D3DX11_TECHNIQUE_DESC techDesc;
	mTech->GetDesc(&techDesc);

	// 랜더패스는...
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		mTech->GetPassByIndex(p)->Apply(0, m_d3dImmediateContext);

		// 20개의 인덱스로 그리드를 그린다.
		m_d3dImmediateContext->DrawIndexed(40, 0, 0);
	}

	return ;
}
