#include "GeometryGenerator.h"


#define ENDLINE ;
bool GeometryGenerator::CreateLineMesh(ID3D11Device* _pDevice,MeshType _mesh)
{
	switch (_mesh)
	{
	case GeometryGenerator::MeshType::Sphere:
	{
		DirectX::XM_PI;

		VertexPositionColor vertices[6];
		int cnt = _countof(vertices);
		ZeroMemory(&vertices, sizeof(VertexPositionColor) * cnt);

		vertices[0x00] = { DirectX::XMFLOAT3(+1, -1.0f, -1.0f),  DirectX::XMFLOAT4((const float*)&DirectX::Colors::Green) };
		vertices[0x01] = { DirectX::XMFLOAT3(+1, +1.0f, -1.0f),  DirectX::XMFLOAT4((const float*)&DirectX::Colors::Green) };
		
		vertices[0x02] = { DirectX::XMFLOAT3(-1, -1.0f, -1.0f),  DirectX::XMFLOAT4((const float*)&DirectX::Colors::Green) };
		vertices[0x03] = { DirectX::XMFLOAT3(+1, +1.0f, -1.0f),  DirectX::XMFLOAT4((const float*)&DirectX::Colors::Green) };

		vertices[0x04] = { DirectX::XMFLOAT3(+5, -1.0f, +1.0f),  DirectX::XMFLOAT4((const float*)&DirectX::Colors::Green) };
		vertices[0x05] = { DirectX::XMFLOAT3(+5, +1.0f, +1.0f),  DirectX::XMFLOAT4((const float*)&DirectX::Colors::Green) };

		

		UINT indices[6];

		///============================================================================================================================================///
		indices[0x00] = 0; indices[0x01] = 1; indices[0x02] = 2;  indices[0x03] = 0; indices[0x04] = 3; indices[0x05] = 2;

		CreateVertexBuffer<VertexPositionColor>(_pDevice, vertices, 4, vertices);
		//#_countof : 정적배열의 개수를 구하는 매크로
		CreateIndexBuffer(_pDevice, indices, _countof(indices));
	}
	break;
	case GeometryGenerator::MeshType::Box:
	{
		VertexPositionColor vertices[12];
		int cnt = _countof(vertices);
		ZeroMemory(&vertices, sizeof(VertexPositionColor) * cnt);

		vertices[0x00] = { DirectX::XMFLOAT3(+6, -1.0f, -1.0f),  DirectX::XMFLOAT4((const float*)&DirectX::Colors::Green) };
		vertices[0x01] = { DirectX::XMFLOAT3(+6, +1.0f, -1.0f),  DirectX::XMFLOAT4((const float*)&DirectX::Colors::Green) };

		vertices[0x02] = { DirectX::XMFLOAT3(+8, +1.0f, -1.0f),  DirectX::XMFLOAT4((const float*)&DirectX::Colors::Green) };
		vertices[0x03] = { DirectX::XMFLOAT3(+8, -1.0f, -1.0f),  DirectX::XMFLOAT4((const float*)&DirectX::Colors::Green) };
											  
		vertices[0x04] = { DirectX::XMFLOAT3(+8, -1.0f, +1.0f),  DirectX::XMFLOAT4((const float*)&DirectX::Colors::Green) };
		vertices[0x05] = { DirectX::XMFLOAT3(+8, +1.0f, +1.0f),  DirectX::XMFLOAT4((const float*)&DirectX::Colors::Green) };

		vertices[0x06] = { DirectX::XMFLOAT3(+6, +1.0f, +1.0f),  DirectX::XMFLOAT4((const float*)&DirectX::Colors::Green) };
		vertices[0x07] = { DirectX::XMFLOAT3(+6, -1.0f, +1.0f),  DirectX::XMFLOAT4((const float*)&DirectX::Colors::Green) };

		vertices[0x08] = { DirectX::XMFLOAT3(+2, -1.0f, -1.0f),  DirectX::XMFLOAT4((const float*)&DirectX::Colors::Green) };
		vertices[0x09] = { DirectX::XMFLOAT3(+2, +1.0f, -1.0f),  DirectX::XMFLOAT4((const float*)&DirectX::Colors::Green) };

		vertices[0x0a] = { DirectX::XMFLOAT3(+2, +1.0f, +1.0f),  DirectX::XMFLOAT4((const float*)&DirectX::Colors::Green) };
		vertices[0x0b] = { DirectX::XMFLOAT3(+2, -1.0f, +1.0f),  DirectX::XMFLOAT4((const float*)&DirectX::Colors::Green) };


		UINT indices[48];

		///============================================================================================================================================///
		indices[0x00] = 0; indices[0x01] = 1; indices[0x02] = 0; indices[0x03] = 3; /* Front */ indices[0x04] = 2; indices[0x05] = 1; indices[0x06] = 2; indices[0x07] = 3;
		///============================================================================================================================================///				   
		indices[0x08] = 6; indices[0x09] = 5; indices[0x0a] = 6; indices[0x0b] = 7; /* Back  */ indices[0x0c] = 4; indices[0x0d] = 5; indices[0x0e] = 4; indices[0x0f] = 7;
		///============================================================================================================================================///				   
		indices[0x10] = 0; indices[0x11] = 7; indices[0x12] = 0; indices[0x13] = 1; /* Left  */ indices[0x14] = 6; indices[0x15] = 7; indices[0x16] = 6; indices[0x17] = 1;
		///============================================================================================================================================///				   
		indices[0x18] = 3; indices[0x19] = 2; indices[0x1a] = 3; indices[0x1b] = 4; /* Right */ indices[0x1c] = 5; indices[0x1d] = 2; indices[0x1e] = 5; indices[0x1f] = 4;
		///============================================================================================================================================///				   
		indices[0x20] = 2; indices[0x21] = 1; indices[0x22] = 6; indices[0x23] = 1; /* Top   */ indices[0x24] = 6; indices[0x25] = 5; indices[0x26] = 2; indices[0x27] = 5;
		///============================================================================================================================================///				   
		indices[0x28] = 3; indices[0x29] = 0; indices[0x2a] = 7; indices[0x2b] = 0; /* Bottom*/ indices[0x2c] = 7; indices[0x2d] = 4; indices[0x2e] = 3; indices[0x2f] = 4;
		///============================================================================================================================================///                 


		CreateVertexBuffer<VertexPositionColor>(_pDevice, vertices, 8, vertices);
		//#_countof : 정적배열의 개수를 구하는 매크로
		CreateIndexBuffer(_pDevice, indices, _countof(indices));
	}
		break;
	case GeometryGenerator::MeshType::Cylinder:
		break;
	case GeometryGenerator::MeshType::Mesh:
		break;
	case GeometryGenerator::MeshType::Capsule:
		break;

	}

	return false;
}


bool GeometryGenerator::CreateIndexBuffer(ID3D11Device* _pDevice, unsigned int* _Indices, int _Size)
{
	HRESULT hr = S_OK;

	D3D11_BUFFER_DESC ibd;

	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * _Size; // LINELIST / 48/ TRANGLELIST/36
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = _Indices;
	hr = (_pDevice->CreateBuffer(&ibd, &iinitData, &m_pIndexBuffer));
	
	return false;
}

bool GeometryGenerator::CreateBulildFX(ID3D11Device* _pDevice)
{
	HRESULT hr = S_OK;
	std::ifstream fin("../Resources/Shader/LWJ/color.cso", std::ios::binary);

	fin.seekg(0, std::ios_base::end);
	int size = (int)fin.tellg();
	fin.seekg(0, std::ios_base::beg);
	std::vector<char> compiledShader(size);

	fin.read(&compiledShader[0], size);
	fin.close();

	hr =  (D3DX11CreateEffectFromMemory(&compiledShader[0], size, 0, _pDevice, &m_pEffectFX));

	return false;
}

bool GeometryGenerator::CreateBulildInputLayout(ID3D11Device* _pDevice)
{
	HRESULT hr =S_OK;
	m_pTech = m_pEffectFX->GetTechniqueByName("ColorTech");
	m_pFxWorldViewProj = m_pEffectFX->GetVariableByName("gWorldViewProj")->AsMatrix();

	// Create the vertex input layout.
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	// Create the input layout
	D3DX11_PASS_DESC passDesc;
	m_pTech->GetPassByIndex(0)->GetDesc(&passDesc);
	hr = (_pDevice->CreateInputLayout(vertexDesc, 2, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &m_pInputLayout));
	

	return false;
}
