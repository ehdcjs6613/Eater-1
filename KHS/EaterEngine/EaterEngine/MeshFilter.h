#pragma once

#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif

#include <string>
#include "Component.h"
#include "../SharedData.h"

/// <summary>
/// 각각의 매쉬정보를 파서에서 받아오고 저장해두는 컨퍼넌트
/// 현재는 테스트용이다 다시만들어야 할수도있음
/// </summary>
class FBXModel;
class DH3DEngine;
class MeshFilter : public Component
{
public:
	EATER_ENGINEDLL MeshFilter();
	virtual ~MeshFilter();

	// Component을(를) 통해 상속됨
	virtual void Awake() override;

	virtual void Start() override;

	virtual void Update() override;


	static HWND hWnd;
	EATER_ENGINEDLL void SetMeshName(std::string mMeshName);
	EATER_ENGINEDLL void SetBuffer(FBXModel* Model);
private:
	std::string MeshName;
	FBXModel* MeshFilterData;


	DH3DEngine* pTest_Engine;
	OneFrameData* pTest_OFD;
	SharedRenderData* pTest_SRD;
	DHParser::Mesh* pTest_Mesh;
};

