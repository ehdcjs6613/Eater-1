#pragma once
#include "ResourcesData.h"
#include "ParserData.h"
#include <functional>
#include <map>
#include "LightHelper.h"


using namespace DirectX;
using namespace SimpleMath;
using namespace ParserData;

class Component;
enum class OBJECT_TYPE
{
	///���� �⺻������ �־�� ������Ʈ ����
	///���߿� �ʿ��Ѱ� �ְ� �ʿ���°� ����

	DEFALT,		//���� �����ʾ����� �⺻��
	GAMEOBJECT,		//�ٸ� ������Ʈ���� ������� �뵵
	BASE,			//��ӱ����� �Ǿ��ִ� ������Ʈ
	SKINNING,		//��Ű���� �߰��� ������Ʈ
	BONE,			//���� �ִ� ������Ʈ
	CAMERA,			//ī�޶� ��ɸ� �ϴ� ������Ʈ
	LIGHT,			//����Ʈ ��ü
	SKYBOX,			//��ī�� �ڽ�
	TEXTURE,		//�Ѱ��� �ؽ��ķε� ������Ʈ(���̽��ΰ��� ������ �簢�� �ؽ���)
	DEBUGOBJECT,			//����� ������Ʈ
	PARTICLE,		//��ƼŬ ������Ʈ
	EFFECT			//����Ʈ ������Ʈ
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
/// ���ӿ������� �׷��ȿ������� ������ ���� ������
/// </summary>
class StaticData
{
public:
	LightData* mLightData;
	MaterialData mMatData[5];
};


/// <summary>
/// ���ӿ������� �׷��ȿ������� ������ �Ѱ��� �޽� ������
/// </summary>
class MeshData
{
public:
	~MeshData()
	{
		IB = nullptr;
		VB = nullptr;
	}

public:
	OBJECT_TYPE ObjType = OBJECT_TYPE::DEFALT;	//������Ʈ Ÿ��

	Indexbuffer* IB = nullptr;			//�ε��� ����
	Vertexbuffer* VB = nullptr;			//���ؽ� ����

	TextureBuffer* Albedo = nullptr;	// DiffuseMap Texture
	TextureBuffer* Normal = nullptr;	// NormalMap Texture
	TextureBuffer* Height = nullptr;	// HeightMap Texture
	TextureBuffer* Roughness = nullptr;	// RoughnessMap Texture
	TextureBuffer* Metallic = nullptr;	// MetallicMap Texture

	UINT Material_Index = 0;			// Material Index

	std::vector<DirectX::SimpleMath::Matrix> BoneOffsetTM; //�� ������ TM

	DirectX::XMMATRIX mWorld = DirectX::XMMatrixIdentity();	//�Ž��� ���� ���
	DirectX::XMMATRIX mLocal = DirectX::XMMatrixIdentity();	//�Ž��� �������
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

		Material = nullptr;
		Animation = nullptr;

		BoneTMList = nullptr;
		BoneList = nullptr;

		Parent = nullptr;
	};

	bool Top_Object = false;		//���� �ֻ��� ������Ʈ���� ����
	bool Bone_Object = false;		//��������Ʈ ����
	bool Skinning_Object = false;		//��Ű�� ������Ʈ ����

	int BoneIndex = -1;						//���ϰ�� �ڽ��� �ε���

	std::string ParentName = "";			//�θ��� �̸�
	std::string	Name = "";			//�ڱ��ڽ��� �̸�

	DirectX::SimpleMath::Matrix* WorldTM = nullptr;	//���� ��Ʈ����
	DirectX::SimpleMath::Matrix* LocalTM = nullptr;	//���� ��Ʈ����

	Indexbuffer* IB = nullptr;			//�ε��� ����
	Vertexbuffer* VB = nullptr;			//���ؽ� ����

	TextureBuffer* Albedo = nullptr;	// DiffuseMap Texture
	TextureBuffer* Normal = nullptr;	// NormalMap Texture
	TextureBuffer* Height = nullptr;	// HeightMap Texture
	TextureBuffer* Roughness = nullptr;	// RoughnessMap Texture
	TextureBuffer* Metallic = nullptr;	// MetallicMap Texture

	ParserData::CMaterial* Material = nullptr;	//���׸��� ����
	ParserData::OneAnimation* Animation = nullptr;	//�ִϸ��̼� ����

	std::vector<Matrix>* BoneTMList = nullptr;	//�� ��Ʈ����
	std::vector<Mesh*>* BoneList = nullptr;	//�� �Ž�

	LoadMeshData* Parent = nullptr;			//�θ� �Ž�
	std::vector<LoadMeshData*> Child;		//�ڽ� �Ž� ����Ʈ


	Matrix* BoneOffset = nullptr;			//�� ��Ʈ����
	Mesh* BoneNumber = nullptr;			//�� �Ž�
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

	std::vector<Matrix>* BoneOffsetList = nullptr;	//�� ��Ʈ����
	std::vector<Mesh*>* BoneList = nullptr;	//�� �Ž�
};

class ModelAnimationData
{
public:
	~ModelAnimationData()
	{

	}
	std::map<std::string, std::vector<OneAnimation*>* > AnimList;
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
	Component* ComponentPointer;

	//���۳�Ʈ ����
	int OrderCount = 0;
};