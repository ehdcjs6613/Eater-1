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

	//어떠한자료형으로 버텍스 버퍼를 만들었는지 사이즈
	unsigned int VectexDataSize = 0;
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








