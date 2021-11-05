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
	DirectX::XMMATRIX* mViewMX;
	DirectX::XMMATRIX* mProj;
};

//한개의 매쉬에 존재하는 데이터
class MeshData
{
public:
	MeshData()
	{	
		//초기화
		indexCount	= 0;
		vertexCount = 0;

		mWorld = nullptr;
		mLocal = nullptr;
		Pos = { 0,0,0 };
		ObjType = OBJECT_TYPE::Default;
	}
	~MeshData() {};


	OBJECT_TYPE ObjType;//오브젝트 타입

	Indexbuffer*	IB;	//인덱스 버퍼
	Vertexbuffer*	VB;	//버텍스 버퍼
	
	int indexCount;		//인덱스 카운터
	int vertexCount;	//버텍스 카운터

	DirectX::XMMATRIX* mWorld;	//매쉬의 월드 행렬
	DirectX::XMMATRIX* mLocal;	//매쉬의 로컬행렬
	DirectX::XMFLOAT3 Pos;		//매쉬의 위치값
};

//파서에서 읽어오고 변경해주는 데이터
class LoadData
{
public:
	~LoadData()
	{
		delete IB;
		delete VB;
	};

	Indexbuffer*	IB = nullptr;
	Vertexbuffer*	VB = nullptr;
};

//저장할 한개매쉬의 데이터
class SaveOneMeshData
{
public:
	//스키닝 데이터
	//std::vector<ParserData::Mesh*>* BoneList;
	//std::vector<DirectX::SimpleMath::Matrix>* m_BoneTMList;
	////애니메이션
	//ParserData::OneAnimation* Animation;
	//ParserData::CMaterial*	MaterialD;



	LoadData* BufferData;


};



 



