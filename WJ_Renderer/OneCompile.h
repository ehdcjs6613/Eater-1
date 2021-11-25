#pragma once


//  ���� ���̺귯���� �����ؾ� �� �ʿ伺�� �����.
// �� ó���� �� ���� ������ DX11��å�� �������� ���� �� �� ����.
#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#else
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

///----------------------------------------
#define _XM_NO_INTRINSICS_	

/// DX11 ��ŷ
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



/// DX11 ��Ŭ���.
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3dcommon.h>
#include <dxgi.h>

#include <DirectXMath.h>
#include <DirectXColors.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
//����Ʈ������ ��Ŭ����
#include <windef.h>
#include <wrl.h>
#include <wrl/client.h>
#include <memory>
#include <winerror.h> //


//c++ iostream �� �ڷᱸ�� ���
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>


#include <Windows.h>
#include <vector>
#include <map>
#include <atlstr.h>
#include "SimpleMath.h"

