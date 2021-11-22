#pragma once
#include <Windows.h>

class XGeometry
{
public:
	XGeometry();
	virtual ~XGeometry();
public:
	//BOOL Initialize(ID3D11Device*, ID3D11DeviceContext* );
	BOOL BuildGeometry();
	BOOL BuildFX();
	BOOL BuildLayout();

};

