#pragma once
class PhysEngine;

class PhysManager
{
public:
	PhysManager();
	~PhysManager();


	void Initialize();	//�ʱ�ȭ 
	void Release();		//����
	void Update();

private:
	PhysEngine* Phys;
};