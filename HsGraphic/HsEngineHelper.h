#pragma once

//�ؽ��� �ҷ��Ë�
////////////////////////////////////////////////
#ifdef _DEBUG
#pragma comment(lib, "DirectXTKd.lib")
#else
#pragma comment(lib, "DirectXTK.lib")
#endif
#include "DDSTextureLoader.h"
////////////////////////////////////////////////


//D3D �⺻ ���̺귯�� 
////////////////////////////////////////////////
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib") //���̴�
////////////////////////////////////////////////


#include <d3dcompiler.h>
#include <winerror.h>
#include <assert.h>
#include <d3d11.h>
#include <string>
#include "atlstr.h"