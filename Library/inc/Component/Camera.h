#pragma once
#include <DirectXMath.h>
#include <vector>
#include "Component.h"
#include "EaterEngineDLL.h"

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
	// Camera Position
	DirectX::XMFLOAT3* GetPos();
	// Camera View TexSpace
	DirectX::XMMATRIX* GetViewTex();
	//���� ī�޶��� �����
	DirectX::XMMATRIX* GetView();
	//�������� ����� �����´�
	DirectX::XMMATRIX* GetProj();

	//ī�޶��� ���� ��ǥ�� �����´�
	//static DirectX::XMFLOAT3  GetLocalPos_Up();
	//static DirectX::XMFLOAT3  GetLocalPos_Right();
	//static DirectX::XMFLOAT3  GetLocalPos_Look();

	//OnResize ���� ����� �Լ�
	void SetSize(int Change_Width, int Change_Height);
	void CreateProj(int winsizeX,int WinSizeY, bool ViewPoint = false);
private:
	Transform* tranform;

	//�������� ��� �����ϱ�
	void CreateView();

	//��������
	DirectX::XMFLOAT4X4 mProj;
	DirectX::XMMATRIX mProj_M;

	//��
	DirectX::XMFLOAT4X4 mView;
	DirectX::XMMATRIX mView_M;

	//ViewTexSpace
	DirectX::XMMATRIX mViewTex_M;

	//ī�޶� ����Ʈ���� ���� �ε���
	int MyIndex;
	//ī�޶󸮽�Ʈ�� ���ڽ��� �о�ִ´�
	void PushCamList();
	//ī�޶� ����Ʈ
	static std::vector<Camera*> CamList;

public:
	//����ī�޶�
	static Camera* g_MainCam;
};