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
	UINT size;
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
	UINT size;
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

	//(ID3D11ShaderResourceView)
	void* TextureBufferPointer;
	UINT size;
};

//���̴� ������
class ShaderBuffer : Resources
{
public:
	ShaderBuffer() {};
	virtual ~ShaderBuffer() {};
	///�������������� �ϴ��� �׳� ����⸸..
	virtual void Delete() {};
};

//���͸��� ������
class MaterialBuffer :Resources
{
	MaterialBuffer() {};
	virtual ~MaterialBuffer() {};
	///�������������� �ϴ��� �׳� ����⸸..
	virtual void Delete() {};
};

//�ִϸ��̼� ������
class AnimationBuffer : Resources
{
	AnimationBuffer() {};
	virtual ~AnimationBuffer() {};
	///�������������� �ϴ��� �׳� ����⸸..
	virtual void Delete() {};
};



