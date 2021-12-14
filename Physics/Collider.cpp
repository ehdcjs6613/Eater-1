#include "Collider.h"

Collider::Collider()
{
}

Collider::~Collider()
{
}

void Collider::Awake()
{
}

void Collider::Start()
{
}

void Collider::StartUpdate()
{
}

void Collider::TransformUpdate()
{
}

void Collider::PhysicsUpdate()
{
}

void Collider::Update()
{
}

void Collider::EndUpdate()
{
}

void Collider::SetDevice(ID3D11Device* _pDevice)
{
	this->md3dDevice  = _pDevice;
}

void Collider::SetDeviceContext(ID3D11DeviceContext* _pDeviceContext)
{
	this->md3dImmediateContext = _pDeviceContext;
}

ID3D11Device* Collider::GetDevice()
{
	return this->md3dDevice;
}

ID3D11DeviceContext* Collider::GetDeviceContext()
{
	return this->md3dImmediateContext;
}

void Collider::Initialize()
{
}
