#include "MathHelper.h"
#include "Effects.h"
#include "d3dx11effect.h"
#include "InputLayout.h"
#include "EngineData.h"
#include "../Physics/VertexPositionColor.h"
//#include "../EaterEngine/EaterEngine/DebugManager.h"
#include "BoxCol.h"

#ifdef DEBUG
#pragma  comment(lib,"../Library/lib/EaterEngine_x64d.lib")
#else
#pragma  comment(lib,"../Library/lib/EaterEngine_x64r.lib")

#endif // DEBUG


BoxCol::BoxCol()
{
	
}

BoxCol::~BoxCol()
{
}

void BoxCol::init()
{
	// 정점 버퍼를 생성한다. 
	// 각 축에 맞도록 6개의 정점을 만들었다.
	VertexPositionColor vertices[] =
	{
		{ XMFLOAT3(+6.0f, -1.0f, -1.0f), XMFLOAT4((const float*)&Colors::White)      },
		{ XMFLOAT3(+6.0f, +1.0f, -1.0f), XMFLOAT4((const float*)&Colors::Green)      },

		{ XMFLOAT3(+8.0f, +1.0f, -1.0f), XMFLOAT4((const float*)&Colors::White)          },
		{ XMFLOAT3(+8.0f, -1.0f, -1.0f), XMFLOAT4((const float*)&Colors::Green)      },

		{ XMFLOAT3(+6.0f, -1.0f, +1.0f), XMFLOAT4((const float*)&Colors::White)        },
		{ XMFLOAT3(+6.0f, +1.0f, +1.0f), XMFLOAT4((const float*)&Colors::Green)    },

		{ XMFLOAT3(+8.0f, +1.0f, +1.0f), XMFLOAT4((const float*)&Colors::White)        },
		{ XMFLOAT3(+8.0f, -1.0f, +1.0f), XMFLOAT4((const float*)&Colors::Green)  },
		//
		{ XMFLOAT3(+3.0f, -1.0f, -2.0f), XMFLOAT4((const float*)&Colors::White)      },
		{ XMFLOAT3(+3.0f, +4.0f, -2.0f), XMFLOAT4((const float*)&Colors::Green)      },

		{ XMFLOAT3(+2.0f, +5.0f, +3.0f), XMFLOAT4((const float*)&Colors::White)          },
		{ XMFLOAT3(+2.0f, -3.0f, +3.0f), XMFLOAT4((const float*)&Colors::Green)      },

	};

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex) * 8;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = vertices;
	HR(md3dDevice->CreateBuffer(&vbd, &vinitData, &mVB));


	// 인덱스 버퍼를 생성한다.
	// 역시 3개의 축을 나타내도록 했다.

	UINT indices[] =
	{
		// front face
		0, 1, 2,
		0, 2, 3,

		// back face
		4, 6, 5,
		4, 7, 6,

		// left face
		4, 5, 1,
		4, 1, 0,

		// right face
		3, 2, 6,
		3, 6, 7,

		// top face
		1, 5, 6,
		1, 6, 2,

		// bottom face
		4, 0, 3,
		4, 3, 7,


		8, 9, 7,
		7, 10, 11,

		12, 9, 6,
		8, 10, 11,

		12, 9, 6,
		10, 12, 11,
	};

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * 36;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = indices;
	HR(md3dDevice->CreateBuffer(&ibd, &iinitData, &mIB));


	std::ifstream fin("../Resources/Shader/LWJ/color.cso", std::ios::binary);

	fin.seekg(0, std::ios_base::end);
	int size = (int)fin.tellg();
	fin.seekg(0, std::ios_base::beg);
	std::vector<char> compiledShader(size);

	fin.read(&compiledShader[0], size);
	fin.close();

	HR(D3DX11CreateEffectFromMemory(&compiledShader[0], size,
		0, md3dDevice, &mFX));

	mTech = mFX->GetTechniqueByName("ColorTech");
	mfxWorldViewProj = mFX->GetVariableByName("gWorldViewProj")->AsMatrix();

	// Create the vertex input layout.
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	// Create the input layout
	D3DX11_PASS_DESC passDesc;
	mTech->GetPassByIndex(0)->GetDesc(&passDesc);
	HR(md3dDevice->CreateInputLayout(vertexDesc, 2, passDesc.pIAInputSignature,
		passDesc.IAInputSignatureSize, &mInputLayout));
}

void BoxCol::Update(DirectX::SimpleMath::Matrix _view, DirectX::SimpleMath::Matrix _proj)
{
	mView = _view;
	mProj = _proj;
}

void BoxCol::Initialize(ID3D11Device* _pDevice, ID3D11DeviceContext* _pDeviceContext)
{
	md3dDevice = _pDevice;
	md3dImmediateContext = _pDeviceContext;
	init();
}

void BoxCol::Render(std::queue<MeshData*>* meshList)
{
	//printf("안녕하세요\n");

	// 입력 배치 객체 셋팅
	md3dImmediateContext->IASetInputLayout(mInputLayout);
	md3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//D3D11_PRIMITIVE_TOPOLOGY_LINELIST

	// 인덱스버퍼와 버텍스버퍼 셋팅
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	md3dImmediateContext->IASetVertexBuffers(0, 1, &mVB, &stride, &offset);
	md3dImmediateContext->IASetIndexBuffer(mIB, DXGI_FORMAT_R32_UINT, 0);

	/// WVP TM등을 셋팅

	

	// Set constants

	mWorld = DirectX::XMMatrixIdentity();

	XMMATRIX worldViewProj = mWorld * mView * mProj;
	mfxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProj));


	//mWorld =
	//{
	//	1,0,0,0,
	//	0,1,0,0,
	//	0,0,1,0,
	//	0,0,0,1,
	//};

	// 렌더스테이트
	//md3dImmediateContext->RSSetState(m_pRenderstate);

	// 테크닉은...
	D3DX11_TECHNIQUE_DESC techDesc;
	mTech->GetDesc(&techDesc);

	// 렌더패스는...
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		mTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);

		// 36개의 인덱스로 축을 그린다.
		md3dImmediateContext->DrawIndexed(36, 0, 0);
	}
}
