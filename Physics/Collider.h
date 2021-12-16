#pragma once

#include "DllDefine.h"
#include "DxDefine.h"
#include "GeometryGenerator.h"
#include "../Library/inc/Component/Component.h"

class Collider : public Component
{
public:
	GeometryGenerator m_Gemetry;
protected:
	unsigned int m_Num;							//콜라이더의 넘버

	DirectX::XMFLOAT4X4 mWorld;	// 월드 변환 행렬 (로컬->월드)
	DirectX::XMFLOAT4X4 mView;	// 시야 변환 행렬 (카메라 뷰)
	DirectX::XMFLOAT4X4 mProj;	// 투영 변환 행렬 (원근/직교)

	float Center[3];
	float Size[3];

public:
	ID3D11Device* md3dDevice;						/// D3D11 디바이스
	ID3D11DeviceContext* md3dImmediateContext;		/// 디바이스 컨텍스트
public:
	PhysicsExport Collider();
	PhysicsExport virtual ~Collider();
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
public:
	void SetDevice(ID3D11Device*);						/// D3D11 디바이스
	void SetDeviceContext(ID3D11DeviceContext*);		/// 디바이스 컨텍스트

	ID3D11Device* GetDevice();						/// D3D11 디바이스
	ID3D11DeviceContext* GetDeviceContext();		/// 디바이스 컨텍스트

	PhysicsExport float* GetCenter();
	PhysicsExport float* GetSize();
	PhysicsExport DirectX::XMFLOAT4X4 GetWorld();


	PhysicsExport virtual bool OnPick();
	PhysicsExport virtual bool OffPick();

protected:
	virtual void Initialize();
	virtual void SetSize(float _x, float _y, float _z);
	virtual void SetCenter(float _x, float _y, float _z) ;

};

