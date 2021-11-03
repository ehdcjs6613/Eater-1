#pragma once
#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)


	#ifdef _DEBUG
	#define EATER_ENGINEDLL __declspec(dllexport)
	#pragma comment(lib,"EaterEngine_x64d")
	#else
	#define EATER_ENGINEDLL __declspec(dllimport)
	#pragma comment(lib,"EaterEngine_x64dr")
	#endif

#endif
