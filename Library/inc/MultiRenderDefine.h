#pragma once
#ifdef MULTIRENDERENGINE_EXPORTS
#define MULTIENGINE_DLL __declspec(dllexport)
#else
#define MULTIENGINE_DLL __declspec(dllimport)

#ifdef _DEBUG
#pragma comment(lib,"MultiRenderEngine_x64d")
#else
#pragma comment(lib,"MultiRenderEngine_x64r")
#endif

#endif



#ifdef _WIN64
#ifdef _DEBUG
#pragma comment( lib, "../lib/DirectXTK_x64d.lib" )
#else
#pragma comment( lib, "../lib/DirectXTK_x64r.lib" )
#endif
#endif




#include <windows.h>
#include <map>
#include <queue>
#include <string>