#pragma once
#include <DirectXMath.h>
#include "Component.h"

#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif


class Transform;
class Camera : public Component
{
public:
	EATER_ENGINEDLL Camera();
	virtual ~Camera();

	virtual void Awake();
	virtual void Update();

	//메인 카메라 여부
	bool MainCamera;

	//프로젝션 행렬을 가져온다
	DirectX::XMMATRIX GetProj();

	//뷰행렬을 가져온다
	DirectX::XMMATRIX GetView();

	//뷰행렬과 프로젝션 행렬을 곱한값을 가져온다
	DirectX::XMMATRIX GetView_Proj();
	
private:
	Transform* tranform;

	//프로젝션 행렬 생성하기
	void CreateProj(float fovY = 0.5f * 3.141592f,float aspect = 1,float zn = 0.1f,float zf = 4000.0f,bool viewPoint = false);
	void CreateView();

	float mNearZ;
	float mFarZ;
	float mAspect;
	float mFovY;
	float mNearWindowHeight;
	float mFarWindowHeight;

	//프로젝션
	DirectX::XMFLOAT4X4 mProj;
	DirectX::XMMATRIX mProj_M;

	//뷰
	DirectX::XMFLOAT4X4 mView;
	DirectX::XMMATRIX mView_M;
};