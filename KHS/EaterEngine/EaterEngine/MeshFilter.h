#pragma once

#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif

#include <string>
#include <vector>
#include "Component.h"


/// <summary>
/// 매쉬정보를 파서에서 받아오고 저장해두는 컨퍼넌트
/// </summary>

struct MeshData;
class Transform;
class FBXModel;
class DH3DEngine;
class MeshFilter : public Component
{
public:
	EATER_ENGINEDLL MeshFilter();
	virtual ~MeshFilter();

	virtual void Start() override;

	virtual void EndUpdate() override;

	EATER_ENGINEDLL void SetMeshName(std::string mMeshName);


	static std::vector<MeshData*>* GetMeshData();
private:
	//매쉬 로드여부
	bool isLoad;

	std::string MeshName;
	FBXModel* MeshFilterData;


	Transform* transform;
	MeshData* Meshtemp;


	static std::vector<MeshData*> MeshList;
};

