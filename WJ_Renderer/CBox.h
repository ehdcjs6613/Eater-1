#pragma once

#include "OneCompile.h"
#include <queue>
class MeshData;

class CBox
{
private:
	/// 쓰이고있는거
	ID3D11Device*		  m_pDevice;					
	ID3D11DeviceContext*  m_pDeviceContext;		
	
	ID3D11Buffer* Render_VB = nullptr;
	ID3D11Buffer* Render_IB = nullptr;

	ID3DX11Effect* m_FX;
	ID3DX11EffectTechnique* mTech;
	ID3DX11EffectMatrixVariable* mfxWorldViewProj;

	ID3D11InputLayout* mInputLayout;
	// 폰트때문에 뎁스스탠실 스테이트가 강제가 됐다.
	ID3D11DepthStencilState* NormalDSS;

	DirectX::SimpleMath::Matrix mWorld;	// Transform Matrix
	DirectX::SimpleMath::Matrix mView;
	DirectX::SimpleMath::Matrix mProj;

	// Buffer 관련
	UINT Vertex_Buffer_Stride = 0;
	UINT Vertex_Buffer_Offset = 0;
	// WVP 관련
	DirectX::SimpleMath::Matrix Mul_WVP;		// W * V * P
	DirectX::SimpleMath::Matrix World_Inverse;	// 월드 역행렬
	DirectX::SimpleMath::Matrix World_Inverse_Transpose;
public:
	CBox();
	~CBox();
public:
	void Update(DirectX::SimpleMath::Matrix _view, DirectX::SimpleMath::Matrix _proj);
	void Initialize(ID3D11Device*, ID3D11DeviceContext*);
	void Render(std::queue<MeshData*>* meshList);
};

