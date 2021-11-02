#pragma once
#include <DirectXMath.h>
//���ҽ� �ֻ��� Ŭ����
class  Resources
{
public:
	Resources() {};
	virtual ~Resources() {};

	///�����͸� �־��ٸ� true �ٲ��ּ���
	bool Use = false;

	virtual void Delete() = 0;
};

//�ε��� ���۸� ���� Ŭ����
class Indexbuffer : Resources
{
public:
	virtual ~Indexbuffer()
	{
		delete IndexBufferPointer;
	};
	Indexbuffer()
	{
		IndexBufferPointer = nullptr;
		size = 0;
	};
	virtual void Delete() {};
	void* IndexBufferPointer;
	unsigned int size;
};


//���ؽ� ���۸� ���� Ŭ����
class Vertexbuffer : Resources
{
public:
	virtual ~Vertexbuffer()
	{
		delete VertexbufferPointer;
	};
	Vertexbuffer()
	{
		VertexbufferPointer = nullptr;
		size = 0;
	};
	virtual void Delete() {};
	void* VertexbufferPointer;
	unsigned int size;
};

//�ؽ��ĸ� ���� Ŭ����
class TextureBuffer : Resources
{
public:
	virtual ~TextureBuffer()
	{
		delete TextureBufferPointer;
	};
	TextureBuffer()
	{
		TextureBufferPointer = nullptr;
		size = 0;
	};
	virtual void Delete() {};

	void* TextureBufferPointer;
	unsigned int size;
};




