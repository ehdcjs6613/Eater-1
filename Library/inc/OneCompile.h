#pragma once


/// DX11 ��ŷ
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")

#ifdef _DEBUG
//#pragma comment( lib, "DirectXTKd.lib" )
//#pragma comment( lib, "Effects11d.lib" )
#else
#pragma comment( lib, "DirectXTK.lib" )
#pragma comment( lib, "Effects11.lib" )
#endif



/// DX11 ��Ŭ���.
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3dcommon.h>

#include <dxgi.h>

#include <DirectXMath.h>
#include <DirectXColors.h>
#include <DirectXPackedVector.h>

//����Ʈ������ ��Ŭ����
#include <wrl/client.h>
#include <memory>

//c++ iostream �� �ڷᱸ�� ���
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>


