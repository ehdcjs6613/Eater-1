#pragma once
#include "ResourcesData.h"
#include "ParserData.h"

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
class GlobalData
{
public:
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

		mWorld;
		mLocal;
		Pos = { 0,0,0 };
		ObjType = OBJECT_TYPE::Default;
	}
	~MeshData() {};


	OBJECT_TYPE ObjType;//������Ʈ Ÿ��

	Indexbuffer*	IB;	//�ε��� ����
	Vertexbuffer*	VB;	//���ؽ� ����
	
	int indexCount;		//�ε��� ī����
	int vertexCount;	//���ؽ� ī����

	std::vector<DirectX::SimpleMath::Matrix> BoneOffsetTM; //�� ������ TM


	DirectX::XMMATRIX mWorld;	//�Ž��� ���� ���
	DirectX::XMMATRIX mLocal;	//�Ž��� �������
	DirectX::XMFLOAT3 Pos;		//�Ž��� ��ġ��
};

//�ļ����� �о���� �������ִ� ������
class LoadMeshData
{
public:
	~LoadMeshData()
	{
		delete IB;
		delete VB;
	};

	bool Top_Object;			//���� �ֻ��� ������Ʈ���� ����
	bool Bone_Object;			//��������Ʈ ����
	bool Skinning_Object;		//��Ű�� ������Ʈ ����

	std::string ParentName;		//�θ��� �̸�
	std::string	Name;			//�ڱ��ڽ��� �̸�

	DirectX::SimpleMath::Matrix* WorldTM;	//���� ��Ʈ����
	DirectX::SimpleMath::Matrix* LocalTM;	//���� ��Ʈ����
	


	Indexbuffer*	IB = nullptr;	//�ε��� ����
	Vertexbuffer*	VB = nullptr;	//���ؽ� ����

	
	ParserData::CMaterial* Material;	 //���׸��� ����
	ParserData::OneAnimation* Animation; //�ִϸ��̼� ����

	
	std::vector<DirectX::SimpleMath::Matrix>* BoneTMList;	//�� ��Ʈ����
	std::vector<ParserData::Mesh*>* BoneList;				//�� �Ž�


	LoadMeshData* Parent;				//�θ� �Ž�
	std::vector<LoadMeshData*> Child;	//�ڽ� �Ž� ����Ʈ
};

//������ �Ѱ��Ž��� ������
class ModelData
{
public:
	std::vector<LoadMeshData*> MeshList;
	std::vector<LoadMeshData*> BoneList;

	int TopObjCount		= 0;	//�ֻ��� �Ž���ü ����
	int TopBoneCount	= 0;	//�ֻ��� �� ��ü ����

	
	LoadMeshData* Top;
};



 



