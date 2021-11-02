#include "OneCompile.h"
#include "DirectXDefine.h"
#include "DirectXRasterizerState.h"

DirectXRasterizerState::DirectXRasterizerState() : m_State(StateRS::eSolid), m_pFrameRS(nullptr)
{
	//�⺻������ �ʱ�ȭ
}

DirectXRasterizerState::~DirectXRasterizerState()
{
	m_pFrameRS->Release();
}

HRESULT DirectXRasterizerState::Create(ID3D11Device* _pDevice, StateRS _StateRS)
{
	m_State = _StateRS;
	//Rasterizer State�� ������ش�. 
	HRESULT hr = E_FAIL;

	D3D11_RASTERIZER_DESC RasterRizeDESC;

	ZeroMemory(&RasterRizeDESC, sizeof(D3D11_RASTERIZER_DESC));

	//switch ������ ��� �׸��� ���Ѵ�.
	switch (m_State)
	{
		case StateRS::eWireFrame:
		{

			RasterRizeDESC.FillMode = D3D11_FILL_WIREFRAME;
			RasterRizeDESC.CullMode = D3D11_CULL_BACK;
			RasterRizeDESC.FrontCounterClockwise = false;
			RasterRizeDESC.DepthClipEnable = true;
		}
		break;
		case StateRS::eSolid:
		{

			RasterRizeDESC.FillMode = D3D11_FILL_SOLID;
			RasterRizeDESC.CullMode = D3D11_CULL_BACK;
			RasterRizeDESC.FrontCounterClockwise = false;
			RasterRizeDESC.DepthClipEnable = true;
		}
		break;

	}


	HR(_pDevice->CreateRasterizerState(&RasterRizeDESC, &m_pFrameRS));

	hr = S_OK;

	return hr;
}

ID3D11RasterizerState* DirectXRasterizerState::GetFrameRS()
{
	return m_pFrameRS;
}
