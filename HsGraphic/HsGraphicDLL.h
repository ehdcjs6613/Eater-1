#pragma once

#ifdef HSGRAPHIC_INTERFACE
#define HS_GRAPHICDLL __declspec(dllexport)
#else
#define HS_GRAPHICDLL __declspec(dllimport)
#pragma comment(lib,"HsGraphic_x64d")


#ifdef _DEBUG
#define HS_GRAPHICDLL __declspec(dllimport)
#pragma comment(lib,"HsGraphic_x64d")
#else
#define HS_GRAPHICDLL __declspec(dllimport)
#pragma comment(lib,"HsGraphic_x64r")
#endif

#endif