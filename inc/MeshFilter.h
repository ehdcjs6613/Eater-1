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

class MeshFilter : public Component
{
public:
	EATER_ENGINEDLL MeshFilter();
	virtual ~MeshFilter();

	virtual void Start() override;
public:
	//메쉬의 이름을 넣으면 데이터 로드
	EATER_ENGINEDLL void SetMeshName(std::string mMeshName);
private:
	//매쉬 로드여부
	bool isLoad;
	std::string MeshName;
};

