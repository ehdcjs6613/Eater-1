#pragma once
#include <DirectXMath.h>
//리소스 최상위 클래스
class  Resources
{
public:
	Resources() {};
	virtual ~Resources() {};

	///데이터를 넣었다면 true 바꿔주세요
	bool Use = false;

	virtual void Delete() = 0;
};

//인덱스 버퍼를 받을 클래스
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


//버텍스 버퍼를 받을 클래스
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

//텍스쳐를 받을 클래스
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

	///(ID3D11ShaderResourceView)
	void* TextureBufferPointer;
	UINT size;
};

//쉐이더 데이터
class ShaderBuffer : Resources
{
public:
	ShaderBuffer() {};
	virtual ~ShaderBuffer() {};
	///뭐가있을지몰라서 일단은 그냥 만들기만..
	virtual void Delete() {};
};

//메터리얼 데이터
class MaterialBuffer :Resources
{
	MaterialBuffer() {};
	virtual ~MaterialBuffer() {};
	///뭐가있을지몰라서 일단은 그냥 만들기만..
	virtual void Delete() {};
};

//애니메이션 데이터
class AnimationBuffer : Resources
{
	AnimationBuffer() {};
	virtual ~AnimationBuffer() {};
	///뭐가있을지몰라서 일단은 그냥 만들기만..
	virtual void Delete() {};
};



