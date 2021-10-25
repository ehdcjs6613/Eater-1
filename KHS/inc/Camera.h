#pragma once
#include <DirectXMath.h>
#include "Component.h"

#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif


class Transform;
class Camera : public Component
{
public:
	EATER_ENGINEDLL Camera();
	virtual ~Camera();

	virtual void Awake();
	virtual void Update();

	//���� ī�޶� ����
	bool MainCamera;

	//�������� ����� �����´�
	DirectX::XMMATRIX GetProj();

	//������� �����´�
	DirectX::XMMATRIX GetView();

	//����İ� �������� ����� ���Ѱ��� �����´�
	DirectX::XMMATRIX GetView_Proj();
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
	DirectX::XMMATRIX mProj_M;

	//��
	DirectX::XMFLOAT4X4 mView;
	DirectX::XMMATRIX mView_M;
};