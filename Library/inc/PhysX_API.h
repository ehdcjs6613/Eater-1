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

///Dinamic ��ü ����
//1.������ ������ ������ ���� PhysData ����ü
//retrun ��ü�� ã���� �ʿ��� �ε��� ��ȯ
extern "C"  PHYS_ENGINEDLL int PhysX_Create_DinamicActor(PhysData data);
extern "C"  PHYS_ENGINEDLL int PhysX_Create_StaticActor(PhysData data);


///Dinamic ��ü ��������
//1.������ ������ �����͸� �����´�
//return ã�� ������ ������
extern "C"	PHYS_ENGINEDLL PhysData Get_DinamicActors(int index);
extern "C"	PHYS_ENGINEDLL PhysData Get_StaticActors(int index);


extern "C"  PHYS_ENGINEDLL void PhysX_CreateScene();					



