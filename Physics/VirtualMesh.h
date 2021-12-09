#pragma once

#include <windows.h>
#include "VertexPositionColor.h"
#include <vector>



class VertexBuffer
{
public:
	VertexBuffer() : buffer(nullptr), vertexBufferDESC{ 0, }, vertexBufferDATA{ 0, } {};
	~VertexBuffer()
	{

	};

public:
	ID3D11Buffer* buffer;
	D3D11_BUFFER_DESC vertexBufferDESC;
	D3D11_SUBRESOURCE_DATA vertexBufferDATA;
	UINT indexCount = 0;
	::VertexPositionColor* mVertex = nullptr;

public:
	ID3D11Buffer* Get();
	ID3D11Buffer* const GetAdressOf();
	UINT						  GetIndexCount();


	//Box,Axis,								 |DefaultMesh
	HRESULT Initialize(::VertexPositionColor* data, UINT indexCount , ID3D11Device*);
	//Skull, Car,							 |SampleMesh 
	HRESULT Initialize(const char* p_pPath, void* p_pVertex, UINT p_VertexCount);
	//Geometry  							 |Create 
	HRESULT Initialize(void* p_pVertex, UINT p_VertexCount , ID3D11Device*);
};


class IndexBuffer
{
public:
	IndexBuffer() : buffer(nullptr), indexBufferDESC{ 0, }, indexBufferDATA{ 0, } {};

	~IndexBuffer() {};

public:
	ID3D11Buffer* buffer;
	D3D11_BUFFER_DESC indexBufferDESC;
	D3D11_SUBRESOURCE_DATA indexBufferDATA;
	UINT mStride = 0;
	UINT mVertexCount = 0;



public:
	ID3D11Buffer* Get();
	ID3D11Buffer* const				GetAdressOf();
	UINT							GetVertexCount();
	UINT							GetStride();
	UINT* GetStridePtr();

	//Box,Axis,								 |DefaultMesh
	HRESULT Initialize(UINT data[], UINT vertexCount , ID3D11Device*);
	//Skull, Car,							 |SampleMesh 
	HRESULT Initialize(std::vector<UINT>& p_Indices, UINT indexCount , ID3D11Device*);

};


struct VirtualMesh
{

	enum class MeshType
	{
		eNone,
		eSample,
		eAxis,
		eCube,
		eCylinder,
		eSphere,
		eCapsule,
		eQuad,
		ePlan,
	};


	MeshType				    mMeshType;
	VertexPositionColor			vertices;
	int						    vertexCount;
	UINT					    indicesCount;

	//메시의 크기를 수정하기위한 자료
	//
	float x = 1, y = 1, z = 1;

	void* CreateVertex(MeshType _mesh);
	UINT* CreateIndex(MeshType _mesh);
	void  Set(float p_x, float  p_y, float  p_z);

};
