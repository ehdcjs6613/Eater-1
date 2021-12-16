#pragma once

#include <fstream>
#include <functional>
#include <vector>

#include "DxDefine.h"
#include "d3dx11effect.h"
#include "VertexPositionColor.h"



struct GeometryGenerator
{
public:
	DirectX::XMFLOAT4 m_Color;

	ID3D11Buffer*				 m_pVertexBuffer;	// ���ؽ�����
	ID3D11Buffer*				 m_pIndexBuffer;	// �ε�������
	ID3DX11Effect*			     m_pEffectFX;				// ����Ʈ
	ID3DX11EffectTechnique*		 m_pTech;					// ��ũ
	ID3DX11EffectMatrixVariable* m_pFxWorldViewProj;	// ����Ʈ�뺯��

	ID3D11InputLayout*			 m_pInputLayout;				// ��ǲ���̾ƿ�

	float x = 1, y = 1, z = 1;

	//�ϴ� ȿ������ ���ĺ��� ����
	enum class MeshType
	{
		Sphere,
		Box,
		Cylinder,
		Mesh,
		Capsule,
	};
public:
	/// �������θ� �׸� �Լ�
	bool CreateLineMesh(ID3D11Device* ,MeshType );
	void Position(float _x, float _y, float _z);
	void SetColor(const DirectX::XMVECTORF32 _Color);
protected:
	template<class Arcive>
	bool CreateVertexBuffer(ID3D11Device*, Arcive* ,int ,typename std::enable_if<std::is_class<Arcive>::value, bool>::type );
private:
	bool CreateIndexBuffer (ID3D11Device*, unsigned int*, int );
	bool CreateBulildFX(ID3D11Device* _pDevice);
	bool CreateBulildInputLayout(ID3D11Device*);
};

template<class Arcive>
inline bool GeometryGenerator::CreateVertexBuffer(ID3D11Device* _pDevice,  Arcive* _pArcive, int _Size, typename std::enable_if<std::is_class<Arcive>::value, bool>::type tArcive)
{
	HRESULT hr = S_OK;

	D3D11_BUFFER_DESC vbd;

	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Arcive) * _Size;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = _pArcive;
	hr = (_pDevice->CreateBuffer(&vbd, &vinitData, &m_pVertexBuffer));
	
	return false;
}
