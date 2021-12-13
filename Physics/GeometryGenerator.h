#pragma once
class GeometryGenerator
{
public:
	GeometryGenerator();
	~GeometryGenerator();




public:
	/// �޽����·� �׸� �Լ�
	bool CreateMeshForBox();
	bool CreateMeshForSphere();
	bool CreateMeshForCylinder();
public:
	/// �������θ� �׸� �Լ�
	bool CreateLineForBox();
	bool CreateLineForSphere();
	bool CreateLineForCylinder();

};

