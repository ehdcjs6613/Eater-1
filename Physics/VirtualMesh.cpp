#include "VirtualMesh.h"

void* VirtualMesh::CreateVertex(MeshType _mesh)
{
	VertexPositionColor* vmesh = nullptr;
	switch (_mesh)
	{


	case VirtualMesh::MeshType::eNone:
		break;
	case VirtualMesh::MeshType::eAxis:
	{
		VertexPositionColor vertices[] =
		{
			{ DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f), DirectX::XMFLOAT4((const float*)&DirectX::Colors::Red)},	// x축 (빨강)
			{ DirectX::XMFLOAT3(x, 0.0f, 0.0f),    DirectX::XMFLOAT4((const float*)&DirectX::Colors::Red)  },

			{ DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f), DirectX::XMFLOAT4((const float*)&DirectX::Colors::Green)},	// y축 (초록)
			{ DirectX::XMFLOAT3(0.0f,    y, 0.0f), DirectX::XMFLOAT4((const float*)&DirectX::Colors::Green)},

			{ DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f), DirectX::XMFLOAT4((const float*)&DirectX::Colors::Blue)	},	// z축 (파랑)
			{ DirectX::XMFLOAT3(0.0f, 0.0f,    z), DirectX::XMFLOAT4((const float*)&DirectX::Colors::Blue) }
		};
		vertexCount = _countof(vertices);
		vmesh = new VertexPositionColor[vertexCount];

		for (UINT inx = 0; inx < _countof(vertices); inx++)
		{
			vmesh[inx] = vertices[inx];

		}
	}
	break;
	case VirtualMesh::MeshType::eCube:
	{

		VertexPositionColor vertices[] =
		{
			{ DirectX::XMFLOAT3(-x, -y, -z), DirectX::XMFLOAT4((const float*)&DirectX::Colors::White)   },
			{ DirectX::XMFLOAT3(-x, +y, -z), DirectX::XMFLOAT4((const float*)&DirectX::Colors::Black)   },
			{ DirectX::XMFLOAT3(+x, +y, -z), DirectX::XMFLOAT4((const float*)&DirectX::Colors::Red)     },	// 우상 증가
			{ DirectX::XMFLOAT3(+x, -y, -z), DirectX::XMFLOAT4((const float*)&DirectX::Colors::Green)   },
			{ DirectX::XMFLOAT3(-x, -y, +z), DirectX::XMFLOAT4((const float*)&DirectX::Colors::Blue)    },
			{ DirectX::XMFLOAT3(-x, +y, +z), DirectX::XMFLOAT4((const float*)&DirectX::Colors::Yellow)  },
			{ DirectX::XMFLOAT3(+x, +y, +z), DirectX::XMFLOAT4((const float*)&DirectX::Colors::Cyan)    },
			{ DirectX::XMFLOAT3(+x, -y, +z), DirectX::XMFLOAT4((const float*)&DirectX::Colors::Magenta) }
		};
		vertexCount = _countof(vertices);
		vmesh = new VertexPositionColor[vertexCount];

		for (UINT inx = 0; inx < _countof(vertices); inx++)
		{
			vmesh[inx] = vertices[inx];

		}

		//vmesh = vertices;
	}

	break;
	case VirtualMesh::MeshType::eCapsule:
		break;
	case VirtualMesh::MeshType::eQuad:
		break;
	case VirtualMesh::MeshType::eSphere:
		break;
	}

	return vmesh;
}

UINT* VirtualMesh::CreateIndex(MeshType _mesh)
{
	UINT* Indices = nullptr;

	switch (_mesh)
	{
	case VirtualMesh::MeshType::eNone:
		break;
	case VirtualMesh::MeshType::eAxis:
	{
		UINT indices[] =
		{
			// x축
			0, 1,

			// y축
			2, 3,

			// z축
			4, 5,
		};
		indicesCount = _countof(indices);
		Indices = new UINT[indicesCount];

		for (UINT inx = 0; inx < _countof(indices); inx++)
		{
			Indices[inx] = indices[inx];
		}
	}


	break;
	case VirtualMesh::MeshType::eCube:
	{
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
			4, 3, 7
		};


		indicesCount = _countof(indices);
		Indices = new UINT[indicesCount];

		for (UINT inx = 0; inx < _countof(indices); inx++)
		{
			Indices[inx] = indices[inx];
		}
	}

	break;
	case VirtualMesh::MeshType::eCapsule:
		break;
	case VirtualMesh::MeshType::eQuad:
		break;
	case VirtualMesh::MeshType::eSphere:
		break;
	}

	return Indices;
}

void VirtualMesh::Set(float p_x, float p_y, float p_z)
{
	x = p_x;
	y = p_y;
	z = p_z;
}

ID3D11Buffer* VertexBuffer::Get()
{
	return this->buffer;
}

ID3D11Buffer* const VertexBuffer::GetAdressOf()
{
	return this->buffer;
}

UINT VertexBuffer::GetIndexCount()
{
	return 0;
}

HRESULT VertexBuffer::Initialize(::VertexPositionColor* data, UINT indexCount, ID3D11Device* _pDevice)
{

	HRESULT hr = S_OK;
	ZeroMemory(&vertexBufferDESC, sizeof(vertexBufferDESC));

	this->indexCount = indexCount;
	//인덱스 데이터 로드
	vertexBufferDESC.Usage = D3D11_USAGE_IMMUTABLE;
	for (UINT inx = 0; inx < indexCount; inx++)
	{
		vertexBufferDESC.ByteWidth += sizeof(VertexPositionColor);
	}
	vertexBufferDESC.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDESC.CPUAccessFlags = 0;
	vertexBufferDESC.MiscFlags = 0;
	vertexBufferDESC.StructureByteStride = 0;

	mVertex = (VertexPositionColor*)malloc(sizeof(VertexPositionColor) * (int)(indexCount));

	if (mVertex == nullptr)
	{
		//만약에 날 경우..
		return E_FAIL;
	}
	for (UINT inx = 0; inx < (indexCount); inx++)
	{
		mVertex[inx] = data[inx];
	}
	vertexBufferDATA.pSysMem = mVertex;

	HR(_pDevice->CreateBuffer(&vertexBufferDESC, &vertexBufferDATA, &buffer));

	free(mVertex);
	mVertex = nullptr;

	return E_NOTIMPL;
}

HRESULT VertexBuffer::Initialize(const char* p_pPath, void* p_pVertex, UINT p_VertexCount)
{
	return E_NOTIMPL;
}

HRESULT VertexBuffer::Initialize(void* p_pVertex, UINT p_VertexCount, ID3D11Device* _pDevice)
{
	HRESULT hr = S_OK;

	vertexBufferDESC.Usage = D3D11_USAGE_IMMUTABLE;

	for (UINT inx = 0; inx < p_VertexCount; inx++)
	{
		vertexBufferDESC.ByteWidth += sizeof(VertexStruct::Basic32);
	}
	vertexBufferDESC.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDESC.CPUAccessFlags = 0;
	vertexBufferDESC.MiscFlags = 0;
	vertexBufferDESC.StructureByteStride = 0;
	vertexBufferDATA.pSysMem = p_pVertex;

	HR(_pDevice->CreateBuffer(&vertexBufferDESC, &vertexBufferDATA, &buffer));

	return E_NOTIMPL;
}

ID3D11Buffer* IndexBuffer::Get()
{
	return this->buffer;
}

ID3D11Buffer* const IndexBuffer::GetAdressOf()
{
	return this->buffer;
}

UINT IndexBuffer::GetVertexCount()
{
	return 0;
}

UINT IndexBuffer::GetStride()
{
	return 0;
}

UINT* IndexBuffer::GetStridePtr()
{
	return nullptr;
}

HRESULT IndexBuffer::Initialize(UINT data[], UINT vertexCount , ID3D11Device* _pDevice)
{
	HRESULT hr = S_OK;

	if (data == nullptr || vertexCount == 0)
	{
		return E_FAIL;
	}
	this->mVertexCount = vertexCount;

	indexBufferDESC;
	ZeroMemory(&indexBufferDESC, sizeof(indexBufferDESC));
	indexBufferDESC.Usage = D3D11_USAGE_IMMUTABLE;

	for (UINT inx = 0; inx < mVertexCount; inx++)
	{
		indexBufferDESC.ByteWidth += sizeof(UINT);
	}


	indexBufferDESC.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDESC.CPUAccessFlags = 0;
	indexBufferDESC.MiscFlags = 0;
	indexBufferDESC.StructureByteStride = 0;

	indexBufferDATA.pSysMem = data;

	HR(_pDevice->CreateBuffer(&indexBufferDESC, &indexBufferDATA, &buffer));

	return hr;
}

HRESULT IndexBuffer::Initialize(std::vector<UINT>& p_Indices, UINT indexCount , ID3D11Device* _pDevice)
{
	HRESULT hr = S_OK;

	ZeroMemory(&indexBufferDESC, sizeof(indexBufferDESC));
	indexBufferDESC.Usage = D3D11_USAGE_IMMUTABLE;

	for (UINT inx = 0; inx < indexCount; inx++)
	{
		indexBufferDESC.ByteWidth += sizeof(UINT);
	}

	indexBufferDESC.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDESC.CPUAccessFlags = 0;
	indexBufferDESC.MiscFlags = 0;
	indexBufferDESC.StructureByteStride = 0;

	indexBufferDATA.pSysMem = &p_Indices[0];

	HR(_pDevice->CreateBuffer(&indexBufferDESC, &indexBufferDATA, &buffer));

	return hr;
}
