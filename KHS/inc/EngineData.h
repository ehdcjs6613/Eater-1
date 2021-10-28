#pragma once
#include "ResourcesData.h"

enum class OBJECT_TYPE
{
	///현재 기본형으로 넣어둔 오브젝트 종류
	///나중에 필요한건 넣고 필요없는건 빼자
	
	Default,		//값을 넣지않았을때 기본형
	Base,			//상속구조로 되어있는 오브젝트
	Skinning,		//스키닝이 추가된 오브젝트
	Bone,			//본만 있는 오브젝트
	Camera,			//카메라 기능만 하는 오브젝트
	Light,			//라이트 객체
	SkyBox,			//스카이 박스
	Texture,		//한개의 텍스쳐로된 오브젝트(페이스두개가 합쳐진 사각형 텍스쳐)
	Debug,			//디버깅 오브젝트
	Particle,		//파티클 오브젝트
	Effect			//이펙트 오브젝트
};

//씬 기준 매쉬마다 존재하지않아도 되는것들
struct GlobalData
{
	//카메라 정보들
	DirectX::XMMATRIX mViewMX;
	DirectX::XMMATRIX mProj;
};

//한개의 매쉬에 존재하는 데이터
class MeshData
{
public:
	MeshData()= default;
	~MeshData() {};

	//오브젝트 타입
	OBJECT_TYPE ObjType = OBJECT_TYPE::Default;
	//인덱스버퍼 ,버텍스 버퍼
	Indexbuffer*	IB;
	Vertexbuffer*	VB;


	//매쉬 관련 행렬
	DirectX::XMMATRIX mWorld;
	DirectX::XMMATRIX mlocal;

	//애니메이션



	//Mesh 위치값
	DirectX::XMFLOAT3 Pos;
};

class LoadData
{
public:
	LoadData() 
	{
		IB = new Indexbuffer();
		VB = new Vertexbuffer();
	};
	~LoadData()
	{
		delete IB;
		delete VB;
	};

	Indexbuffer* IB;
	Vertexbuffer* VB;
};



 



