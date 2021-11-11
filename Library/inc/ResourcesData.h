#pragma once
#include <DirectXMath.h>
#include <string>
//���ҽ� �ֻ��� Ŭ����
class  Resources
{
public:
	Resources() {};
	virtual ~Resources() {};
};

//�ε��� ���۸� ���� Ŭ����
class Indexbuffer : Resources
{
public:
	virtual ~Indexbuffer()
	{
		delete IndexBufferPointer;
	};
	
	void* IndexBufferPointer = nullptr;

	unsigned int Count	= 0;	//���ؽ� ����
	unsigned int size	= 0;	//�ٲٷ��� �ڷ����� ������
};


//���ؽ� ���۸� ���� Ŭ����
class Vertexbuffer : Resources
{
public:
	virtual ~Vertexbuffer()
	{
		delete VertexbufferPointer;
	};

	void* VertexbufferPointer = nullptr;

	//����ڷ������� ���ؽ� ���۸� ��������� ������
	unsigned int VectexDataSize = 0;
	unsigned int Count	= 0;	//���ؽ� ����
	unsigned int size	= 0;	//�ٲٷ��� �ڷ����� ������
};

//�ؽ��ĸ� ���� Ŭ����
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








