#include "DirectDefine.h"
#include "D3D11Graphic.h"
#include "ToolKitDefine.h"

D3D11Graphic::D3D11Graphic(HWND hwnd, int screenWidth, int screenHeight)
{
	Initialize(hwnd, screenWidth, screenHeight);
}

D3D11Graphic::~D3D11Graphic()
{

}

void D3D11Graphic::Initialize(HWND hwnd, int screenWidth, int screenHeight)
{
	UINT createDeviceFlags = 0;

#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// ���� ü�� ������ �ʱ�ȭ..
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	// swapChainDesc�� ���� �� ���۷� ����..
	swapChainDesc.BufferCount = 1;

	// �� ������ �ʺ�� ���̸� ����..
	swapChainDesc.BufferDesc.Width = screenWidth;
	swapChainDesc.BufferDesc.Height = screenHeight;

	// �� ���ۿ� �Ϲ� 32 ��Ʈ ǥ���� ����..
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// �� ������ ������� ����..
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

	// ��ĵ ���� ���� �� ������ �������� �������� ����..
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// �� ������ ��� ����..
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
	swapChainDesc.OutputWindow = (HWND)hwnd;

	// ��Ƽ ���ø��� ���ϴ�..
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = true;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// �߰� �÷��� ���� �� ��..
	swapChainDesc.Flags = createDeviceFlags;

	// featureLevel�� DirectX 11�� ����..
	D3D_FEATURE_LEVEL featurelevel = D3D_FEATURE_LEVEL_11_0;

	// ���� ü��, Direct3D ��ġ �� Direct3D ��ġ ���ؽ�Ʈ ����..
	/// MSDN���� SwapChain �� Device �� �ѹ��� �������ִ� �Լ��� ������..
	HR(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featurelevel, 1,
		D3D11_SDK_VERSION, &swapChainDesc, &m_SwapChain, &m_Device, NULL, &m_DeviceContext));
}

void D3D11Graphic::Release()
{

}

void D3D11Graphic::CreateBuffer(D3D11_BUFFER_DESC* bufferDesc, D3D11_SUBRESOURCE_DATA* subDesc, ID3D11Buffer** buffer)
{
	HR(m_Device->CreateBuffer(bufferDesc, subDesc, buffer));
}

void D3D11Graphic::CreateTextureBuffer(std::string filePath, ID3D11Resource** resource, ID3D11ShaderResourceView** srv)
{
	std::wstring wPath(filePath.begin(), filePath.end());

	// Ȯ���ڿ� ���� �ؽ�ó ���� �ε� ���..
	if (filePath.rfind(".dds") != std::string::npos)
	{
		HR(DirectX::CreateDDSTextureFromFile(m_Device.Get(), wPath.c_str(), resource, srv));
	}
	else
	{
		HR(DirectX::CreateWICTextureFromFile(m_Device.Get(), wPath.c_str(), resource, srv));
	}
}

void D3D11Graphic::CreateBackBuffer(UINT width, UINT height, ID3D11Texture2D** tex2D, ID3D11RenderTargetView** rtv, ID3D11ShaderResourceView** srv)
{
	// BackBuffer Resize..
	HR(m_SwapChain->ResizeBuffers(1, (UINT)width, (UINT)height, DXGI_FORMAT_R8G8B8A8_UNORM, 0));

	// Get Swap Chain Back Buffer Pointer..
	HR(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(tex2D)));

	// BackBuffer Resource Resize..
	HR(m_Device->CreateRenderTargetView(*tex2D, nullptr, rtv));
	HR(m_Device->CreateShaderResourceView(*tex2D, nullptr, srv));
}

void D3D11Graphic::CreateTexture2D(D3D11_TEXTURE2D_DESC* texDesc, ID3D11Texture2D** tex2D)
{
	if (texDesc == nullptr) return;

	// Texture2D Resource ����..
	HR(m_Device->CreateTexture2D(texDesc, 0, tex2D));
}

void D3D11Graphic::CreateDepthStencilView(ID3D11Texture2D* tex2D, D3D11_DEPTH_STENCIL_VIEW_DESC* dsvDesc, ID3D11DepthStencilView** dsv)
{
	// Texture2D Description ����..
	D3D11_TEXTURE2D_DESC texDesc;
	tex2D->GetDesc(&texDesc);

	// BindFlag Check..
	if (texDesc.BindFlags & D3D11_BIND_DEPTH_STENCIL)
	{
		// RenderTargetView Resource ����..
		HR(m_Device->CreateDepthStencilView(tex2D, dsvDesc, dsv));
	}
}

void D3D11Graphic::CreateRenderTargetView(ID3D11Texture2D* tex2D, D3D11_RENDER_TARGET_VIEW_DESC* rtvDesc, ID3D11RenderTargetView** rtv)
{
	// Texture2D Description ����..
	D3D11_TEXTURE2D_DESC texDesc;
	tex2D->GetDesc(&texDesc);

	// BindFlag Check..
	if (texDesc.BindFlags & D3D11_BIND_RENDER_TARGET)
	{
		// RenderTargetView Resource ����..
		HR(m_Device->CreateRenderTargetView(tex2D, rtvDesc, rtv));
	}
}

void D3D11Graphic::CreateShaderResourceView(ID3D11Texture2D* tex2D, D3D11_SHADER_RESOURCE_VIEW_DESC* srvDesc, ID3D11ShaderResourceView** srv)
{
	// Texture2D Description ����..
	D3D11_TEXTURE2D_DESC texDesc;
	tex2D->GetDesc(&texDesc);

	// BindFlag Check..
	if (texDesc.BindFlags & D3D11_BIND_SHADER_RESOURCE)
	{
		// ShaderResourceView Resource ����..
		HR(m_Device->CreateShaderResourceView(tex2D, srvDesc, srv));
	}
}

void D3D11Graphic::CreateUnorderedAccessView(ID3D11Texture2D* tex2D, D3D11_UNORDERED_ACCESS_VIEW_DESC* uavDesc, ID3D11UnorderedAccessView** uav)
{
	// Texture2D Description ����..
	D3D11_TEXTURE2D_DESC texDesc;
	tex2D->GetDesc(&texDesc);

	// BindFlag Check..
	if (texDesc.BindFlags & D3D11_BIND_UNORDERED_ACCESS)
	{
		// UnorderedAccessView Resource ����..
		HR(m_Device->CreateUnorderedAccessView(tex2D, uavDesc, uav));
	}
}

void D3D11Graphic::CreateDepthStencilState(D3D11_DEPTH_STENCIL_DESC* dssDesc, ID3D11DepthStencilState** dss)
{
	if (dssDesc == nullptr) return;

	// DepthStencilState Resource ����..
	HR(m_Device->CreateDepthStencilState(dssDesc, dss));
}

void D3D11Graphic::CreateRasterizerState(D3D11_RASTERIZER_DESC* rsDesc, ID3D11RasterizerState** rs)
{
	if (rsDesc == nullptr) return;

	// RasterizerState Resource ����..
	HR(m_Device->CreateRasterizerState(rsDesc, rs));
}

void D3D11Graphic::CreateBlendState(D3D11_BLEND_DESC* bsDesc, ID3D11BlendState** bs)
{
	if (bsDesc == nullptr) return;

	// BlendState Resource ����..
	HR(m_Device->CreateBlendState(bsDesc, bs));
}

void D3D11Graphic::CreateSamplerState(D3D11_SAMPLER_DESC* ssDesc, ID3D11SamplerState** ss)
{
	if (ssDesc == nullptr) return;

	// SamplerState Resource ����..
	HR(m_Device->CreateSamplerState(ssDesc, ss));
}

Microsoft::WRL::ComPtr<ID3D11Device> D3D11Graphic::GetDevice()
{
	return m_Device;
}

Microsoft::WRL::ComPtr<ID3D11DeviceContext> D3D11Graphic::GetContext()
{
	return m_DeviceContext;
}

Microsoft::WRL::ComPtr<IDXGISwapChain> D3D11Graphic::GetSwapChain()
{
	return m_SwapChain;
}

