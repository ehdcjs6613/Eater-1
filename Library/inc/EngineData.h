#pragma once
#include <map>
#include <functional>
#include "ResourcesData.h"
#include "ParserData.h"
#include "LightHelper.h"

using namespace DirectX;
using namespace SimpleMath;
using namespace ParserData;

class Component;

typedef enum RENDER_OPTION_DESC : UINT
{
	RENDER_GAMMA_CORRECTION	= 0x00000001,
	RENDER_SHADOW			= 0x00000010,
	RENDER_SSAO				= 0x00000100,
}RENDER_OPTION_DESC;

enum class OBJECT_TYPE
{
	///���� �⺻������ �־�� ������Ʈ ����
	///���߿� �ʿ��Ѱ� �ְ� �ʿ���°� ����

	DEFALT,			//���� �����ʾ����� �⺻��
	GAMEOBJECT,		//�ٸ� ������Ʈ���� ������� �뵵
	BASE,			//��ӱ����� �Ǿ��ִ� ������Ʈ
	SKINNING,		//��Ű���� �߰��� ������Ʈ
	BONE,			//���� �ִ� ������Ʈ
	TERRAIN,		//�ͷ��� ������Ʈ
	CAMERA,			//ī�޶� ��ɸ� �ϴ� ������Ʈ
	LIGHT,			//����Ʈ ��ü
	SKYBOX,			//��ī�� �ڽ�
	TEXTURE,		//�Ѱ��� �ؽ��ķε� ������Ʈ(���̽��ΰ��� ������ �簢�� �ؽ���)
	DEBUGOBJECT,	//����� ������Ʈ
	PARTICLE,		//��ƼŬ ������Ʈ
	EFFECT			//����Ʈ ������Ʈ
};

class MaterialBuffer
{
public:
	UINT Material_Index = 0;				// Material Index

	MaterialData* Material_Data = nullptr;	// Material Data

	TextureBuffer* Albedo = nullptr;		// DiffuseMap Texture
	TextureBuffer* Normal = nullptr;		// NormalMap Texture
	TextureBuffer* Roughness = nullptr;		// RoughnessMap Texture
	TextureBuffer* Metallic = nullptr;		// MetallicMap Texture

	Vector4 Color_Base;			// Base Color
	Vector4 Color_Add;			// Add Color
};

/// <summary>
/// ���ӿ������� �׷��ȿ������� ������ �۷ι� ������
/// </summary>
class GlobalData
{
public:
	//ī�޶� ������
	XMMATRIX* mCamView;	// Camera View Matrix
	XMMATRIX* mCamProj;	// Camera Proj Matrix
	XMMATRIX* mCamPT;		// Camera Proj * TexSpace Matrix
	XMFLOAT3* mCamPos;		// Camera Pos

	XMMATRIX* mLightView;	// Light View Matrix
	XMMATRIX* mLightProj;	// Light Proj Matrix
	XMMATRIX* mLightVPT;	// Light View * Proj * TexSpace Matrix

	LightData* mLightData;
	std::vector<MaterialData*> mMatData;
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
	OBJECT_TYPE ObjType = OBJECT_TYPE::DEFALT;		//������Ʈ Ÿ��

	Indexbuffer* IB = nullptr;						//�ε��� ����
	Vertexbuffer* VB = nullptr;						//���ؽ� ����

	std::vector<MaterialBuffer*> Material_List;		// Material List

	std::vector<Matrix> BoneOffsetTM;				//�� ������ TM

	XMMATRIX mWorld = XMMatrixIdentity();			//�Ž��� ���� ���
	XMMATRIX mLocal = XMMatrixIdentity();			//�Ž��� �������
	XMMATRIX mTexTM = XMMatrixIdentity();
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

	MESH_TYPE MeshType;				// �Ž� Ÿ��

	bool Top_Object = false;		//���� �ֻ��� ������Ʈ���� ����

	int BoneIndex = -1;				//���ϰ�� �ڽ��� �ε���

	std::string ParentName = "";	//�θ��� �̸�
	std::string	Name = "";			//�ڱ��ڽ��� �̸�

	Matrix* WorldTM = nullptr;	//���� ��Ʈ����
	Matrix* LocalTM = nullptr;	//���� ��Ʈ����

	Indexbuffer* IB = nullptr;			//�ε��� ����
	Vertexbuffer* VB = nullptr;			//���ؽ� ����

	TextureBuffer* Albedo = nullptr;	// DiffuseMap Texture
	TextureBuffer* Normal = nullptr;	// NormalMap Texture
	TextureBuffer* Roughness = nullptr;	// RoughnessMap Texture
	TextureBuffer* Metallic = nullptr;	// MetallicMap Texture

	std::vector<UINT> Index_List;		//	
	std::vector<Vector3> Vertex_List;	//

	ParserData::CMaterial* Material = nullptr;	//���׸��� ����
	ParserData::OneAnimation* Animation = nullptr;	//�ִϸ��̼� ����

	std::vector<Matrix>* BoneTMList = nullptr;	//�� ��Ʈ����
	std::vector<Mesh*>* BoneList = nullptr;	//�� �Ž�

	LoadMeshData* Parent = nullptr;			//�θ� �Ž�
	std::vector<LoadMeshData*> Child;		//�ڽ� �Ž� ����Ʈ

	Matrix* BoneOffset = nullptr;			//�� ��Ʈ����
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