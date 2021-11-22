#pragma once
#include "ResourcesData.h"
#include "ParserData.h"
#include <functional>
#include "LightHelper.h"


using namespace DirectX;
using namespace SimpleMath;
using namespace ParserData;

class Component;
enum class OBJECT_TYPE
{
	///���� �⺻������ �־�� ������Ʈ ����
	///���߿� �ʿ��Ѱ� �ְ� �ʿ���°� ����
	
	Default,		//���� �����ʾ����� �⺻��
	GameObject,		//�ٸ� ������Ʈ���� ������� �뵵
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

/// <summary>
/// ���ӿ������� �׷��ȿ������� ������ �۷ι� ������
/// </summary>
class GlobalData
{
public:
	//ī�޶� ������
	DirectX::XMMATRIX* mViewMX;
	DirectX::XMMATRIX* mProj;

	DirectX::XMMATRIX* mLightViewMX;
	DirectX::XMMATRIX* mLightProj;
	DirectX::XMMATRIX* mShadowTrans;

	LightData* mLightData;
	MaterialData mMatData[5];
};

/// <summary>
/// ���ӿ������� �׷��ȿ������� ������ �Ѱ��� �Ž� ������
/// </summary>
class MeshData
{
public:
	~MeshData()
	{
		IB = nullptr;
		VB = nullptr;
	}


	OBJECT_TYPE ObjType = OBJECT_TYPE::Default;	//������Ʈ Ÿ��

	Indexbuffer*  IB = nullptr;	//�ε��� ����
	Vertexbuffer* VB = nullptr;	//���ؽ� ����

	TextureBuffer* Diffuse = nullptr;	// Diffuse Texture
	TextureBuffer* Normal = nullptr;	// NormalMap Texture

	UINT Material_Index = 0;			// Material Index;

	std::vector<DirectX::SimpleMath::Matrix> BoneOffsetTM; //�� ������ TM

	DirectX::XMMATRIX mWorld = DirectX::XMMatrixIdentity();	//�Ž��� ���� ���
	DirectX::XMMATRIX mLocal = DirectX::XMMatrixIdentity();	//�Ž��� �������
	DirectX::XMFLOAT3 Pos = { 0,0,0 };						//�Ž��� ��ġ��
};




/// <summary>
/// ��Ȳ�� �ļ����� ���ؽ��� �ε����� ���۷� �������ְ�
/// �ִϸ��̼ǰ�, ��������ʴ°����� �׳� �����ͼ� ���ĳ��� Ŭ����
/// </summary>
class LoadMeshData
{
public:
	~LoadMeshData()
	{
		IB = nullptr;
		VB = nullptr;

		Material	= nullptr;
		Animation	= nullptr;

		BoneTMList	= nullptr;
		BoneList	= nullptr;

		Parent = nullptr;
	};

	bool Top_Object			= false;		//���� �ֻ��� ������Ʈ���� ����
	bool Bone_Object		= false;		//��������Ʈ ����
	bool Skinning_Object	= false;		//��Ű�� ������Ʈ ����

	int BoneIndex;							//���ϰ�� �ڽ��� �ε���

	std::string ParentName	= "";			//�θ��� �̸�
	std::string	Name		= "";			//�ڱ��ڽ��� �̸�

	DirectX::SimpleMath::Matrix* WorldTM = nullptr;	//���� ��Ʈ����
	DirectX::SimpleMath::Matrix* LocalTM = nullptr;	//���� ��Ʈ����
	
	Indexbuffer*	IB = nullptr;	//�ε��� ����
	Vertexbuffer*	VB = nullptr;	//���ؽ� ����

	TextureBuffer* Diffuse = nullptr;	// Diffuse Texture
	TextureBuffer* Normal = nullptr;	// NormalMap Texture

	ParserData::CMaterial*		Material	= nullptr;	//���׸��� ����
	ParserData::OneAnimation*	Animation	= nullptr;	//�ִϸ��̼� ����
	
	std::vector<Matrix>*	BoneTMList		= nullptr;	//�� ��Ʈ����
	std::vector<Mesh*>*		BoneList		= nullptr;	//�� �Ž�

	LoadMeshData* Parent = nullptr;		//�θ� �Ž�
	std::vector<LoadMeshData*> Child;	//�ڽ� �Ž� ����Ʈ


	Matrix* BoneOffset	= nullptr;	//�� ��Ʈ����
	Mesh*	BoneNumber	= nullptr;	//�� �Ž�
};

/// <summary>
/// �Ѱ��� ���� �����ϴ� ����
/// �Ž��� ���� �ֻ��� ������Ʈ�鸸 �����ϴ� ���嵥����
/// </summary>
class ModelData
{
public:
	~ModelData()
	{
		//�ֻ����� ������Ʈ�� ��ͷ� ���鼭 �����ͷ� �����Ȱ͵� ��λ���
		//
	}
	std::vector<LoadMeshData*> TopMeshList;
	std::vector<LoadMeshData*> TopBoneList;

	std::vector<Matrix>*	BoneOffsetList	= nullptr;	//�� ��Ʈ����
	std::vector<Mesh*>*		BoneList		= nullptr;	//�� �Ž�
};

//���۳�Ʈ���� �Լ������͸� ������ ����ü
class ComponentFunctionData
{
public:
	//�Լ� Ȱ��ȭ ����
	bool* Enabled = nullptr;

	//�Լ� ������ 
	std::function<void()> FunctionPointer;

	//���۳�Ʈ ������
	Component* ComponentPoiner;
};



 



