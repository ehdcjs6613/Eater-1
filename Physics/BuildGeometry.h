#pragma once
#include "DxDefine.h"
#include "d3dx11effect.h"

struct Build
{
	void BuildFX(const char* _csoPath, ID3D11Device* _pDevice);
	void BuildVertexLayOut(ID3D11Device* _pDevice);
	void BuildRelease();

	ID3DX11Effect* mFX;
	ID3DX11EffectTechnique* mTech;
	ID3DX11EffectMatrixVariable* mfxWorldViewProj;
	ID3D11InputLayout* mInputLayout;
};