#pragma once

/// DX11 ��ŷ
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")

#ifdef _DEBUG
#pragma comment( lib, "DirectXTKd.lib" )
#pragma comment( lib, "Effects11d.lib" )
#else
#pragma comment( lib, "DirectXTK.lib" )
#pragma comment( lib, "Effects11.lib" )
#endif

#include <fstream>
#include <vector>

/// DX11 ��Ŭ���.
#include <d3d11.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <DirectXPackedVector.h>
#include "d3dx11effect.h"

/// Helper
#include "MathHelper.h"
#include "LightHelper.h"
#include "SimpleMath.h"
#include "DirectXHelpers.h"
#include "DirectXColors.h"
#include "WICTextureLoader.h"

using namespace DirectX;
using namespace DirectX::PackedVector;
