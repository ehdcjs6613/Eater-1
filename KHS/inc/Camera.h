#pragma once
#include <DirectXMath.h>
#include <vector>
#include "Component.h"

#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif

/// <summary>
/// ī�޶� ���۳�Ʈ ���Ʈ������ �������� ��Ʈ������ �������ش�
/// </summary>
 
 
class Transform;
class Camera : public Component
{
public:
	EATER_ENGINEDLL Camera();
	virtual ~Camera();

	virtual void Awake();
	virtual void Update();

	//����ī�޶� ����ī�޶�� �����Ų��
	void ChoiceMainCam();
	//���� ī�޶��� �����
	DirectX::XMMATRIX GetView();
	//�������� ������ ī�޶��� �����
	static DirectX::XMMATRIX GetMainView();
	//�������� ����� �����´�
	static DirectX::XMMATRIX GetProj();
	
private:
	Transform* tranform;

	//�������� ��� �����ϱ�
	void CreateProj(float fovY = 0.5f * 3.141592f,float aspect = 1,float zn = 0.1f,float zf = 4000.0f,bool viewPoint = false);
	void CreateView();

	float mNearZ;
	float mFarZ;
	float mAspect;
	float mFovY;
	float mNearWindowHeight;
	float mFarWindowHeight;

	//��������
	DirectX::XMFLOAT4X4 mProj;
	static DirectX::XMMATRIX mProj_M;

	//��
	DirectX::XMFLOAT4X4 mView;
	DirectX::XMMATRIX mView_M;


	//ī�޶� ����Ʈ���� ���� �ε���
	int MyIndex;
	//ī�޶󸮽�Ʈ�� ���ڽ��� �о�ִ´�
	void PushCamList();
	//ī�޶� ����Ʈ
	static std::vector<Camera*> CamList;
	//����ī�޶�
	static Camera* MainCam;
};