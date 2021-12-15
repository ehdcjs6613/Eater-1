#pragma once

#include <fstream>

#include "DllDefine.h"
#include "DxDefine.h"
#include "Collider.h"
#include <queue>
#include "VertexPositionColor.h"
#include "GeometryGenerator.h"


class BoxCollider : public Collider
{
private:

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
	//자체사용함수
	PhysicsExport void Initialize(ID3D11Device*, ID3D11DeviceContext*);
	PhysicsExport void Draw(const DirectX::XMFLOAT4X4 _View, const DirectX::XMFLOAT4X4 _Proj);
	PhysicsExport void Rnder();


	PhysicsExport void Translasion(DirectX::XMMATRIX* _World);


public:
	//상속 함수
	virtual void Initialize() override;
	virtual void SetSize(float _x, float _y, float _z) override;
	virtual void SetCenter(float _x, float _y, float _z) override;

	
	
};
