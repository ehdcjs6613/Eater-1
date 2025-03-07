#pragma once


#if _DEBUG
	#ifdef PhysicsExportDLL
		#define PhysicsExport __declspec(dllexport)
	#else
		#define PhysicsExport __declspec(dllimport)
	#endif
#else //_Release
	#ifdef PhysicsExportDLL
		#define PhysicsExport __declspec(dllexport)
	#else
		#define PhysicsExport __declspec(dllimport)
	#endif

#endif

#if _DEBUG
	#pragma comment(lib,"EaterEngine_x64d.lib")
#else
	#pragma comment(lib,"EaterEngine_x64r.lib")
#endif


