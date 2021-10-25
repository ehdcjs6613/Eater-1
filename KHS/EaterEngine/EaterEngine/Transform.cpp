#include "Component.h"
#include "Transform.h"
#include "DebugManager.h"

Transform::Transform()
{
	Position = { 0,0,0 };
	Rotation = { 0,0,0 };
	Scale = { 1,1,1 };
	World_M = DirectX::XMMatrixIdentity();

	Local_UP	= { 0,0,0 };
	Local_Right = { 0,0,0 };
	Local_Look	= { 0,0,0 };

	LocalUpdate = false;
}

Transform::~Transform()
{

}

void Transform::Awake()
{

}

void Transform::StartUpdate()
{
	//���� ��ǥ���� ������� ���� ����� ���Ѵ�
	UpdateWorldXM();

	
	//���� ��ǥ�� ������� ������ǥ�� �������ش�
	//�ٸ� ����ڰ� ���Ҷ���
	if (LocalUpdate != false)
	{
		UpdateLocalPosition();
	}
}

DirectX::XMFLOAT3 Transform::GetLocalPosition_UP()
{
	return Local_UP;
}

DirectX::XMFLOAT3 Transform::GetLocalPosition_Right()
{
	return Local_Right;
}

DirectX::XMFLOAT3 Transform::GetLocalPosition_Look()
{
	return Local_Look;
}

void Transform::SetLocalPosition(float X, float Y, float Z)
{
	Position =
	{
		Position.x + (Local_Right.x * X),
		Position.y + (Local_Right.y * X),
		Position.z + (Local_Right.z * X)
	};

	Position =
	{
		Position.x + (Local_UP.x * Y),
		Position.y + (Local_UP.y * Y),
		Position.z + (Local_UP.z * Y)
	};


	Position =
	{
		Position.x + (Local_Look.x * Z),
		Position.y + (Local_Look.y * Z),
		Position.z + (Local_Look.z * Z)
	};
}

void Transform::SetTranlate(float X, float Y, float Z)
{
	Position.x += X;
	Position.y += Y;
	Position.z += Z;
}

void Transform::SetTranlate(DirectX::XMFLOAT3 mPos)
{
	Position.x += mPos.x;
	Position.y += mPos.y;
	Position.z += mPos.z;
}

void Transform::SetRotate(float X, float Y, float Z)
{
	Rotation.x += X;
	Rotation.y += Y;
	Rotation.z += Z;
}

void Transform::SetRotate(DirectX::XMFLOAT3 mRot)
{
	Rotation.x += mRot.x;
	Rotation.y += mRot.y;
	Rotation.z += mRot.z;
}

void Transform::SetScale(float X, float Y, float Z)
{
	Scale.x += X;
	Scale.y += Y;
	Scale.z += Z;
}

void Transform::SetScale(DirectX::XMFLOAT3 mScl)
{
	Scale.x += mScl.x;
	Scale.y += mScl.y;
	Scale.z += mScl.z;
}

DirectX::XMMATRIX Transform::GetPositionXM()
{
	return PositionXM;
}

DirectX::XMMATRIX Transform::GetRotationXM()
{
	return RotationXM;
}

DirectX::XMMATRIX Transform::GetScaleXM()
{
	return ScaleXM;
}

DirectX::XMMATRIX Transform::GetWorld()
{
	return World_M;
}

void Transform::SetLocalUpdate(bool isUpdate)
{
	LocalUpdate = isUpdate;
}

DirectX::XMMATRIX Transform::CreateXMPos4x4()
{
	DirectX::XMFLOAT4X4 Position_4x4;
	Position_4x4._11 = 1;				Position_4x4._12 = 0;			Position_4x4._13 = 0;			Position_4x4._14 = 0;
	Position_4x4._21 = 0;				Position_4x4._22 = 1;			Position_4x4._23 = 0;			Position_4x4._24 = 0;
	Position_4x4._31 = 0;				Position_4x4._32 = 0;			Position_4x4._33 = 1;			Position_4x4._34 = 0;
	Position_4x4._41 = Position.x;		Position_4x4._42 = Position.y;	Position_4x4._43 = Position.z;	Position_4x4._44 = 1;

	return XMLoadFloat4x4(&Position_4x4);
}

DirectX::XMMATRIX Transform::CreateXMRot4x4()
{
	float radX = Rotation.x * 3.141592f / 180;
	float radY = Rotation.y * 3.141592f / 180;
	float radZ = Rotation.z * 3.141592f / 180;
	DirectX::XMMATRIX _P = DirectX::XMMatrixRotationX(radX);
	DirectX::XMMATRIX _Y = DirectX::XMMatrixRotationY(radY);
	DirectX::XMMATRIX _R = DirectX::XMMatrixRotationZ(radZ);

	return _R * _Y * _P;
}

DirectX::XMMATRIX Transform::CreateXMScl4x4()
{
	DirectX::XMFLOAT4X4 Scale_4x4;
	Scale_4x4._11 = Scale.x;	Scale_4x4._12 = 0;			Scale_4x4._13 = 0;			Scale_4x4._14 = 0;
	Scale_4x4._21 = 0;			Scale_4x4._22 = Scale.y;	Scale_4x4._23 = 0;			Scale_4x4._24 = 0;
	Scale_4x4._31 = 0;			Scale_4x4._32 = 0;			Scale_4x4._33 = Scale.z;	Scale_4x4._34 = 0;
	Scale_4x4._41 = 0;			Scale_4x4._42 = 0;			Scale_4x4._43 = 0;			Scale_4x4._44 = 1;

	return XMLoadFloat4x4(&Scale_4x4);
}

void Transform::UpdateWorldXM()
{
	PositionXM	= CreateXMPos4x4();
	RotationXM	= CreateXMRot4x4();
	ScaleXM		= CreateXMScl4x4();

	World_M = ScaleXM * RotationXM * PositionXM;
}

void Transform::UpdateLocalPosition()
{
	//���� ��� ���ϱ�
	DirectX::XMVECTOR det = DirectX::XMMatrixDeterminant(World_M);
	//������ǥ�� ���ϱ����� ������ ������� ����
	DirectX::XMMATRIX LocalPos = DirectX::XMMatrixInverse(&det, World_M);
	DirectX::XMFLOAT4X4 A_Master4x4;
	XMStoreFloat4x4(&A_Master4x4, LocalPos);

	//������ ���� �־��ش�
	Local_Right.x = A_Master4x4._11;
	Local_Right.y = A_Master4x4._12;
	Local_Right.z = A_Master4x4._13;

	Local_UP.x = A_Master4x4._21;
	Local_UP.y = A_Master4x4._22;
	Local_UP.z = A_Master4x4._23;

	Local_Look.x = A_Master4x4._31;
	Local_Look.y = A_Master4x4._32;
	Local_Look.z = A_Master4x4._33;
}






