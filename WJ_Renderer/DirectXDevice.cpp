#include "OneCompile.h"
#include "DirectXDefine.h"
#include "DirectXDevice.h"

DirectXDevice::DirectXDevice()
{
	
	
}

DirectXDevice::~DirectXDevice()
{
	m_pDX11Device->Release();
}


void DirectXDevice::SetDevice(ID3D11Device* _v)
{
	if (nullptr == m_pDX11Device) { m_pDX11Device = std::move(_v); }
}

ID3D11Device* DirectXDevice::GetDevice()
{
	
	return m_pDX11Device;
}


