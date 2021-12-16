#include "Collider.h"

Collider::Collider() :Size{ 1,1,1}, Center{0,0, 0}
{
	m_Num = 1;
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

float* Collider::GetCenter()
{

	return this->Center;
}

float* Collider::GetSize()
{
	return  this->Size;
}

DirectX::XMFLOAT4X4 Collider::GetWorld()
{
	return this->mWorld;
}

bool Collider::OnPick()
{
	m_Gemetry.SetColor(DirectX::Colors::Green);
	return  true;
}

bool Collider::OffPick()
{
	m_Gemetry.SetColor(DirectX::Colors::Black);
	return false;
}

void Collider::Initialize()
{
}

void Collider::SetSize(float _x, float _y, float _z)
{
	 Size[0] = _x;
	 Size[1] = _y;
	 Size[2] = _z;
}

void Collider::SetCenter(float _x, float _y, float _z)
{
	Center[0] = _x;
	Center[1] = _y;
	Center[2] = _z;
}
