#pragma once
class PhysEngine;

class PhysManager
{
public:
	PhysManager();
	~PhysManager();


	void Initialize();	//�ʱ�ȭ 
	void Release();		//����
	void Update(float m_Time);

private:
	PhysEngine* Phys;
};