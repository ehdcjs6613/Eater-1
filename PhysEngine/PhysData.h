#pragma once
#include "PhysEngineDLL.h"
#include "SimpleMath.h"
#include <vector>

//typedef unsigned int UINT;
 enum class SHAPE_TYPE
{
	BOX,
	SPHERE,
	CAPSULE,
	TRIANGLE
};

 enum class ACTOR_TYPE
 {
	 DINAMIC,
	 STATIC,
	 KNEMATIC,
 };

///���̽� �������� �ݶ��̴��� �����ϰ������ �ʿ��� ������
struct TriangleMeshData 
{
	std::vector<DirectX::SimpleMath::Vector3>* VertexList;
	std::vector<UINT>* IndexList;
};

///�ϳ��� ��ü�� ����� ����ü ������������ ��������� �Ʒ��ʿ� ����
///������� �ʴ� ���� �׳� ����Ʈ������ ���θ�ȴ�
struct Vec
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 0.0f; //ȸ���� ��������
};

///�ϳ��� ��ü�� ����� ����ü ������������ ��������� �Ʒ��ʿ� ����
///������� �ʴ� ���� �׳� ����Ʈ������ ���θ�ȴ�
class PHYS_ENGINEDLL PhysData
{
public:
	PhysData();
	~PhysData();
	//���� ��ġ
	Vec WorldPosition;
	//ȸ��
	Vec Rotation;
	//�̰�ü�� ���� �߽���
	Vec CenterPoint;
	//������� ��ġ
	void SetWorldPosition(float x, float y, float z);
	void SetLocalPosition(float x, float y, float z);
	void SetTranlate(float x, float y, float z);

	//������� ȸ��
	void SetRotation(float x, float y, float z);
	void SetRotate(float x, float y, float z);
	void AddForce(float x, float y, float z);
public:
	///����(���׸���) ������
	//���� ������
	float MT_StaticFriction;
	//� ������
	float MT_DynamicFriction;
	//������
	float MT_Restitution;
	//����
	float MT_Mass;
public:
	///��ü ���� ������
	//�����̴� ��ü���� (Dinamic , Static)
	bool isDinamic;
	//�߷� �ۿ� ����
	bool isGrvity;
	//�������� �ʴµ� �浹 �Ұ�����
	bool isKinematic;
public:
	//���� ���� ����
	void CreateBoxCollider(float x, float y, float z);
	//������
	void CreateBoxCollider(float Radius);
	//������
	void CreateSphereCollider(float Radius);
	//������,����
	void CreateCapsuleCollider(float Radius, float Height);
	//���̽��������� �ݶ��̴��� ���鶧
	void CreateTriangleCollider(TriangleMeshData*  Data);
private:
	///��ġ ������
	Vec MovePoint;
	//���� ��ġ (���� �����϶�)
	Vec LocalPosition;
	//��� �� �̵��� ���� ��ų�� ��� 
	Vec FreezePositon;
	//��� �� ȸ���� ���� ��ų�� ���
	Vec FreezeRotaticon;
	//�̰�ü�� �̵��ӷ��� �־��ش�
	Vec Velocity;
	//���� ���� �������� ���� �ٶ� ���
	Vec Force;
private:
	///�ݶ��̴� ������
	Vec Shape_Size;			//������
	SHAPE_TYPE	Shape_type; //Ÿ��
private:
	bool isMove;
	bool isForce;
private:
	void* ActorObj;
	TriangleMeshData* Triangle;
	friend class Factory;
	friend class PhysEngine;
};

//Phys ������ ���� ������
struct PhysSceneData
{
	

};





/*
*
 ������ (Restitution)
	�籸���� ���� ���ڸ� �����̴� ���� �������ִ� ���� �浹������ �����̴� ���� ���߰�
	�����ִ� ���� �����̰� �ȴ� �̶� �ۿ�Ǵ°��� ������ 1�ϼ��� �浹�Ͽ����� �ӵ��� �����ȴ�
	0�̶�� �浹 ���ڸ��� ����� �� 1 = ���� ź��  0 = ��ź�� �浹

 ���� ������ (StaticFriction) , � ������ (DynamicFriction)
	��ü�� �����̱� ���� �������� �ǹ� ���� ���ڸ� ������ �ִ� �ڵ����� ó�������̱�� ��������
	�����̱� �����ϸ� ū���� �����ʴ´� ��ü�� �����̱� �����ϸ� � �������� ����ȴ� ���� ��쿡
	� �������� ���� �����º��� �۱⶧���� 
	
	F(��) = u(�������) * m(����) * g(�߷�) 

Dinamic ��ü
	���� ���ؼ� ������ ���� �ְ� �浹�� ������ ��ü

Knematic ��ü
	�� ��ġ���� �ٸ� ��ġ���� �̵��� ���������� ���� ���ؼ�
	������ �� �ִ� ��ü�� �ƴϴ�

	���� ������ ���� ��ü�� �����ϸ� moveGlobal �Լ��� �����ϼ� �ִ�
	�Ϲ����� Dynamic ���͸� �м��� �ִ� ������ static �� �ٸ� Knematic ��ü�� �浹��������

Static ��ü
	�̰�ü�� ��� ����� ������ ������ �� ���� ��ü�̴�
	������ ��ü�� �ǹ��Ѵ�
*/
