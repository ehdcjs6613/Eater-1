#pragma once
#include <DirectXMath.h>

//씬 기준 매쉬마다 존재하지않아도 되는것들
struct GlobalData
{
	//카메라 정보들
	DirectX::XMMATRIX mViewMX;
	DirectX::XMMATRIX mProj;
};

//한개의 매쉬에 존재하는 데이터
struct MeshData
{
	//World
	DirectX::XMMATRIX mViewMX;
	


};


