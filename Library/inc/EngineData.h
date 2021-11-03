#pragma once
#include "ResourcesData.h"

enum class OBJECT_TYPE
{
	///���� �⺻������ �־�� ������Ʈ ����
	///���߿� �ʿ��Ѱ� �ְ� �ʿ���°� ����
	
	Default,		//���� �����ʾ����� �⺻��
	Base,			//��ӱ����� �Ǿ��ִ� ������Ʈ
	Skinning,		//��Ű���� �߰��� ������Ʈ
	Bone,			//���� �ִ� ������Ʈ
	Camera,			//ī�޶� ��ɸ� �ϴ� ������Ʈ
	Light,			//����Ʈ ��ü
	SkyBox,			//��ī�� �ڽ�
	Texture,		//�Ѱ��� �ؽ��ķε� ������Ʈ(���̽��ΰ��� ������ �簢�� �ؽ���)
	Debug,			//����� ������Ʈ
	Particle,		//��ƼŬ ������Ʈ
	Effect			//����Ʈ ������Ʈ
};

//�� ���� �Ž����� ���������ʾƵ� �Ǵ°͵�
struct GlobalData
{
	//ī�޶� ������
	DirectX::XMMATRIX* mViewMX;
	DirectX::XMMATRIX* mProj;
};

//�Ѱ��� �Ž��� �����ϴ� ������
class MeshData
{
public:
	MeshData()
	{	
		//�ʱ�ȭ
		indexCount	= 0;
		vertexCount = 0;

		mWorld = nullptr;
		mLocal = nullptr;
		Pos = { 0,0,0 };
		ObjType = OBJECT_TYPE::Default;
	}
	~MeshData() {};


	OBJECT_TYPE ObjType;//������Ʈ Ÿ��

	Indexbuffer*	IB;	//�ε��� ����
	Vertexbuffer*	VB;	//���ؽ� ����
	
	int indexCount;		//�ε��� ī����
	int vertexCount;	//���ؽ� ī����

	DirectX::XMMATRIX* mWorld;	//�Ž��� ���� ���
	DirectX::XMMATRIX* mLocal;	//�Ž��� �������
	DirectX::XMFLOAT3 Pos;		//�Ž��� ��ġ��
};

class LoadData
{
public:
	LoadData() 
	{
		indexCount	= 0;
		vertexCount = 0;
	};
	~LoadData()
	{
		delete IB;
		delete VB;
	};


	int indexCount;
	int vertexCount;
	Indexbuffer* IB;
	Vertexbuffer* VB;
};



 



