#pragma once

#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif

#include "Component.h"
class MeshFilter : public Component
{
public:
	EATER_ENGINEDLL MeshFilter();
	virtual ~MeshFilter();


	
	// Component��(��) ���� ��ӵ�
	virtual void Awake() override;

	virtual void Start() override;

	virtual void Update() override;
private:

};

