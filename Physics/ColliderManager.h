#pragma once

#include "DxDefine.h"

#include <vector>
#include <deque>
#include <list>
#include <map>
#include <stack>

class Collider;


/// <summary>
/// 자료구조의 성능면에서 어느것이 적당할까?
/// 구 < 캡슐 < 상자 < 메시(볼록) < 메시(비볼록)
/// 
/// 빈번하진 않겠지만 
/// 삽입삭제가 많다면, 리스트, 덱
/// 삽입삭제가 아닌 호출이 많다면 벡터
/// 콜라이더 검색만 한다면 트리 관련 구조
/// </summary>

class ColliderManager
{
public:
	ColliderManager();
	~ColliderManager();
public:
	std::map<int,Collider*> m_ColliderVec;
public:
	ID3D11Device* md3dDevice;						/// D3D11 디바이스
	ID3D11DeviceContext* md3dImmediateContext;		/// 디바이스 컨텍스트

	int m_ColliderNum;
public:
	//
	//그리기를 위한 , 디바이스 초기화를 위한 함수
	void Initialize(ID3D11Device*,ID3D11DeviceContext*);
	//처음 배치된 오브젝트로
	void AllSet();
	void Update();

	//콜라이더가 입혀진 데이터를 푸시
	void Push(Collider*);
	void DeviceSet(Collider*);
};

///일단 처음엔 콜라이더 메쉬를 그려야한다.
