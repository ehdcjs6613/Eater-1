#pragma once

#include "EaterEngineDLL.h"

#include <string>
#include "Component.h"
/// <summary>
/// 매쉬정보를 파서에서 받아오고 저장해두는 컨퍼넌트
/// </summary>

class LoadMeshData;
class Transform;
class ObjectManager;

class  MeshFilter : public Component
{
public:
	EATER_ENGINEDLL MeshFilter();
	virtual ~MeshFilter();

	virtual void Awake() override;

	static void SetObjMananager(ObjectManager* obj);
public:
	//메쉬의 이름을 넣으면 데이터 로드
	EATER_ENGINEDLL void SetMeshName(std::string mMeshName);

	//게임오브젝트의 LoadData를 합쳐준다
	void PushModelData(LoadMeshData* mModel);

	//LoadMeshData를 게임에 사용할 오브젝트로 생성하면서 값을 넣어준다
	void ChangeLoadMeshData(LoadMeshData* data,Transform* parent);

	//Transform을 연결한다
	void LinkHierarchy(Transform* my,Transform*parent);
private:
	//매쉬 로드여부
	bool isLoad;

	std::string MeshName;

	static ObjectManager* OBJ_Manager;

	
};

