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
	//���� ī�޶��� �����
	DirectX::XMMATRIX* GetView();
	//�������� ������ ī�޶��� �����
	static DirectX::XMMATRIX* GetMainView();
	//�������� ����� �����´�
	static DirectX::XMMATRIX* GetProj();
	// Main Camera Position
	static DirectX::XMFLOAT3* GetMainPos();

	//OnResize ���� ����� �Լ�
	static void SetSize(int Change_Width, int Change_Height);
	static void CreateProj(int winsizeX,int WinSizeY, bool ViewPoint = false);
private:
	Transform* tranform;

	//�������� ��� �����ϱ�
	void CreateView();

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