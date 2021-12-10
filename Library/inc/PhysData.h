#pragma once

enum COLLIDER_TYPE
{
	BOX,
	SPHERE,
};


struct Vec
{
	float x;
	float y;
	float z;
	float w = 0; //ȸ���� ��������
};

//�ϳ��� ��ü�� ����� ����ü
struct PhysData
{
	// ��ġ
	Vec Position = { 0,0,0 };

	// ũ��
	Vec Scale;

	//ȸ��
	Vec Rotation;
	

	//��ü�� ����(���׸���) ������
	float MT_StaticFriction		= 0;
	float MT_DynamicFriction	= 0;
	float MT_Restitution		= 1;	//ƨ��� ����


	void Collider_length(COLLIDER_TYPE _type, float x, float y, float z)
	{
		type = _type;
		Col.x = x;
		Col.y = y;
		Col.z = z;
	}
	void Collider_length(COLLIDER_TYPE _type, float length = 0.5f)
	{
		type = _type;
		Col.x = length;
		Col.y = length;
		Col.z = length;
	}
	
	Vec Col;
	COLLIDER_TYPE type;
};

//�ٽ� �޴� ������
struct PhysTrData
{
	float* PosX;
	float* PosY;
	float* PosZ;
};