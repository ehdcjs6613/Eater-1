
#include "Camera.h"
#define PI (float)3.141592653589

DRCamera::DRCamera()
	: mPosition(0.0f, 0.0f, 0.0f),
	mRight(1.0f, 0.0f, 0.0f),
	mUp(0.0f, 1.0f, 0.0f),
	mLook(0.0f, 0.0f, 1.0f)
{
	SetLens(0.25f * PI, 1.0f, 0.0001f, 1000.0f);
}

DRCamera::~DRCamera()
{

}

DirectX::XMVECTOR DRCamera::GetPositionXM() const
{
	return XMLoadFloat3(&mPosition);
}

DirectX::XMFLOAT3 DRCamera::GetPosition() const
{
	return mPosition;
}

void DRCamera::SetPosition(float x, float y, float z)
{
	mPosition = DirectX::XMFLOAT3(x, y, z);
}

void DRCamera::SetPosition(const DirectX::XMFLOAT3& v)
{
	mPosition = v;
}

DirectX::XMVECTOR DRCamera::GetRightXM() const
{
	return XMLoadFloat3(&mRight);
}

DirectX::XMFLOAT3 DRCamera::GetRight() const
{
	return mRight;
}

DirectX::XMVECTOR DRCamera::GetUpXM() const
{
	return XMLoadFloat3(&mUp);
}

DirectX::XMFLOAT3 DRCamera::GetUp() const
{
	return mUp;
}

DirectX::XMVECTOR DRCamera::GetLookXM() const
{
	return XMLoadFloat3(&mLook);
}

DirectX::XMFLOAT3 DRCamera::GetLook() const
{
	return mLook;
}

float DRCamera::GetNearZ() const
{
	return mNearZ;
}

float DRCamera::GetFarZ() const
{
	return mFarZ;
}

float DRCamera::GetAspect() const
{
	return mAspect;
}

float DRCamera::GetFovY() const
{
	return mFovY;
}

float DRCamera::GetFovX() const
{
	float halfWidth = 0.5f * GetNearWindowWidth();
	return 2.0f * atan(halfWidth / mNearZ);
}

float DRCamera::GetNearWindowWidth() const
{
	return mAspect * mNearWindowHeight;
}

float DRCamera::GetNearWindowHeight() const
{
	return mNearWindowHeight;
}

float DRCamera::GetFarWindowWidth() const
{
	return mAspect * mFarWindowHeight;
}

float DRCamera::GetFarWindowHeight() const
{
	return mFarWindowHeight;
}

void DRCamera::SetLens(float fovY, float aspect, float zn, float zf)
{
	// cache properties
	mFovY = fovY;
	mAspect = aspect;
	mNearZ = zn;
	mFarZ = zf;

	mNearWindowHeight = 2.0f * mNearZ * tanf(0.5f * mFovY);
	mFarWindowHeight = 2.0f * mFarZ * tanf(0.5f * mFovY);

	DirectX::XMMATRIX P = DirectX::XMMatrixPerspectiveFovLH(mFovY, mAspect, mNearZ, mFarZ);
	DirectX::XMStoreFloat4x4(&mProj, P);
}

void DRCamera::LookAt(DirectX::FXMVECTOR pos, DirectX::FXMVECTOR target, DirectX::FXMVECTOR worldUp)
{
	// 시선벡터와 월드업을 외적하면 right벡터가 나오고
	// 다시 그 right벡터와 시선벡터를 외적하면 내 up벡터가 나옴
	DirectX::XMVECTOR L = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(target, pos));
	DirectX::XMVECTOR R = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(worldUp, L));
	DirectX::XMVECTOR U = DirectX::XMVector3Cross(L, R);

	XMStoreFloat3(&mPosition, pos);
	XMStoreFloat3(&mLook, L);
	XMStoreFloat3(&mRight, R);
	XMStoreFloat3(&mUp, U);
}

void DRCamera::LookAt(const DirectX::XMFLOAT3& pos, const DirectX::XMFLOAT3& target, const DirectX::XMFLOAT3& up)
{
	DirectX::XMVECTOR P = DirectX::XMLoadFloat3(&pos);
	DirectX::XMVECTOR T = DirectX::XMLoadFloat3(&target);
	DirectX::XMVECTOR U = DirectX::XMLoadFloat3(&up);

	LookAt(P, T, U);
}

DirectX::XMMATRIX DRCamera::View() const
{
	return XMLoadFloat4x4(&mView);
}

DirectX::XMMATRIX DRCamera::Proj() const
{
	return XMLoadFloat4x4(&mProj);
}

DirectX::XMMATRIX DRCamera::ViewProj() const
{
	return XMMatrixMultiply(View(), Proj());
}

void DRCamera::Strafe(float d)
{
	// mPosition += d*mRight
	DirectX::XMVECTOR s = DirectX::XMVectorReplicate(d);
	DirectX::XMVECTOR r = DirectX::XMLoadFloat3(&mRight);
	DirectX::XMVECTOR p = DirectX::XMLoadFloat3(&mPosition);
	XMStoreFloat3(&mPosition, DirectX::XMVectorMultiplyAdd(s, r, p));
}

void DRCamera::Walk(float d)
{
	// mPosition += d*mLook
	DirectX::XMVECTOR s = DirectX::XMVectorReplicate(d);
	DirectX::XMVECTOR l = DirectX::XMLoadFloat3(&mLook);
	DirectX::XMVECTOR p = DirectX::XMLoadFloat3(&mPosition);
	XMStoreFloat3(&mPosition, DirectX::XMVectorMultiplyAdd(s, l, p));
}

void DRCamera::WorldUpDown(float d)
{
	// mPosition += d * mUp
	DirectX::XMVECTOR scale = DirectX::XMVectorReplicate(d);
	DirectX::XMVECTOR up = DirectX::XMLoadFloat3(&mUp);
	DirectX::XMVECTOR position = DirectX::XMLoadFloat3(&mPosition);
	XMStoreFloat3(&mPosition, DirectX::XMVectorMultiplyAdd(scale, up, position));
}

void DRCamera::Pitch(float angle)
{
	// Rotate up and look vector about the right vector.

	DirectX::XMMATRIX R = DirectX::XMMatrixRotationAxis(XMLoadFloat3(&mRight), angle);

	XMStoreFloat3(&mUp, DirectX::XMVector3TransformNormal(XMLoadFloat3(&mUp), R));
	XMStoreFloat3(&mLook, DirectX::XMVector3TransformNormal(XMLoadFloat3(&mLook), R));
}

void DRCamera::RotateY(float angle)
{
	// Rotate the basis vectors about the world y-axis.

	DirectX::XMMATRIX R = DirectX::XMMatrixRotationY(angle);

	XMStoreFloat3(&mRight,	DirectX::XMVector3TransformNormal(XMLoadFloat3(&mRight), R));
	XMStoreFloat3(&mUp,		DirectX::XMVector3TransformNormal(XMLoadFloat3(&mUp), R));
	XMStoreFloat3(&mLook,	DirectX::XMVector3TransformNormal(XMLoadFloat3(&mLook), R));
}

void DRCamera::UpdateViewMatrix()
{
	DirectX::XMVECTOR R = XMLoadFloat3(&mRight);
	DirectX::XMVECTOR U = XMLoadFloat3(&mUp);
	DirectX::XMVECTOR L = XMLoadFloat3(&mLook);
	DirectX::XMVECTOR P = XMLoadFloat3(&mPosition);

	// Keep camera's axes orthogonal to each other and of unit length.
	L = DirectX::XMVector3Normalize(L);
	U = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(L, R));

	// U, L already ortho-normal, so no need to normalize cross product.
	R = DirectX::XMVector3Cross(U, L);

	// Fill in the view matrix entries.
	float x = -DirectX::XMVectorGetX(DirectX::XMVector3Dot(P, R));
	float y = -DirectX::XMVectorGetX(DirectX::XMVector3Dot(P, U));
	float z = -DirectX::XMVectorGetX(DirectX::XMVector3Dot(P, L));

	XMStoreFloat3(&mRight, R);
	XMStoreFloat3(&mUp, U);
	XMStoreFloat3(&mLook, L);

	mView(0, 0) = mRight.x;
	mView(1, 0) = mRight.y;
	mView(2, 0) = mRight.z;
	mView(3, 0) = x;

	mView(0, 1) = mUp.x;
	mView(1, 1) = mUp.y;
	mView(2, 1) = mUp.z;
	mView(3, 1) = y;

	mView(0, 2) = mLook.x;
	mView(1, 2) = mLook.y;
	mView(2, 2) = mLook.z;
	mView(3, 2) = z;

	mView(0, 3) = 0.0f;
	mView(1, 3) = 0.0f;
	mView(2, 3) = 0.0f;
	mView(3, 3) = 1.0f;
}
