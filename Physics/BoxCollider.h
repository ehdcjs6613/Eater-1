#pragma once

#include "DxDefine.h"
#include "DllDefine.h"
#include "VirtualMesh.h"
#include "BuildGeometry.h"
#include "Collider.h"

class GameObject;
class VertexPositionColor;
class VertexBuffer;
class IndexBuffer;

class BoxCollider : public Collider
{
private:
	DirectX::XMFLOAT4X4					 mWorldTM;
	DirectX::XMFLOAT4X4					 mView;
	DirectX::XMFLOAT4X4					 mProj;


	ID3D11Buffer* buffer;

	VertexBuffer* m_pVertexBuffer;
	IndexBuffer* m_pIndexBuffer;
	D3D11_BUFFER_DESC vertexBufferDESC;
	D3D11_SUBRESOURCE_DATA vertexBufferDATA;
	UINT indexCount = 0;
	VertexPositionColor* mVertex = nullptr;
	Build						 mBuild;
	VirtualMesh					 mVirtualMesh;

	ID3D11Device* m_Device;
	ID3D11DeviceContext* m_DeviceContext;
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
	void Draw(const DirectX::XMFLOAT4X4 _View, const DirectX::XMFLOAT4X4 _Proj, const DirectX::XMFLOAT4X4 _WorldTM);
	//계산해서 충돌체크하는 OBB(Orient Bounding Box)함수
	//영역과 축이 같이돔
	void CalculateOBB();
	//정렬된 정사격형끼리의 충돌
	void CalculateAABB();
public:
	void Initialize(ID3D11Device*, ID3D11DeviceContext*, VertexPositionColor* , UINT );
};
