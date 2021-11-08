#pragma once
#include <DirectXMath.h>
#include <string>
//리소스 최상위 클래스
class  Resources
{
public:
	Resources() {};
	virtual ~Resources() {};
};

//인덱스 버퍼를 받을 클래스
class Indexbuffer : Resources
{
public:
	virtual ~Indexbuffer()
	{
		delete IndexBufferPointer;
	};
	
	void* IndexBufferPointer = nullptr;

	unsigned int Count	= 0;	//버텍스 개수
	unsigned int size	= 0;	//바꾸려는 자료형의 사이즈
};


//버텍스 버퍼를 받을 클래스
class Vertexbuffer : Resources
{
public:
	virtual ~Vertexbuffer()
	{
		delete VertexbufferPointer;
	};

	void* VertexbufferPointer = nullptr;

	unsigned int Count	= 0;	//버텍스 개수
	unsigned int size	= 0;	//바꾸려는 자료형의 사이즈
};

//텍스쳐를 받을 클래스
class TextureBuffer : Resources
{
public:
	virtual ~TextureBuffer()
	{
		delete TextureBufferPointer;
	};

	void* TextureBufferPointer = nullptr;
	unsigned int size = 0;
};

//본 데이터 (본은 인덱스 버퍼와 버텍스버퍼가 필요없음)
class Bone : Resources
{
public:
	bool isTop;
	std::string ParentName;
	std::string MyName;



	
	Bone* ParentBone;					//부모객체
	std::vector<Bone*> ChildBoneList;	//자식객체
};

//매쉬 데이터
class Mesh : Resources
{
public:
	bool isTop;
	std::string ParentName;	//부모 이름
	std::string MyName;		//나의 이름



	Mesh* ParentMesh;					//부모 객체
	std::vector<Mesh*> ChildMeshList;	//자식 객체

	
	Indexbuffer*  IB;	//인덱스 버퍼
	Vertexbuffer* VB;	//버텍스 버퍼
};








