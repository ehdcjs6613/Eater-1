#pragma once

#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif

#include <DirectXMath.h>
#include "Component.h"

class Transform :public Component
{
public:
	EATER_ENGINEDLL Transform();
	virtual ~Transform();
	
	//�����ɶ� �ѹ�
	void Awake();
	//������� ����Ǵ� ������Ʈ
	void TransformUpdate();

public:
	//��ġ
	DirectX::XMFLOAT3 Position;
	//ȸ��
	DirectX::XMFLOAT3 Rotation;
	//ũ��
	DirectX::XMFLOAT3 Scale;

	

	///���� �Լ��� ������������ SetLocalUpdate
	///���Լ��� ������Ѽ� ���þ�����Ʈ�� �ϴ��� Ȯ������
	//���� ������ ���͸� �����´�
	DirectX::XMFLOAT3 GetLocalPosition_UP();
	//���� �����ʹ��� ���͸� �����´�
	DirectX::XMFLOAT3 GetLocalPosition_Right();
	//���� �չ��� ���͸� �����´�
	DirectX::XMFLOAT3 GetLocalPosition_Look();


	//������ġ���� ���� ������
	EATER_ENGINEDLL void SetLocalPosition(float X, float Y, float Z);
	EATER_ENGINEDLL void SetTranlate(float X, float Y, float Z);
	EATER_ENGINEDLL void SetTranlate(DirectX::XMFLOAT3 mPos);

	//���� ȸ������ ���� ������
	EATER_ENGINEDLL void SetRotate(float X, float Y, float Z);
	EATER_ENGINEDLL void SetRotate(DirectX::XMFLOAT3 mRot);

	//���� ũ�Ⱚ�� ���� ������
	EATER_ENGINEDLL void SetScale(float X, float Y, float Z);
	EATER_ENGINEDLL void SetScale(DirectX::XMFLOAT3 mScl);

	//��ġ,ȸ��,ũ�� ��ĵ��� ���� �����´�
	EATER_ENGINEDLL DirectX::XMMATRIX GetPositionXM();
	EATER_ENGINEDLL DirectX::XMMATRIX GetRotationXM();
	EATER_ENGINEDLL DirectX::XMMATRIX GetScaleXM();

	//�����Ʈ������ ������
	EATER_ENGINEDLL DirectX::XMMATRIX	GetWorld();

	//������ǥ���� �������� ������Ʈ ���ٰ��ΰ� ����
	EATER_ENGINEDLL void SetLocalUpdate(bool isUpdate);
private:
	//���� ��ġ ȸ�� ũ�Ⱚ�� ������ ����� ���Ѵ�
	DirectX::XMMATRIX CreateXMPos4x4();
	DirectX::XMMATRIX CreateXMRot4x4();
	DirectX::XMMATRIX CreateXMScl4x4();

	///���� ��ǥ�� ������ġ���� ���ù������� 1��ŭ ������ ��ǥ��
	///���� Ŭ���ʿ��� �ٲ��ʿ䰡���⶧���� �������°͸� ����
	//�ڱ� �������� ���������� 1��ŭ ������ ��ǥ
	DirectX::XMFLOAT3 Local_UP;
	//�ڱ� �������� ������ �������� 1��ŭ ������ ��ǥ
	DirectX::XMFLOAT3 Local_Right;
	//�ڱ� �������� �չ������� 1��ŭ ������ ��ǥ
	DirectX::XMFLOAT3 Local_Look;


	//������ ��ĵ��� ���κ���
	DirectX::XMMATRIX PositionXM;
	DirectX::XMMATRIX RotationXM;
	DirectX::XMMATRIX ScaleXM;

	///��� ������Ʈ �Լ���
	//������ǥ�� �����Ӹ��� ���Ұ��ΰ� ����
	bool LocalUpdate;

	//������Ʈ���� �Ź� ������� ����
	void UpdateWorldXM();
	//������ǥ�� ������Ʈ �����ش�
	void UpdateLocalPosition();

	//���� ������Ʈ�� ��ġ ȸ�� ũ�Ⱚ�� ��ΰ��� ���� ���
	DirectX::XMMATRIX World_M;
};