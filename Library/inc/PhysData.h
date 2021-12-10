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
	float w = 0; //회전값 있을때만
};

//하나의 강체를 만드는 구조체
struct PhysData
{
	// 위치
	Vec Position = { 0,0,0 };

	// 크기
	Vec Scale;

	//회전
	Vec Rotation;
	

	//강체의 재질(메테리얼) 데이터
	float MT_StaticFriction		= 0;
	float MT_DynamicFriction	= 0;
	float MT_Restitution		= 1;	//튕기는 정도


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

//다시 받는 데이터
struct PhysTrData
{
	float* PosX;
	float* PosY;
	float* PosZ;
};