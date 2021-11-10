#pragma once

#include "EaterEngineDLL.h"
#include "Component.h"
#include <vector>
#include <string>

class LoadMeshData;
class Transform;
class ObjectManager;
class GameObject;

namespace ParserData 
{
	class Mesh;
}

namespace DirectX
{
	namespace SimpleMath
	{
		struct Matrix;
	}
}




class SkinningFilter :public Component
{
public:

	EATER_ENGINEDLL SkinningFilter();
	virtual EATER_ENGINEDLL ~SkinningFilter();

	virtual void Awake();
	//모델을 넣어준다
	//메쉬의 이름을 넣으면 데이터 로드
	EATER_ENGINEDLL void SetMeshName(std::string mMeshName);


	static void SetObjMananager(ObjectManager* obj);

private:
	//게임오브젝트의 LoadData를 합쳐준다
	void PushModelData(LoadMeshData* mModel);

	//LoadMeshData를 게임에 사용할 오브젝트로 생성하면서 값을 넣어준다
	void ChangeLoadBoneData(LoadMeshData* data, Transform* parent);
	void ChangeLoadMeshData(LoadMeshData* data, Transform* parent);


	//Transform을 연결한다
	void LinkHierarchy(Transform* my, Transform* parent);

	//매쉬 로드여부
	bool isLoad;
	std::string MeshName;

	//본정보들
	std::vector<DirectX::SimpleMath::Matrix>* BoneTMList;	//본 매트릭스
	std::vector<ParserData::Mesh*>* BoneList;				//본 매쉬

	//스키닝 오브젝트
	GameObject* SkinningObject;




	static ObjectManager* OBJ_Manager;
};