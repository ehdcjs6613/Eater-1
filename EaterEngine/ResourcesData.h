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

//�� ������ (���� �ε��� ���ۿ� ���ؽ����۰� �ʿ����)
class Bone : Resources
{
public:
	bool isTop;
	std::string ParentName;
	std::string MyName;



	
	Bone* ParentBone;					//�θ�ü
	std::vector<Bone*> ChildBoneList;	//�ڽİ�ü
};

//�Ž� ������
class Mesh : Resources
{
public:
	bool isTop;
	std::string ParentName;	//�θ� �̸�
	std::string MyName;		//���� �̸�



	Mesh* ParentMesh;					//�θ� ��ü
	std::vector<Mesh*> ChildMeshList;	//�ڽ� ��ü

	
	Indexbuffer*  IB;	//�ε��� ����
	Vertexbuffer* VB;	//���ؽ� ����
};








