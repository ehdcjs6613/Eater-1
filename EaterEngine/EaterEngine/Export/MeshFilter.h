#pragma once

#include "EaterEngineDLL.h"

#include <string>
#include "Component.h"
/// <summary>
/// �Ž������� �ļ����� �޾ƿ��� �����صδ� ���۳�Ʈ
/// </summary>

class MeshFilter : public Component
{
public:
	EATER_ENGINEDLL MeshFilter();
	virtual ~MeshFilter();

	virtual void Start() override;
public:
	//�޽��� �̸��� ������ ������ �ε�
	EATER_ENGINEDLL void SetMeshName(std::string mMeshName);
private:
	//�Ž� �ε忩��
	bool isLoad;
	std::string MeshName;
};

