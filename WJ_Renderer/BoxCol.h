#pragma once

#include "OneCompile.h"
#include <queue>
class MeshData;

class BoxCol
{
	struct Vertex
	{
		XMFLOAT3 Pos;
		XMFLOAT4 Color;
	};
	ID3D11Device* md3dDevice;						/// D3D11 디바이스
	ID3D11DeviceContext* md3dImmediateContext;		/// 디바이스 컨텍스트

	ID3D11Buffer* mVB;	// 버텍스버퍼
	ID3D11Buffer* mIB;	// 인덱스버퍼

	ID3DX11Effect* mFX;								// 이펙트
	ID3DX11EffectTechnique* mTech;					// 테크
	ID3DX11EffectMatrixVariable* mfxWorldViewProj;	// 이펙트용변수

	ID3D11InputLayout* mInputLayout;				// 인풋레이아웃

	// 변환 관련
	XMMATRIX mWorld;	// 월드 변환 행렬 (로컬->월드)
	XMMATRIX mView;	// 시야 변환 행렬 (카메라 뷰)
	XMMATRIX mProj;	// 투영 변환 행렬 (원근/직교)


	// 렌더스테이트. 렌더링을 어떻게 할 것인가에 대한 것.
	ID3D11RasterizerState* m_pRenderstate;			/// 외부에서 생성해서 적당히 상황에 따라서 적용함. 쉐이더에서 해도 된다.
public:
	BoxCol();
	~BoxCol();
public:
	void Update(DirectX::SimpleMath::Matrix _view, DirectX::SimpleMath::Matrix _proj);
	void Initialize(ID3D11Device*, ID3D11DeviceContext*);
	void Render(std::queue<MeshData*>* meshList);
public:
	void init();
};

