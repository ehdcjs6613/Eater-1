#pragma once

#include <fstream>

#include "d3dx11effect.h"
#include "DllDefine.h"
#include "DxDefine.h"
#include "Collider.h"
#include <queue>

class MeshData;
class GameObject;
class VertexPositionColor;
class VertexBuffer;
class IndexBuffer;
class Transform;

class BoxCollider : public Collider
{
public:
	
private:
	struct Vertex
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT4 Color;
	};


	ID3D11Buffer* mVB;	// 버텍스버퍼
	ID3D11Buffer* mIB;	// 인덱스버퍼

	ID3DX11Effect* mFX;								// 이펙트
	ID3DX11EffectTechnique* mTech;					// 테크
	ID3DX11EffectMatrixVariable* mfxWorldViewProj;	// 이펙트용변수

	ID3D11InputLayout* mInputLayout;				// 인풋레이아웃

	// 변환 관련
	DirectX::XMMATRIX mWorld;	// 월드 변환 행렬 (로컬->월드)
	DirectX::XMMATRIX mView;	// 시야 변환 행렬 (카메라 뷰)
	DirectX::XMMATRIX mProj;	// 투영 변환 행렬 (원근/직교)



	// 렌더스테이트. 렌더링을 어떻게 할 것인가에 대한 것.
	ID3D11RasterizerState* m_pRenderstate;			/// 외부에서 생성해서 적당히 상황에 따라서 적용함. 쉐이더에서 해도 된다.

public:
	float m_Size[3];

public:
	PhysicsExport BoxCollider();
	PhysicsExport virtual ~BoxCollider();
public:
	//시작 단계에 가장먼저 실행되는 함수
	virtual void Awake() override;
	//시작 함수
	virtual void Start() override;
	//처음
	virtual void StartUpdate() override;
	//이동 행렬 업데이트
	virtual void TransformUpdate() override;
	//물리 업데이트
	virtual void PhysicsUpdate() override;
	//일반 업데이트
	virtual void Update() override;
	//마지막 업데이트
	virtual void EndUpdate() override;
private:
	//그려주는 함수
	//계산해서 충돌체크하는 OBB(Orient Bounding Box)함수
	//영역과 축이 같이돔
	void CalculateOBB();
	//정렬된 정사격형끼리의 충돌
	void CalculateAABB();
public:
	PhysicsExport void Initialize(ID3D11Device*, ID3D11DeviceContext*);
	PhysicsExport void Draw(const DirectX::XMFLOAT4X4 _View, const DirectX::XMFLOAT4X4 _Proj);
	PhysicsExport void Rnder();


	PhysicsExport void Translasion(DirectX::XMMATRIX* _World);

	void init();
};
