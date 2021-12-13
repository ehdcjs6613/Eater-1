#pragma once

#include "DllDefine.h"
#include "DxDefine.h"
#include "../Library/inc/Component/Component.h"

class Collider : public Component
{
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
};

