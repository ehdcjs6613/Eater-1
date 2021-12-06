#pragma once

#include "OneCompile.h"
#include <queue>
class MeshData;

class CBox
{
private:
	/// ���̰��ִ°�
	ID3D11Device*		  m_pDevice;					
	ID3D11DeviceContext*  m_pDeviceContext;		
	
	ID3D11Buffer* Render_VB = nullptr;
	ID3D11Buffer* Render_IB = nullptr;

	ID3DX11Effect* m_FX;
	ID3DX11EffectTechnique* mTech;
	ID3DX11EffectMatrixVariable* mfxWorldViewProj;

	ID3D11InputLayout* mInputLayout;
	// ��Ʈ������ �������Ľ� ������Ʈ�� ������ �ƴ�.
	ID3D11DepthStencilState* NormalDSS;

	DirectX::SimpleMath::Matrix mWorld;	// Transform Matrix
	DirectX::SimpleMath::Matrix mView;
	DirectX::SimpleMath::Matrix mProj;

	// Buffer ����
	UINT Vertex_Buffer_Stride = 0;
	UINT Vertex_Buffer_Offset = 0;
	// WVP ����
	DirectX::SimpleMath::Matrix Mul_WVP;		// W * V * P
	DirectX::SimpleMath::Matrix World_Inverse;	// ���� �����
	DirectX::SimpleMath::Matrix World_Inverse_Transpose;
public:
	CBox();
	~CBox();
public:
	void Update(DirectX::SimpleMath::Matrix _view, DirectX::SimpleMath::Matrix _proj);
	void Initialize(ID3D11Device*, ID3D11DeviceContext*);
	void Render(std::queue<MeshData*>* meshList);
};

