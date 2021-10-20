#pragma once

/// DX11 SwapChain 용 라이브러리.
#pragma comment(lib,"dxgi.lib")
#include <dxgi.h>

/// D2D용 라이브러리.
// WIC 사용을 위함.
#include <wincodec.h>
#pragma comment(lib, "WindowsCodecs.lib")
#pragma comment(lib, "d2d1")
#include <d2d1.h>
#pragma comment(lib, "Dwrite")
#include <dwrite.h>
#include <dwrite_3.h>

/// 기본 라이브러리
#include <stdio.h>
#include <limits>
#include <atlstr.h>
#include <map>

/// 커스텀 오브젝트풀 라이브러리
#include "Non_ThreadObjectPool.h"