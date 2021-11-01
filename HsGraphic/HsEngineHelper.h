#pragma once
#include <winerror.h>
#include <assert.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <string>
#include "atlstr.h"

#include "DDSTextureLoader11.h"
#ifdef _DEBUG
//#pragma comment(lib, "DirectXTexd.lib")
#pragma comment(lib, "DirectXTKd.lib")
#else
#pragma comment(lib, "DirectXTex.lib")
#endif


#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")