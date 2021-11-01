#pragma once

#include "StructHelper.h"
#include "SharedData.h"

class SkyBox
{
public:
	SkyBox(ID3D11Device* device, const ATL::CString& cubemapFilename, float skySphereRadius);
	~SkyBox();

	ID3D11ShaderResourceView* CubeMapSRV();

	void Draw(ID3D11DeviceContext* dc, OneFrameData* _OFD);

private:
	ID3D11Buffer* mVB;
	ID3D11Buffer* mIB;

	ID3D11ShaderResourceView* mCubeMapSRV;

	UINT mIndexCount;
};

