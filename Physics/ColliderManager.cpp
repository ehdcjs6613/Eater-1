#include "Collider.h"
#include "ColliderManager.h"


ColliderManager::ColliderManager() : m_ColliderNum(0), md3dDevice(nullptr), md3dImmediateContext(nullptr)
{
}

ColliderManager::~ColliderManager()
{
}

void ColliderManager::Initialize(ID3D11Device* _pDevice, ID3D11DeviceContext* _pDeviceContext)
{
	md3dDevice = _pDevice;
	md3dImmediateContext = _pDeviceContext;
}

void ColliderManager::AllSet()
{
	//unsigned int ColliderCnt = m_ColliderVec.size();
	std::map<int,Collider*>::iterator CEnd = m_ColliderVec.end();

	for (std::map<int, Collider*>::iterator Cit = m_ColliderVec.begin(); Cit != CEnd; Cit++)
	{
		(*Cit).second->SetDevice(md3dDevice);
		
		(*Cit).second->SetDeviceContext(md3dImmediateContext);

	}

	//m_ColliderVec;
}

void ColliderManager::Update()
{

}

void ColliderManager::Push(Collider* _pCollider)
{

	if (nullptr != _pCollider)
	{
		DeviceSet(_pCollider);
		m_ColliderVec.emplace(m_ColliderNum,_pCollider);
		m_ColliderNum++;
	}
	

}

void ColliderManager::DeviceSet(Collider* _pCollider)
{
	if (nullptr != _pCollider)
	{
		_pCollider->SetDevice(md3dDevice);
		_pCollider->SetDeviceContext(md3dImmediateContext);
	}
}
