#pragma once

/// DX11 SwapChain �� ���̺귯��.
#pragma comment(lib,"dxgi.lib")
#include <dxgi.h>

/// D2D�� ���̺귯��.
// WIC ����� ����.
#include <wincodec.h>
#pragma comment(lib, "WindowsCodecs.lib")
#pragma comment(lib, "d2d1")
#include <d2d1.h>
#pragma comment(lib, "Dwrite")
#include <dwrite.h>
#include <dwrite_3.h>

/// �⺻ ���̺귯��
#include <stdio.h>
#include <limits>
#include <atlstr.h>
#include <map>

/// Ŀ���� ������ƮǮ ���̺귯��
#include "Non_ThreadObjectPool.h"