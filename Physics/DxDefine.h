#pragma once

/// DX11 ¸µÅ·
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

#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3dcommon.h>
#include <dxgi.h>

#include <DirectXMath.h>
#include <DirectXColors.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>

#if defined(DEBUG) | defined(_DEBUG)
#ifndef HR
#define HR(x)\
	{\
		HRESULT hr = (x);\
		if(FAILED(hr))\
		{\
			LPWSTR output;                                    	\
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |		\
				FORMAT_MESSAGE_IGNORE_INSERTS 	 |		\
				FORMAT_MESSAGE_ALLOCATE_BUFFER,			\
				NULL,						\
				hr,						\
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),	\
				(LPTSTR) &output,				\
				0,						\
				NULL);					        \
			MessageBox(NULL, output, L"Error", MB_OK);\
		}								\
	}
#endif
#else
#ifndef HR
#define HR(x) (x)
#endif
#endif 