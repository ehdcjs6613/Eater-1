#include "OneCompile.h"
#include "DirectXDefine.h"
#include "DirectXAdapter.h"


DirectXAdapter::DirectXAdapter()
{
}

DirectXAdapter::~DirectXAdapter()
{
}

HRESULT DirectXAdapter::GetAdapterInfo()
{
	// DXGI버전별로 다름
	IDXGIAdapter1* pAdapter;
	IDXGIFactory1* pFactory = NULL;

	HRESULT hr = S_OK;

	// DXGIFactory 개체 생성(DXGI.lib 필요)
	if (FAILED(CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&pFactory)))
	{
		return E_FAIL;
	}

	hr = pFactory->EnumAdapters1(0, &pAdapter);

	if (hr != DXGI_ERROR_NOT_FOUND)
	{
		pAdapter->GetDesc1(&m_AdapterDesc);
	}
	SAFE_RELEASE(pAdapter);
	SAFE_RELEASE(pFactory);

	return E_NOTIMPL;
}

DXGI_ADAPTER_DESC1 DirectXAdapter::GetAdapter()
{
	return m_AdapterDesc;
}
