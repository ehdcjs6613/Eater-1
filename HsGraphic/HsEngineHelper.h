#pragma once

//텍스쳐 불러올떄
////////////////////////////////////////////////
#ifdef _DEBUG
#pragma comment(lib, "DirectXTKd.lib")
#else
#pragma comment(lib, "DirectXTex.lib")
#endif
#include "DDSTextureLoader11.h"
////////////////////////////////////////////////


//D3D 기본 라이브러리 
////////////////////////////////////////////////
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib") //쉐이더
////////////////////////////////////////////////


#include <winerror.h>
#include <assert.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <string>
#include "atlstr.h"