#pragma once

#include "DllDefine.h"
#include "Collider.h"

class GameObject;

class BoxCollider : public Collider
{
private:
	//GameObject* m_pGameObject;

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
	void Draw();
	//계산해서 충돌체크하는 OBB(Orient Bounding Box)함수
	//영역과 축이 같이돔
	void CalculateOBB();
	//정렬된 정사격형끼리의 충돌
	void CalculateAABB();
public:
	void Initialize(ID3D11DeviceContext*);
};
