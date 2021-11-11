#pragma once
#include "ResourcesData.h"
#include "ParserData.h"

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
class GlobalData
{
public:
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

		mWorld;
		mLocal;
		Pos = { 0,0,0 };
		ObjType = OBJECT_TYPE::Default;
	}
	~MeshData() {};


	OBJECT_TYPE ObjType;//오브젝트 타입

	Indexbuffer*	IB;	//인덱스 버퍼
	Vertexbuffer*	VB;	//버텍스 버퍼
	
	int indexCount;		//인덱스 카운터
	int vertexCount;	//버텍스 카운터

	std::vector<DirectX::SimpleMath::Matrix> BoneOffsetTM; //본 오프셋 TM


	DirectX::XMMATRIX mWorld;	//매쉬의 월드 행렬
	DirectX::XMMATRIX mLocal;	//매쉬의 로컬행렬
	DirectX::XMFLOAT3 Pos;		//매쉬의 위치값
};

//파서에서 읽어오고 변경해주는 데이터
class LoadMeshData
{
public:
	~LoadMeshData()
	{
		delete IB;
		delete VB;
	};

	bool Top_Object;			//가장 최상위 오브젝트인지 여부
	bool Bone_Object;			//본오브젝트 여부
	bool Skinning_Object;		//스키닝 오브젝트 여부

	std::string ParentName;		//부모의 이름
	std::string	Name;			//자기자신의 이름

	DirectX::SimpleMath::Matrix* WorldTM;	//월드 매트릭스
	DirectX::SimpleMath::Matrix* LocalTM;	//로컬 매트릭스
	


	Indexbuffer*	IB = nullptr;	//인덱스 버퍼
	Vertexbuffer*	VB = nullptr;	//버텍스 버퍼

	
	ParserData::CMaterial* Material;	 //메테리얼 정보
	ParserData::OneAnimation* Animation; //애니메이션 정보

	
	std::vector<DirectX::SimpleMath::Matrix>* BoneTMList;	//본 매트릭스
	std::vector<ParserData::Mesh*>* BoneList;				//본 매쉬


	LoadMeshData* Parent;				//부모 매쉬
	std::vector<LoadMeshData*> Child;	//자식 매쉬 리스트
};

//저장할 한개매쉬의 데이터
class ModelData
{
public:
	std::vector<LoadMeshData*> MeshList;
	std::vector<LoadMeshData*> BoneList;

	int TopObjCount		= 0;	//최상위 매쉬객체 개수
	int TopBoneCount	= 0;	//최상위 본 객체 개수

	
	LoadMeshData* Top;
};



 



