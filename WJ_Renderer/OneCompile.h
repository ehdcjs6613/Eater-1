#pragma once


//  이전 라이브러리를 제거해야 할 필요성이 생겼다.
// 이 처리를 해 주지 않으면 DX11용책의 예제들을 빌드 할 수 없다.
#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#else
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

///----------------------------------------
#define _XM_NO_INTRINSICS_	

/// DX11 링킹
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")

#ifdef _DEBUG
#pragma comment( lib, "DirectXTK_x64d.lib" )
#pragma comment( lib, "Effects11d.lib" )
#else
#pragma comment( lib, "DirectXTK_x64r.lib" )
#pragma comment( lib, "Effects11.lib" )
#endif
//



/// DX11 인클루드.
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3dcommon.h>
#include <dxgi.h>

#include <DirectXMath.h>
#include <DirectXColors.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
//스마트포인터 인클르드
#include <windef.h>
#include <wrl.h>
#include <wrl/client.h>
#include <memory>
#include <winerror.h> //


//c++ iostream 및 자료구조 헤더
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>


#include <Windows.h>
#include <vector>
#include <map>
#include <atlstr.h>
#include "SimpleMath.h"

