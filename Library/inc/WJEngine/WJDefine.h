#pragma once



#ifdef IX3Engine
#define X3Engine_DLL __declspec(dllexport)

#else 
//디버그 모드에서 라이브러리 사용시
#define X3Engine_DLL __declspec(dllimport)
#ifdef _DEBUG
#pragma comment(lib,"WJ_Renderer.lib")
#else
#pragma comment(lib,"WJ_Renderer.lib")
#endif 
#endif // X3Engine_DLL __declspec(dllimport)

