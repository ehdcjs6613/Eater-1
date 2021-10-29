
#include "DH3DEngine.h"
#include "SkyBox.h"
#include "D2DSupport.h"
#include "AxisGrid.h"

DH3DEngine::DH3DEngine()
{

}

DH3DEngine::~DH3DEngine()
{
	InputLayouts::DestroyAll();
	Effects::DestroyAll();
}

void DH3DEngine::Initialize(HWND hWnd, int screenWidth, int screenHeight)
{
	g_hWnd = hWnd;
	g_Screen_Width = screenWidth;
	g_Screen_Height = screenHeight;
	CreateGraphicResource();
	Effects::InitAll(DX11_Device);
	InputLayouts::InitAll(DX11_Device);
}

void DH3DEngine::CreateGraphicResource()
{
	IDXGIFactory* factory;
	IDXGIAdapter* adapter;
	IDXGIOutput* adapterOutput;
	unsigned int numModes, i, numerator, denominator;
	unsigned long long stringLength;
	DXGI_MODE_DESC* displayModeList;
	DXGI_ADAPTER_DESC adapterDesc;
	int error;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ID3D11Texture2D* backBufferPtr;
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	D3D11_RASTERIZER_DESC rasterDesc;
	D3D11_VIEWPORT viewport;
	float fieldOfView, screenAspect;

	// DXGI ���丮 ����.
	HR(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory));

	// Use the factory to create an adapter for the primary graphics interface (video card).
	HR(factory->EnumAdapters(0, &adapter));

	// Enumerate the primary adapter output (monitor).
	HR(adapter->EnumOutputs(0, &adapterOutput));

	// Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output (monitor).
	HR(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL));

	// Create a list to hold all the possible display modes for this monitor/video card combination.
	displayModeList = new DXGI_MODE_DESC[numModes];

	if (!displayModeList)
	{
		return;
	}

	// Now fill the display mode list structures.
	HR(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList));

	// Now go through all the display modes and find the one that matches the screen width and height.
	// When a match is found store the numerator and denominator of the refresh rate for that monitor.
	for (i = 0; i < numModes; i++)
	{
		if (displayModeList[i].Width == (unsigned int)g_Screen_Width)
		{
			if (displayModeList[i].Height == (unsigned int)g_Screen_Height)
			{
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	// Get the adapter (video card) description.
	HR(adapter->GetDesc(&adapterDesc));

	// ����ī�� �޸𸮸� MB ������ �ٲ��ش�.
	Video_Card_Memory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	// Release the display mode list.
	delete[] displayModeList;
	displayModeList = 0;

	// Release the adapter output.
	SAFE_RELEASE(adapterOutput);

	// Release the adapter.
	SAFE_RELEASE(adapter);

	// Release the factory.
	SAFE_RELEASE(factory);

	// Initialize the swap chain description.
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	// Set to a single back buffer.
	swapChainDesc.BufferCount = 1;

	// Set the width and height of the back buffer.
	swapChainDesc.BufferDesc.Width = g_Screen_Width;
	swapChainDesc.BufferDesc.Height = g_Screen_Height;

	// Set regular 32-bit surface for the back buffer.
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Set the refresh rate of the back buffer.

	// Vsync ����
	//swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
	//swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;

	// Vsync ������
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

	// Set the usage of the back buffer.
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// Set the handle for the window to render to.
	swapChainDesc.OutputWindow = g_hWnd;

	// Turn multisampling off.
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	/// Ǯ ��ũ�� ���.
	swapChainDesc.Windowed = true;

	// Set the scan line ordering and scaling to unspecified.
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Discard the back buffer contents after presenting.
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// Don't set the advanced flags.
	swapChainDesc.Flags = 0;

	// Set the feature level to DirectX 11.
	featureLevel = D3D_FEATURE_LEVEL_11_0;

	// ���� ü�ΰ� Device�� ���� ����. (D2D�� �����ϱ� ���� �ɼ����� BGRA �� ���� �� �ξ���.)
	HR(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_BGRA_SUPPORT, &featureLevel, 1,
		D3D11_SDK_VERSION, &swapChainDesc, &DX11_Swap_Chain, &DX11_Device, NULL, &DX11_Device_Context));

	// Get the pointer to the back buffer.
	HR(DX11_Swap_Chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr));

	// Create the render target view with the back buffer pointer.
	HR(DX11_Device->CreateRenderTargetView(backBufferPtr, NULL, &DX11_Render_Target_View));

	// Release pointer to the back buffer as we no longer need it.
	SAFE_RELEASE(backBufferPtr);

	// Initialize the description of the depth buffer.
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	// Set up the description of the depth buffer.
	depthBufferDesc.Width = g_Screen_Width;
	depthBufferDesc.Height = g_Screen_Height;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	// Create the texture for the depth buffer using the filled out description.
	HR(DX11_Device->CreateTexture2D(&depthBufferDesc, NULL, &DX11_Depth_Stencil_Buffer));

	// Initialize the description of the stencil state.
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	// Set up the description of the stencil state.
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create the depth stencil state.
	HR(DX11_Device->CreateDepthStencilState(&depthStencilDesc, &DX11_Depth_Stencil_State));

	// Set the depth stencil state.
	DX11_Device_Context->OMSetDepthStencilState(DX11_Depth_Stencil_State, 1);

	// Initialize the depth stencil view.
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	// Set up the depth stencil view description.
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	// Create the depth stencil view.
	HR(DX11_Device->CreateDepthStencilView(DX11_Depth_Stencil_Buffer, &depthStencilViewDesc, &DX11_Depth_Stencil_View));

	/// ����Ÿ�ٺ�, ����/���ĽǺ並 ���������ο� ���ε��Ѵ�.
	DX11_Device_Context->OMSetRenderTargets(1, &DX11_Render_Target_View, DX11_Depth_Stencil_View);

	// Setup the raster description which will determine how and what polygons will be drawn.
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	// Create the rasterizer state from the description we just filled out.
	HR(DX11_Device->CreateRasterizerState(&rasterDesc, &DX11_Raster_State));

	// Now set the rasterizer state.
	DX11_Device_Context->RSSetState(DX11_Raster_State);

	// Setup the viewport for rendering.
	viewport.Width = (float)g_Screen_Width;
	viewport.Height = (float)g_Screen_Height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	// Create the viewport.
	DX11_Device_Context->RSSetViewports(1, &viewport);

	// Mesh
	//BuildGeometryBuffers();

	//BuildFX();
	//BuildFX_Create();
	//BuildVertexLayout();

	// Render State
	CreateRenderStates();

	// ����� ������ ��´�.
	GetAdapterInfo();

	// D2D �� ����ϱ� ����.
	m_D2DSupport = new D2DSupport(g_hWnd, DX11_Swap_Chain);
	m_AxisGrid = new AxisGrid(DX11_Device, DX11_Device_Context, DX11_Raster_State);
}

void DH3DEngine::SetDebug(bool _Is_Debug, int _Grid_Num)
{
	Is_Debug = _Is_Debug;

	// �ش� ����� ��忡���� Grid ��������. default = 50
	_Grid_Num = 150;
	m_AxisGrid->Initialize(_Grid_Num);
}

void DH3DEngine::SetSkyBox(ATL::CString _Sky_Box_Path)
{
	Sky_Box_Path = _Sky_Box_Path;
}

void DH3DEngine::BeginDraw()
{
	float color[4];

	// Setup the color to clear the buffer to.
	color[0] = 0.17f;
	color[1] = 0.17f;
	color[2] = 0.17f;
	color[3] = 1.0f;

	// Clear the back buffer.
	DX11_Device_Context->ClearRenderTargetView(DX11_Render_Target_View, color);

	// Clear the depth buffer.
	DX11_Device_Context->ClearDepthStencilView(DX11_Depth_Stencil_View, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

}

void DH3DEngine::Update(float DTime)
{
	m_Delta_Time = DTime;

	// view TM�� �����.
	//m_DHCamera->UpdateViewMatrix();
}


void DH3DEngine::RenderDraw(OneFrameData* _OFD, SharedRenderData* _SRD)
{
	/// �׸� �޽ð� �������� ������ ����..
	if (_SRD->Render_Mesh_List == nullptr)
	{
		return;
	}

	if (!_SRD->Texture_SetUp)
	{
		SetTextureSRV(_SRD);
		_SRD->Texture_SetUp = true;
	}

	if (Is_Debug)
	{
		// �����ֱ�
		static float _addedTime = 0;
		static float _FPS = 0;
		static float _deltaTimeMS = 0;

		// �����ֱ�� 0.2��
		if (0.2f < _addedTime)
		{
			_FPS = (1.0f / m_Delta_Time);
			_deltaTimeMS = m_Delta_Time * 1000.0f;

			_addedTime = 0;
		}

		_addedTime += (m_Delta_Time);
		// FPS, deltaTime�� �׸���.
		m_D2DSupport->Push_DrawText({ 10, 8 }, 500, 1, 0, 0, 1, 20, (TCHAR*)L"FPS : %.2f", _FPS);
		m_D2DSupport->Push_DrawText({ 10, 29 }, 500, 1, 0, 0, 1, 20, (TCHAR*)L"DTime : %.4f ms", _deltaTimeMS);
		m_D2DSupport->Push_DrawText({ 510, 29 }, 500, 1, 0, 0, 1, 20, (TCHAR*)L"ī�޶� ��ġ : %f, %f, %f", _OFD->World_Eye_Position.x, _OFD->World_Eye_Position.y, _OFD->World_Eye_Position.z);
		m_D2DSupport->Push_DrawText({ 510, 50 }, 500, 1, 0, 0, 1, 20, (TCHAR*)L"ĳ���� ��ġ : %f, %f, %f", _OFD->Main_Position.x, _OFD->Main_Position.y, _OFD->Main_Position.z);

		// ���ķ���, ����� ���� ���¸� �׸���.
		this->Draw_Status();

		/// AxisGrid�� �׸����� ���ٸ� �׷���! ���� Begin �� End ���̿� �ѹ��̶� �׷����� �ٽô� �ȱ׸�.
		if (!Is_Draw_AxisGrid)
		{
			m_AxisGrid->Render(&_OFD->View_Matrix, &_OFD->Projection_Matrix);

			Is_Draw_AxisGrid = true;
		}
	}


	/// �׸� �޽ð� �����ϸ� �޽ø���Ʈ�� ��ȸ�ϸ� �׸���.
	for (auto& _Render_Mesh : *_SRD->Render_Mesh_List)
	{
		/// ���� �ε���, ���ؽ� ���۰� �����Ǿ����� �ʴٸ�
		if ((_Render_Mesh.Index_Buffer == nullptr) && (_Render_Mesh.Vertex_Buffer == nullptr))
		{
			CreateVertexBuffer(&_Render_Mesh);
			CreateIndexBuffer(&_Render_Mesh);
		}

		///----------------------------------------------------------------------------------------------------
		/// ������Ʈ���� �׸���. (Draw Primitive)

		mVB = reinterpret_cast<ID3D11Buffer*>(_Render_Mesh.Vertex_Buffer);
		mIB = reinterpret_cast<ID3D11Buffer*>(_Render_Mesh.Index_Buffer);

		// �Է� ��ġ ��ü ����
		DX11_Device_Context->IASetInputLayout(InputLayouts::PosNormalTexBiNormalTangent);
		DX11_Device_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// ���� ������Ʈ
		DX11_Device_Context->RSSetState(DX11_Raster_State);

		// ���ؽ����ۿ� �ε������� ����
		Vertex_Buffer_Stride = sizeof(DHParser::Vertex);
		Vertex_Buffer_Offset = 0;

		/// WVP TM���� ����
		Mul_WVP = _Render_Mesh.World_TM * _SRD->SRT_Matrix  * _OFD->View_Matrix * _OFD->Projection_Matrix;

		// ������ �����
		World_Inverse = _Render_Mesh.World_TM.Invert();

		// Set per frame constants.
		DirectionalLight _temp_Dir;
		DirectX::SimpleMath::Vector4 _Ambient = DirectX::SimpleMath::Vector4(0.2f, 0.2f, 0.2f, 1.0f);
		DirectX::SimpleMath::Vector4 _Diffuse = DirectX::SimpleMath::Vector4(0.5f, 0.5f, 0.5f, 1.0f);
		DirectX::SimpleMath::Vector4 _Specular = DirectX::SimpleMath::Vector4(0.5f, 0.5f, 0.5f, 1.0f);
		DirectX::SimpleMath::Vector3 _Direction = DirectX::SimpleMath::Vector3(-0.57735f, -0.57735f, 0.57735f);
		_temp_Dir.Ambient = _Ambient;
		_temp_Dir.Diffuse = _Diffuse;
		_temp_Dir.Specular = _Specular;
		_temp_Dir.Direction = _Direction;
		
		_OFD->DirLight_List.push_back(_temp_Dir);

		Effects::BasicFX->SetDirLights(_OFD->DirLight_List);
		Effects::BasicFX->SetEyePosW(_OFD->World_Eye_Position);

		ID3DX11EffectTechnique* mTech = nullptr;

		if (_Render_Mesh.Texture_Key != -1 && _SRD->Diffuse_Texture[_Render_Mesh.Texture_Key] != nullptr)
		{
			/// �ؽ��� ���
			mTech = Effects::BasicFX->Light1Tech;
		}
		else
		{
			/// �ؽ��� �̻��
			mTech = Effects::BasicFX->Light2Tech;
		}

		// ��ũ����...
		D3DX11_TECHNIQUE_DESC techDesc;
		mTech->GetDesc(&techDesc);

		// �����н���...
		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			DX11_Device_Context->IASetVertexBuffers(0, 1, &mVB, &Vertex_Buffer_Stride, &Vertex_Buffer_Offset);
			DX11_Device_Context->IASetIndexBuffer(mIB, DXGI_FORMAT_R32_UINT, 0);

			World_Inverse_Transpose = MathHelper::InverseTranspose(_Render_Mesh.World_TM);
			Effects::BasicFX->SetWorld(_Render_Mesh.World_TM);
			Effects::BasicFX->SetWorldInvTranspose(World_Inverse_Transpose);
			Effects::BasicFX->SetWorldViewProj(Mul_WVP);
			Effects::BasicFX->SetMaterial(_Render_Mesh.Mesh_Material);

			if (mTech == Effects::BasicFX->Light1Tech)
			{
				Effects::BasicFX->SetTexTransform(DirectX::SimpleMath::Matrix::Identity);
				Effects::BasicFX->SetDiffuseMap(reinterpret_cast<ID3D11ShaderResourceView*>(_SRD->Diffuse_Texture[_Render_Mesh.Texture_Key]->Texture_SRV));
			}

			mTech->GetPassByIndex(p)->Apply(0, DX11_Device_Context);
			DX11_Device_Context->DrawIndexed(_Render_Mesh.Tcount * 3, 0, 0);
		}

	}

	DrawSkyBox(_OFD);

	_OFD->DirLight_List.clear();

	// Restore default.
	DX11_Device_Context->RSSetState(0);
}

void DH3DEngine::UIDraw(Shared2DRenderData* _S2DRD)
{
	// �ؽ�Ʈ �����Ͱ� �ִٸ� �׷���
	if (_S2DRD->Is_Text)
	{
		m_D2DSupport->Push_DrawText(POINT{ (int)_S2DRD->Play_Text_Att.Position.x, (int)_S2DRD->Play_Text_Att.Position.y },
			1200, _S2DRD->Play_Text_Att.Color.x, _S2DRD->Play_Text_Att.Color.y, _S2DRD->Play_Text_Att.Color.z,
			_S2DRD->Play_Text_Att.Alpha, _S2DRD->Play_Text_Att.Size, _S2DRD->Play_Text_String);
	}

	if (!_S2DRD->Is_Img_Load)
	{
		// �̹��� �ε�.
		for (auto Img_Data : _S2DRD->Img_Path_List)
		{
			m_D2DSupport->LoadBitMap(Img_Data.first, Img_Data.second);
		}

		_S2DRD->Is_Img_Load = true;
	}

	// �׸� �̹��� Queue�� �߰�.
	for (auto Img_Data : _S2DRD->Img_List)
	{
		DHRENDER::ImageTRSA* TRSA_Data = Img_Data.second;

		m_D2DSupport->Push_DrawImage(Img_Data.first,
			POINTF{ TRSA_Data->Position.x, TRSA_Data->Position.y }, POINTF{ TRSA_Data->Scale.x, TRSA_Data->Scale.y }, TRSA_Data->Rotate_Angle, TRSA_Data->Alpha,
			POINTF{ _S2DRD->UI_TRSA.Position.x, _S2DRD->UI_TRSA.Position.y }, POINTF{ _S2DRD->UI_TRSA.Scale.x, _S2DRD->UI_TRSA.Scale.y }, _S2DRD->UI_TRSA.Rotate_Angle, _S2DRD->UI_TRSA.Alpha);
	}

}

void DH3DEngine::TextDraw(POINT _Pos, float _Width, float r, float g, float b, float a, float _Size, const wchar_t* _Input_String)
{
	m_D2DSupport->Push_DrawText(_Pos, _Width, r, g, b, a, _Size, _Input_String);
}

void DH3DEngine::LoadingDraw(ATL::CString _Loading_Path)
{
	m_D2DSupport->LoadLoadingImage(_Loading_Path);

	m_D2DSupport->DrawLoadingImage();
}

void DH3DEngine::EndDraw()
{
	// �̹��� �׸���
	m_D2DSupport->Draw_AllImage();
	// �ؽ�Ʈ �׸���.
	m_D2DSupport->Draw_AllText();
	// ���� �����ӿ� �ٽ� Axis_Grid�� �׸� �� �ֵ���..
	Is_Draw_AxisGrid = false;
	// Present as fast as possible.
	DX11_Swap_Chain->Present(0, 0);
}

void DH3DEngine::Finalize()
{
	/// �Ϸ��� �۾� ��..
		// Before shutting down set to windowed mode or when you release the swap chain it will throw an exception.
	if (DX11_Swap_Chain)
	{
		DX11_Swap_Chain->SetFullscreenState(false, NULL);
	}

	if (DX11_Raster_State)
	{
		DX11_Raster_State->Release();
		DX11_Raster_State = 0;
	}

	if (DX11_Depth_Stencil_View)
	{
		DX11_Depth_Stencil_View->Release();
		DX11_Depth_Stencil_View = 0;
	}

	if (DX11_Depth_Stencil_State)
	{
		DX11_Depth_Stencil_State->Release();
		DX11_Depth_Stencil_State = 0;
	}

	if (DX11_Depth_Stencil_Buffer)
	{
		DX11_Depth_Stencil_Buffer->Release();
		DX11_Depth_Stencil_Buffer = 0;
	}

	if (DX11_Render_Target_View)
	{
		DX11_Render_Target_View->Release();
		DX11_Render_Target_View = 0;
	}

	if (DX11_Device_Context)
	{
		DX11_Device_Context->Release();
		DX11_Device_Context = 0;
	}

	if (DX11_Device)
	{
		DX11_Device->Release();
		DX11_Device = 0;
	}

	if (DX11_Swap_Chain)
	{
		DX11_Swap_Chain->Release();
		DX11_Swap_Chain = 0;
	}
}

void DH3DEngine::DrawSkyBox(OneFrameData* _OFD)
{
	// ��ī�̹ڽ��� �����Ǿ� ���� �ʴٸ�.. return
	if (Sky_Box_Path == "" && m_SkyBox == nullptr)
	{
		return;
	}

	// ��ī�̹ڽ��� �̹� �ε�Ǿ� �ִ°�� �׷���.
	if (m_SkyBox != nullptr)
	{
		m_SkyBox->Draw(DX11_Device_Context, _OFD);
	}
	// ��ī�̹ڽ��� �ε�Ǿ� ���� ������ ���� ����� �׷���.
	else
	{
		m_SkyBox = new SkyBox(DX11_Device, Sky_Box_Path, 5000.0f);
		m_SkyBox->Draw(DX11_Device_Context, _OFD);
	}
}

float DH3DEngine::GetAspectRatio() const
{
	return static_cast<float>(g_Screen_Width) / g_Screen_Height;
}

void DH3DEngine::SetTextureSRV(SharedRenderData* _SRD)
{

	if (!_SRD->Ambient_Texture.empty())
	{
		for (auto k : _SRD->Ambient_Texture)
		{
			// �ؽ��� ������ ���� �ӽ� ��ü
			ID3D11Resource* Texture_Resource = nullptr;
			// �ؽ��� SRV
			ID3D11ShaderResourceView* DX11_SRV = nullptr;
			// �ؽ��� ���� ����.
			CreateWICTextureFromFile(DX11_Device, k.second->Texture_Path, &Texture_Resource, &DX11_SRV);
			ReleaseCOM(Texture_Resource);

			k.second->Texture_SRV = DX11_SRV;
		}
	}

	if (!_SRD->Emissive_Texture.empty())
	{
		for (auto k : _SRD->Emissive_Texture)
		{
			// �ؽ��� ������ ���� �ӽ� ��ü
			ID3D11Resource* Texture_Resource = nullptr;
			// �ؽ��� SRV
			ID3D11ShaderResourceView* DX11_SRV = nullptr;
			// �ؽ��� ���� ����.
			CreateWICTextureFromFile(DX11_Device, k.second->Texture_Path, &Texture_Resource, &DX11_SRV);
			ReleaseCOM(Texture_Resource);

			k.second->Texture_SRV = DX11_SRV;
		}
	}

	if (!_SRD->Diffuse_Texture.empty())
	{
		for (auto k : _SRD->Diffuse_Texture)
		{
			// �ؽ��� ������ ���� �ӽ� ��ü
			ID3D11Resource* Texture_Resource = nullptr;
			// �ؽ��� SRV
			ID3D11ShaderResourceView* DX11_SRV = nullptr;
			// �ؽ��� ���� ����.
			CreateWICTextureFromFile(DX11_Device, k.second->Texture_Path, &Texture_Resource, &DX11_SRV);
			ReleaseCOM(Texture_Resource);

			k.second->Texture_SRV = DX11_SRV;
		}
	}

	if (!_SRD->Specular_Texture.empty())
	{
		for (auto k : _SRD->Specular_Texture)
		{
			// �ؽ��� ������ ���� �ӽ� ��ü
			ID3D11Resource* Texture_Resource = nullptr;
			// �ؽ��� SRV
			ID3D11ShaderResourceView* DX11_SRV = nullptr;
			// �ؽ��� ���� ����.
			CreateWICTextureFromFile(DX11_Device, k.second->Texture_Path, &Texture_Resource, &DX11_SRV);
			ReleaseCOM(Texture_Resource);

			k.second->Texture_SRV = DX11_SRV;
		}
	}

	if (!_SRD->NormalMap_Texture.empty())
	{
		for (auto k : _SRD->NormalMap_Texture)
		{
			// �ؽ��� ������ ���� �ӽ� ��ü
			ID3D11Resource* Texture_Resource = nullptr;
			// �ؽ��� SRV
			ID3D11ShaderResourceView* DX11_SRV = nullptr;
			// �ؽ��� ���� ����.
			CreateWICTextureFromFile(DX11_Device, k.second->Texture_Path, &Texture_Resource, &DX11_SRV);
			ReleaseCOM(Texture_Resource);

			k.second->Texture_SRV = DX11_SRV;
		}
	}
}

void DH3DEngine::On_Resize(float Change_Width, float Change_Height)
{

	/// �ٲ� ȭ���� ����� ������ �صڿ�
	g_Screen_Width = Change_Width;
	g_Screen_Height = Change_Height;

	/// ȭ���� ��Ÿ���� ������ view�� �����ϰ� ��������� ���� �����Ѵ�.
	assert(DX11_Device_Context);
	assert(DX11_Device);
	assert(DX11_Swap_Chain);

	/// �籸�� �ϴµ� �ʿ��� ������ => ����Ÿ���� ��, ���Ľ� ��,����
	ReleaseCOM(DX11_Render_Target_View);
	ReleaseCOM(DX11_Depth_Stencil_View);
	ReleaseCOM(DX11_Depth_Stencil_Buffer);

	HR(DX11_Swap_Chain->ResizeBuffers(1, g_Screen_Width, g_Screen_Height, DXGI_FORMAT_R8G8B8A8_UNORM, 0));
	ID3D11Texture2D* backBuffer;
	HR(DX11_Swap_Chain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));
	HR(DX11_Device->CreateRenderTargetView(backBuffer, 0, &DX11_Render_Target_View));
	ReleaseCOM(backBuffer);

	// Create the depth/stencil buffer and view.

	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width = g_Screen_Width;
	depthStencilDesc.Height = g_Screen_Height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	/// 4X MSAA ��带 ������� ����.
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;

	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	/// ���Ľ� Desc�� ������� �Ͽ� ���Ľ� ���ۿ� �並 ������Ѵ�.
	HR(DX11_Device->CreateTexture2D(&depthStencilDesc, 0, &DX11_Depth_Stencil_Buffer));
	HR(DX11_Device->CreateDepthStencilView(DX11_Depth_Stencil_Buffer, 0, &DX11_Depth_Stencil_View));


	/// ����Ÿ�ٺ�, ����/���ĽǺ並 ���������ο� ���ε��Ѵ�.
	DX11_Device_Context->OMSetRenderTargets(1, &DX11_Render_Target_View, DX11_Depth_Stencil_View);


	// Set the viewport transform.
	/// ����Ʈ ��ȯ�� �����Ѵ�.
	DX11_View_Port.TopLeftX = 0;
	DX11_View_Port.TopLeftY = 0;
	DX11_View_Port.Width = static_cast<float>(g_Screen_Width);
	DX11_View_Port.Height = static_cast<float>(g_Screen_Height);
	DX11_View_Port.MinDepth = 0.0f;
	DX11_View_Port.MaxDepth = 1.0f;

	DX11_Device_Context->RSSetViewports(1, &DX11_View_Port);

	// The window resized, so update the aspect ratio and recompute the projection matrix.
	
	/// â�� ũ�Ⱑ �������Ƿ�, ��Ⱦ�� ������Ʈ�ϰ� ���� ����� �����Ѵ�.
	//m_DHCamera->SetLens(0.25f * MathHelper::Pi, GetAspectRatio(), 1.0f, 1000.0f);
}

void DH3DEngine::Draw_Status()
{
	DirectX::SimpleMath::Vector4 _white(1.f, 1.f, 1.f, 1.f);	// white

	// ���ķ���
	int _yPos = 50;
	int _Text_Offset = 21;
	//m_DXTKFont->DrawTextColor(0, _yPos, _white, (TCHAR*)L"Feature Level : %x", featureLevel);

	//// ����� ����
	m_D2DSupport->Push_DrawText({ 10, _yPos }, 500, 1, 0, 0, 1, 20, (TCHAR*)L"Description: %s", m_Adapter_Desc1.Description);
	m_D2DSupport->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 1, 0, 1, 20, (TCHAR*)L"VendorID: %u", m_Adapter_Desc1.VendorId);
	m_D2DSupport->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 1, 0, 1, 20, (TCHAR*)L"DeviceID: %u", m_Adapter_Desc1.DeviceId);
	m_D2DSupport->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 1, 0, 1, 20, (TCHAR*)L"SubSysID: %u", m_Adapter_Desc1.SubSysId);
	m_D2DSupport->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 1, 0, 1, 20, (TCHAR*)L"Revision: %u", m_Adapter_Desc1.Revision);
	m_D2DSupport->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 0, 1, 1, 20, (TCHAR*)L"VideoMemory: %lu MB", m_Adapter_Desc1.DedicatedVideoMemory / 1024 / 1024);
	m_D2DSupport->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 0, 1, 1, 20, (TCHAR*)L"SystemMemory: %lu MB", m_Adapter_Desc1.DedicatedSystemMemory / 1024 / 1024);
	m_D2DSupport->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 0, 1, 1, 20, (TCHAR*)L"SharedSysMemory: %lu MB", m_Adapter_Desc1.SharedSystemMemory / 1024 / 1024);
	m_D2DSupport->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 1, 1, 0, 1, 20, (TCHAR*)L"AdpaterLuid: %u.%d", m_Adapter_Desc1.AdapterLuid.HighPart, m_Adapter_Desc1.AdapterLuid.LowPart);

	//// ī�޶� ����
	//m_DXTKFont->DrawTextColor(0, _yPos += 28, _white, (TCHAR*)L"Camera Pos : %.2f / %.2f / %.2f", m_DHCamera->GetPosition().x, m_DHCamera->GetPosition().y, m_DHCamera->GetPosition().z);
}

void DH3DEngine::CreateIndexBuffer(DHParser::Mesh* _Mesh)
{
	ID3D11Buffer* mIB;

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * _Mesh->Tcount*3;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &_Mesh->Optimize_Index[0];

	HR(DX11_Device->CreateBuffer(&ibd, &iinitData, &mIB));

	_Mesh->Index_Buffer = mIB;
}

void DH3DEngine::CreateVertexBuffer(DHParser::Mesh* _Mesh)
{
	ID3D11Buffer* mVB;

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(DHParser::Vertex) * _Mesh->Vcount;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = &_Mesh->Optimize_Vertex[0];

	HR(DX11_Device->CreateBuffer(&vbd, &vinitData, &mVB));

	_Mesh->Vertex_Buffer = mVB;
}

HRESULT DH3DEngine::GetAdapterInfo()
{
	// DXGI�������� �ٸ�
	IDXGIAdapter1* pAdapter;
	IDXGIFactory1* pFactory = NULL;

	HRESULT hr = S_OK;

	// DXGIFactory ��ü ����(DXGI.lib �ʿ�)
	if (FAILED(CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&pFactory)))
	{
		return E_FAIL;
	}

	hr = pFactory->EnumAdapters1(0, &pAdapter);

	if (hr != DXGI_ERROR_NOT_FOUND)
	{
		pAdapter->GetDesc1(&m_Adapter_Desc1);
	}

	SAFE_RELEASE(pAdapter);
	SAFE_RELEASE(pFactory);

	return S_OK;
}

void DH3DEngine::CreateRenderStates()
{
	// Render State �� Rasterizer State
	D3D11_RASTERIZER_DESC solidDesc;
	ZeroMemory(&solidDesc, sizeof(D3D11_RASTERIZER_DESC));
	solidDesc.FillMode = D3D11_FILL_SOLID;
	solidDesc.CullMode = D3D11_CULL_BACK;
	solidDesc.FrontCounterClockwise = false;
	solidDesc.DepthClipEnable = true;

	HR(DX11_Device->CreateRasterizerState(&solidDesc, &mSolidRS));

	D3D11_RASTERIZER_DESC wireframeDesc;
	ZeroMemory(&wireframeDesc, sizeof(D3D11_RASTERIZER_DESC));
	wireframeDesc.FillMode = D3D11_FILL_WIREFRAME;
	wireframeDesc.CullMode = D3D11_CULL_BACK;
	wireframeDesc.FrontCounterClockwise = false;
	wireframeDesc.DepthClipEnable = true;

	HR(DX11_Device->CreateRasterizerState(&wireframeDesc, &mWireframeRS));
}

/// �̹� ����Ǿ��ִ� FX������ �����ؼ� �����ϴ� ����. ( ���� ��� ���ϴ���.. )
void DH3DEngine::BuildFX()
{
	std::ifstream fin("../fx/color.fxo", std::ios::binary);

	fin.seekg(0, std::ios_base::end);
	int size = (int)fin.tellg();
	fin.seekg(0, std::ios_base::beg);
	std::vector<char> compiledShader(size);

	fin.read(&compiledShader[0], size);
	fin.close();

	HR(D3DX11CreateEffectFromMemory(&compiledShader[0], size,
		0, DX11_Device, &mFX));

	// ����Ʈ ��ü�� ���ؼ� ��ũ���� ���´�.
	mTech = mFX->GetTechniqueByName("ColorTech");

	// ����Ʈ ��ü�� ���ؼ� ��������� ������ �����´�.
	mfxWorldViewProj = mFX->GetVariableByName("gWorldViewProj")->AsMatrix();
}

/// �ǽð����� FX������ �����ؼ� �����ϴ� ����.
void DH3DEngine::BuildFX_Create()
{
	DWORD shaderFlags = 0;
#if defined( DEBUG ) || defined( _DEBUG )
	shaderFlags |= D3D10_SHADER_DEBUG;
	shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif

	ID3D10Blob* compiledShader = 0;
	ID3D10Blob* compilationMsgs = 0;
	HRESULT hr = D3DCompileFromFile(L"../FX/color.fx", 0, 0, 0, "fx_5_0", shaderFlags, 0, &compiledShader, &compilationMsgs);

	if (compilationMsgs != 0)
	{
		///MessageBoxA(0, (char*)compilationMsgs->GetBufferPointer(), 0, 0);
		ReleaseCOM(compilationMsgs);
	}

	HR(D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(),
		0, DX11_Device, &mFX));

	// Done with compiled shader.
	ReleaseCOM(compiledShader);

	mTech = mFX->GetTechniqueByName("ColorTech");
	mfxWorldViewProj = mFX->GetVariableByName("gWorldViewProj")->AsMatrix();
}