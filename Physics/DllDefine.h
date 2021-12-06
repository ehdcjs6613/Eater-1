#pragma once


#if _DEBUG
	#ifdef PhysicsExportDLL
		#define PhysicsExport __declspec(dllimport)
	#else
		#define PhysicsExport __declspec(dllexport)
	#endif
#else //_Release
	#ifdef PhysicsExportDLL
		#define PhysicsExport __declspec(dllimport)
	#else
		#define PhysicsExport __declspec(dllexport)
	#endif

#endif

#if _DEBUG
	#pragma comment(lib,"EaterEngine_x64d.lib")
#else
	#pragma comment(lib,"EaterEngine_x64r.lib")
#endif


