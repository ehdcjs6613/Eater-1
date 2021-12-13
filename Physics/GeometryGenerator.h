#pragma once
class GeometryGenerator
{
public:
	GeometryGenerator();
	~GeometryGenerator();




public:
	/// 메시형태로 그릴 함수
	bool CreateMeshForBox();
	bool CreateMeshForSphere();
	bool CreateMeshForCylinder();
public:
	/// 라인으로만 그릴 함수
	bool CreateLineForBox();
	bool CreateLineForSphere();
	bool CreateLineForCylinder();

};

