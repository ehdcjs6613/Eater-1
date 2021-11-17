#pragma once
//#ifdef IX3Engine
//#define X3Engine_DLL __declspec(dllexport)
//#else 
//#define X3Engine_DLL __declspec(dllimport)
////디버그 모드에서 라이브러리 사용시
//#ifdef _DEBUG
//#pragma comment(lib,"WJ_Renderer.lib")
//#else
//#pragma comment(lib,"WJ_Renderer.lib")
//#endif 
//
//#endif // X3Engine_DLL __declspec(dllimport)
//
//
//#ifdef IX3Engine
//#define X3Engine_DLL __declspec(dllexport)
//#else 
//#define X3Engine_DLL __declspec(dllimport)
////디버그 모드에서 라이브러리 사용시
//#ifdef _DEBUG
//#pragma comment(lib,"WJ_Renderer.lib")
//#else
//#pragma comment(lib,"WJ_Renderer.lib")
//#endif 
//#endif // X3Engine_DLL __declspec(dllimport)


#ifdef IX3Engine_INTERFACE
	#define X3Engine_DLL __declspec(dllexport)
#else
	#define X3Engine_DLL __declspec(dllimport)

	#ifdef _DEBUG
		#pragma comment(lib,"WJ_Renderer_x64d")
	#else
		#pragma comment(lib,"WJ_Renderer_x64r")
	#endif


#endif

