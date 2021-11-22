#pragma once


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




/// DX11 ��Ŭ���.
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3dcommon.h>
#include <dxgi.h>

#include <DirectXMath.h>
#include <DirectXColors.h>
#include <DirectXPackedVector.h>

//����Ʈ������ ��Ŭ����
#include <wrl.h>
#include <wrl/client.h>
#include <memory>

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

namespace VertexStruct
{
	struct PosNormal
	{
		DirectX::SimpleMath::Vector3 Pos;
		DirectX::SimpleMath::Vector3 Normal;
	};
}

