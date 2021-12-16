#pragma once

#include "DxDefine.h"

#include <vector>
#include <deque>
#include <list>
#include <map>
#include <stack>

class Collider;


/// <summary>
/// �ڷᱸ���� ���ɸ鿡�� ������� �����ұ�?
/// �� < ĸ�� < ���� < �޽�(����) < �޽�(�񺼷�)
/// 
/// ������� �ʰ����� 
/// ���Ի����� ���ٸ�, ����Ʈ, ��
/// ���Ի����� �ƴ� ȣ���� ���ٸ� ����
/// �ݶ��̴� �˻��� �Ѵٸ� Ʈ�� ���� ����
/// </summary>

class ColliderManager
{
public:
	ColliderManager();
	~ColliderManager();
public:
	std::map<int,Collider*> m_ColliderVec;
public:
	ID3D11Device* md3dDevice;						/// D3D11 ����̽�
	ID3D11DeviceContext* md3dImmediateContext;		/// ����̽� ���ؽ�Ʈ

	int m_ColliderNum;
public:
	//
	//�׸��⸦ ���� , ����̽� �ʱ�ȭ�� ���� �Լ�
	void Initialize(ID3D11Device*,ID3D11DeviceContext*);
	//ó�� ��ġ�� ������Ʈ��
	void AllSet();
	void Update();

	//�ݶ��̴��� ������ �����͸� Ǫ��
	void Push(Collider*);
	void DeviceSet(Collider*);
};

///�ϴ� ó���� �ݶ��̴� �޽��� �׷����Ѵ�.
