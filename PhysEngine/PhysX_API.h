#pragma once

#include "PhysEngineDLL.h"


///ENGINE ����
//1. ����� ������ ����
//2. PhysX���� �����ϴ� Debug���� ����Ұ�����
extern "C" PHYS_ENGINEDLL void PhysX_Initialize(int ThreadCount,bool OnDebug);		//����

///ENGINE ����
extern "C" PHYS_ENGINEDLL void PhysX_Release();

///ENGINE ������Ʈ
//1.�����Ӵ��� �ð� (��Ÿ Ÿ��)
extern "C" PHYS_ENGINEDLL void PhysX_Update(float m_time);	//����

///����
extern "C"  PHYS_ENGINEDLL void PhysX_CreateInstance(PhysData data);	//��ü ����
extern "C"	PHYS_ENGINEDLL PhysData GetActors();
extern "C"  PHYS_ENGINEDLL void PhysX_CreateScene();						//�� ����



