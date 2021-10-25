#pragma once

#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif

#include <string>
#include "Component.h"


/// <summary>
/// �Ž������� �ļ����� �޾ƿ��� �����صδ� ���۳�Ʈ
/// </summary>
class Transform;
class FBXModel;
class DH3DEngine;
class MeshFilter : public Component
{
public:
	EATER_ENGINEDLL MeshFilter();
	virtual ~MeshFilter();

	// Component��(��) ���� ��ӵ�
	virtual void Awake() override;

	virtual void Start() override;

	virtual void Update()override;

	virtual void EndUpdate() override;

	EATER_ENGINEDLL void SetMeshName(std::string mMeshName);
private:
	std::string MeshName;
	FBXModel* MeshFilterData;
};

