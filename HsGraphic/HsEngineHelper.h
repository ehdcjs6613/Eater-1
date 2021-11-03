#pragma once

//텍스쳐 불러올떄
////////////////////////////////////////////////
#ifdef _DEBUG
#pragma comment(lib, "DirectXTKd.lib")
#else
#pragma comment(lib, "DirectXTK.lib")
#endif
#include "DDSTextureLoader.h"

////////////////////////////////////////////////


//D3D 기본 라이브러리 
////////////////////////////////////////////////
#pragma comment(lib, "d3d11")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "d3dcompiler") //쉐이더
////////////////////////////////////////////////


#include <d3dcompiler.h>
#include <winerror.h>
#include <assert.h>
#include <d3d11.h>
#include <string>
//#include "atlstr.h"