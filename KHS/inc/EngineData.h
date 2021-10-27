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
	DirectX::XMMATRIX mViewMX;
	DirectX::XMMATRIX mProj;
};

//�Ѱ��� �Ž��� �����ϴ� ������
class MeshData
{
public:
	MeshData()= default;
	~MeshData() {};

	//������Ʈ Ÿ��
	OBJECT_TYPE ObjType = OBJECT_TYPE::Default;

	//�Ž� ���� ���
	DirectX::XMMATRIX mWorld;
	DirectX::XMMATRIX mlocal;

	//�ִϸ��̼�



	//Mesh ��ġ��
	DirectX::XMFLOAT3 Pos;
};



 



