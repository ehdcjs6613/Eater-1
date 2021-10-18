#include "Component.h"
#include "GameObject.h"
#include "DebugManager.h"
#include "ObjectManager.h"

ObjectManager* ObjectManager::instance = nullptr;
ObjectManager* ObjectManager::GM()
{
	if (instance == nullptr)
	{
		instance = new ObjectManager();
	}

	return instance;
}

ObjectManager::ObjectManager()
{


}

ObjectManager::~ObjectManager()
{


}

void ObjectManager::PushCreateObject(GameObject* obj)
{
	//오브젝트를 넣어줄때 빈곳이 있는지부터 확인
	std::vector<GameObject*>::iterator it = ObjectList.begin();
	for (it; it != ObjectList.end(); it++)
	{
		if ( (*it) == nullptr)
		{
			//빈곳을 찾았다면 빈곳에 넣어주고 함수 종료
			(*it) = obj;
			return;
		}
	}

	//빈곳이없다면 그냥 넣어줌
	ObjectList.push_back(obj);
}

void ObjectManager::PushDeleteObject(GameObject* obj)
{
	//오브젝트를 넣어줄때 빈곳이 있는지부터 확인
	std::vector<GameObject*>::iterator it = ObjectList.begin();
	for (it; it != ObjectList.end(); it++)
	{
		//삭제할 오브젝트를 찾았다면 그오브젝트를 일단 리스트에서 뺀다
		if ((*it) == obj)
		{
			GameObject* temp = (*it);
			(*it) = nullptr;

			//삭제할 리스트에 넣어준다
			DeleteList.push(temp);
		}
	}
}

void ObjectManager::PushStartUpdate(Component* mComponent)
{
	//컨퍼넌트들의 업데이트 함수만 모아놓은 리스트에 들어온 컨퍼넌트 업데이트 함수를 넣어줌
	StartUpdate.Push(mComponent, std::bind(&Component::Update, mComponent));
}

void ObjectManager::PushDefaultUpdate(Component* mComponent)
{
	DefaultUpdate.Push(mComponent, std::bind(&Component::Update, mComponent));
}

void ObjectManager::PushFinalUpdate(Component* mComponent)
{
	//가장 마지막에 실행되는 업데이트 함수리스트에 넣는다
	FinalUpdate.Push(mComponent, std::bind(&Component::Update, mComponent));
}

void ObjectManager::PushStart(Component* mComponent)
{
	StartFunction.Push(mComponent, std::bind(&Component::Start, mComponent));
}

void ObjectManager::PushAwake(Component* mComponent)
{
	AwakeFunction.Push(mComponent, std::bind(&Component::Awake, mComponent));
}

void ObjectManager::PlayUpdate()
{
	DebugManager::GM()->Print("////////////Update////////////\n");

	//가장 먼저실행되는 StartUpdate 함수 리스트
	DebugManager::GM()->Print("->StartUpdate 실행 \n");
	StartUpdate.Play();
	
	//중간 단계에 실행되는 Update 함수 리스트
	DebugManager::GM()->Print("->DefaultUpdate 실행\n");
	DefaultUpdate.Play();

	//가장 마지막에 실행되는 Update 함수 리스트
	DebugManager::GM()->Print("->FinalUpdate 실행\n");
	FinalUpdate.Play();

	///랜더링






	///삭제
	DeleteObject();
}

void ObjectManager::PlayStart()
{
	DebugManager::GM()->Print("////////////start////////////\n");
	DebugManager::GM()->Print("->Awake 실행 \n");
	AwakeFunction.Play();
	DebugManager::GM()->Print("->Start 실행 \n");
	StartFunction.Play();
}

void ObjectManager::ClearFunctionList()
{
	StartUpdate.Clear();
	FinalUpdate.Clear();
}

void ObjectManager::DeleteObject()
{
	//삭제할 오브젝트 만큼 반복문을 돈다
	for (unsigned i = 0; i < DeleteList.size(); i++)
	{
		//큐에서 가장먼저들어온 오브젝트를 꺼낸다
		GameObject* temp = DeleteList.front();

		for (int j = 0; j < temp->GetComponentCount(); j++)
		{
			Component* cpt = temp->GetDeleteComponent();

			//컨퍼넌트 삭제 함수포인터 리스트에서 그컨퍼넌트의 함수포인터를찾아서 삭제
			DeleteComponent(cpt);

			//삭제 했으니 삭제할 리스트에서도 빼준다
			DeleteList.pop();
		}
	}
}

void ObjectManager::DeleteComponent(Component* cpt)
{
	//시작단계의 함수포인터에서 넣어놨던 함수들을 삭제
	AwakeFunction.Pop(cpt);
	StartFunction.Pop(cpt);


	int state = cpt->GetUpdateState();
	//컨퍼넌트가 어떤 업데이트 함수포인터의 들어가있는지 확인하고 삭제
	switch (state)
	{
	case (int)COMPONENT_STATE::DEFAULT_UPDATE:
		DefaultUpdate.Pop(cpt);
		break;
	case (int)COMPONENT_STATE::START_UPDATE:
		StartUpdate.Pop(cpt);
		break;
	case (int)COMPONENT_STATE::END_UPDATE:
		FinalUpdate.Pop(cpt);
		break;
	}

	///이쪽에서 랜더링 함수포인터에 넣었던 것을 삭제시키면 될듯






	///진짜 컨퍼넌트 삭제
	delete cpt;
}
