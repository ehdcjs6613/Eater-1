#pragma once

 enum class SHAPE_TYPE
{
	BOX,
	SPHERE,
	CAPSULE,
};

 enum class ACTOR_TYPE
 {
	 DINAMIC,
	 STATIC,
	 KNEMATIC,
 };


struct Vec
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 0.0f;; //ȸ���� ��������
};

///�ϳ��� ��ü�� ����� ����ü ������������ ��������� �Ʒ��ʿ� ����
///������� �ʴ� ���� �׳� ����Ʈ������ ���θ�ȴ�
struct PhysData
{
public:
	///��ġ ������
	//���� ��ġ
	Vec WorldPosition	= { 0.0f,0.0f,0.0f,0.0f };
	//���� ��ġ (���� �����϶�)
	Vec LocalPosition	= { 0.0f,0.0f,0.0f,0.0f };
	//ȸ��
	Vec Rotation		= { 1.0f,1.0f,1.0f,1.0f };
	//��� �� �̵��� ���� ��ų�� ��� 
	Vec FreezePositon	= { 0.0f,0.0f,0.0f,0.0f };
	//��� �� ȸ���� ���� ��ų�� ���
	Vec FreezeRotaticon = { 0.0f,0.0f,0.0f,0.0f };
	//�̰�ü�� �̵����� �־��ش�
	Vec Velocity		= { 0.0f,0.0f,0.0f,0.0f };
	//�̰�ü�� ���� �߽���
	Vec CenterPoint		= { 0.0f,0.0f,0.0f,0.0f };
public:
	///����(���׸���) ������
	//���� ������
	float MT_StaticFriction = 0.5f;
	//� ������
	float MT_DynamicFriction = 0.5f;
	//������
	float MT_Restitution = 0.6f;
	//����
	float MT_Mass = 1.0f;				
public:
	///��ü ���� ������
	//�����̴� ��ü���� (Dinamic , Static)
	bool isDinamic		= true;
	//�߷� �ۿ� ����
	bool isGrvity		= true;
	//�������� �ʴµ� �浹 �Ұ�����
	bool isKinematic	= false;
public:
	///�ݶ��̴� ������
	//�ݶ��̴��� ������
	Vec Shape_Size = { 0.5f,0.5f, 0.5f,0.0f };

	//�ݶ��̴� ���鶧 �̰ɷ� ����� ����
	void CreateBoxCollider(float x,float y,float z)
	{
		Shape_Size = { x,y,z };
		Shape_type = SHAPE_TYPE::BOX;
	}
	//������
	void CreateBoxCollider(float Radius)
	{
		Shape_Size = { Radius,Radius,Radius,Radius };
		Shape_type = SHAPE_TYPE::BOX;
	}

	//������
	void CreateSphereCollider(float Radius)
	{
		Shape_Size = { Radius,0.0f,0.0f,0.0f};
		Shape_type = SHAPE_TYPE::SPHERE;
	}

	//������,����
	void CreateCapsuleCollider(float Radius,float Height)
	{
		Shape_Size = { Radius,Height,0.0f,0.0f };
		Shape_type = SHAPE_TYPE::CAPSULE;
	}

	//�ݶ��̴��� Ÿ��
	SHAPE_TYPE	Shape_type = SHAPE_TYPE::BOX;

	//�̵����Ϳ� PhysX�ȿ� Actor�� ���� �˰��ֵ����ϱ�����
	void* ActorObj;
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
