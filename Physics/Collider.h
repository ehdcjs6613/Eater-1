#pragma once

#include "DllDefine.h"
#include "DxDefine.h"
#include "../Library/inc/Component/Component.h"

class Collider : public Component
{
public:
	ID3D11Device* md3dDevice;						/// D3D11 ����̽�
	ID3D11DeviceContext* md3dImmediateContext;		/// ����̽� ���ؽ�Ʈ
public:
	PhysicsExport Collider();
	PhysicsExport virtual ~Collider();
public:
	//���� �ܰ迡 ������� ����Ǵ� �Լ�
	virtual void Awake() override;
	//���� �Լ�
	virtual void Start() override;
	//ó��
	virtual void StartUpdate() override;
	//�̵� ��� ������Ʈ
	virtual void TransformUpdate() override;
	//���� ������Ʈ
	virtual void PhysicsUpdate() override;
	//�Ϲ� ������Ʈ
	virtual void Update() override;
	//������ ������Ʈ
	virtual void EndUpdate() override;
public:
	void SetDevice(ID3D11Device*);						/// D3D11 ����̽�
	void SetDeviceContext(ID3D11DeviceContext*);		/// ����̽� ���ؽ�Ʈ

	ID3D11Device* GetDevice();						/// D3D11 ����̽�
	ID3D11DeviceContext* GetDeviceContext();		/// ����̽� ���ؽ�Ʈ
};

