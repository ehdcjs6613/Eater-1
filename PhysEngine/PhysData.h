#pragma once

 enum class COLLIDER_TYPE
{
	BOX,
	SPHERE,
};

 enum class ACTOR_TYPE
 {
	 DINAMIC,
	 STATIC,
	 KNEMATIC,
 };


struct Vec
{
	float x;
	float y;
	float z;
	float w = 0; //ȸ���� ��������
};

///�ϳ��� ��ü�� ����� ����ü ������������ ��������� �Ʒ��ʿ� ���� 
struct PhysData
{
	// ��ġ
	Vec WorldPosition = { 0,0,0 };
	Vec LocalPosition = { 0,0,0 };

	// ũ��
	Vec Scale = {0.5f,0.5f, 0.5f};

	//ȸ��
	Vec Rotation = { 0,0,0,0 };
	

	//��ü�� ����(���׸���) ������
	float MT_StaticFriction		= 0.5f;	//���� ������
	float MT_DynamicFriction	= 0.5f;	//� ������
	float MT_Restitution		= 0.6f;	//������
	float MT_Mass				= 1;	//����


	void Collider_length(COLLIDER_TYPE _type, float x, float y, float z)
	{
		Collider_type = _type;
		Col.x = x;
		Col.y = y;
		Col.z = z;
	}
	void Collider_length(COLLIDER_TYPE _type, float length = 0.5f)
	{
		Collider_type = _type;
		Col.x = length;
		Col.y = length;
		Col.z = length;
	}
	
	Vec Col;
	COLLIDER_TYPE	Collider_type;
	ACTOR_TYPE		Actor_TYPE;
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
