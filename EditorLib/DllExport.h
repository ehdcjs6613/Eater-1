#pragma once

#ifdef DEBUG
#define VS_MFC_EXPORT __declspec(dllexport)
#else
#define VS_MFC_EXPORT __declspec(dllexport)

#endif // DEBUG