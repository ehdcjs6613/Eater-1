#pragma once

#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif

#include <string>
#include "Component.h"


/// <summary>
/// 매쉬정보를 파서에서 받아오고 저장해두는 컨퍼넌트
/// </summary>
class Transform;
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

	virtual void Update()override;

	virtual void EndUpdate() override;

	EATER_ENGINEDLL void SetMeshName(std::string mMeshName);
private:
	std::string MeshName;
	FBXModel* MeshFilterData;
};

