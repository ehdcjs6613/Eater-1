#pragma once

//�ؽ��� �ҷ��Ë�
////////////////////////////////////////////////
#ifdef _DEBUG
#pragma comment(lib, "DirectXTKd.lib")
#else
#pragma comment(lib, "DirectXTex.lib")
#endif
#include "DDSTextureLoader11.h"
////////////////////////////////////////////////


//D3D �⺻ ���̺귯�� 
////////////////////////////////////////////////
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib") //���̴�
////////////////////////////////////////////////


#include <winerror.h>
#include <assert.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <string>
#include "atlstr.h"