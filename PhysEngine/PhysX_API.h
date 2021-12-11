#pragma once

#include "PhysEngineDLL.h"


///ENGINE 생성
//1. 사용할 쓰레드 개수
//2. PhysX에서 제공하는 Debug툴을 사용할것인지
extern "C" PHYS_ENGINEDLL void PhysX_Initialize(int ThreadCount,bool OnDebug);		//생성

///ENGINE 삭제
extern "C" PHYS_ENGINEDLL void PhysX_Release();

///ENGINE 업데이트
//1.프레임단위 시간 (델타 타임)
extern "C" PHYS_ENGINEDLL void PhysX_Update(float m_time);	//실행

///생성
extern "C"  PHYS_ENGINEDLL void PhysX_CreateInstance(PhysData data);	//객체 생성
extern "C"	PHYS_ENGINEDLL PhysData GetActors();
extern "C"  PHYS_ENGINEDLL void PhysX_CreateScene();						//씬 생성



