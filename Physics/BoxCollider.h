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
private:
	//�׷��ִ� �Լ�
	//����ؼ� �浹üũ�ϴ� OBB(Orient Bounding Box)�Լ�
	//������ ���� ���̵�
	void CalculateOBB();
	//���ĵ� ������������� �浹
	void CalculateAABB();
public:
	//��ü����Լ�
	PhysicsExport void Initialize(ID3D11Device*, ID3D11DeviceContext*);
	PhysicsExport void Draw(const DirectX::XMFLOAT4X4 _View, const DirectX::XMFLOAT4X4 _Proj);
	PhysicsExport void Rnder();


	PhysicsExport void Translasion(DirectX::XMMATRIX* _World);


public:
	//��� �Լ�
	virtual void Initialize() override;
	virtual void SetSize(float _x, float _y, float _z) override;
	virtual void SetCenter(float _x, float _y, float _z) override;

	
	
};
