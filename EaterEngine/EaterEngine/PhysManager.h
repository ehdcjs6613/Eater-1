#pragma once
class PhysEngine;

class PhysManager
{
public:
	PhysManager();
	~PhysManager();


	void Initialize();	//�ʱ�ȭ 
	void Release();		//����

	
private:
	PhysEngine* Phys;
};