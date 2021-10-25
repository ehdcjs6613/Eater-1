#pragma once
#include <functional>
#include <map>
#include <string>
class Scene;

/// <summary>
/// ��ũ���� ���� ���ִ� ��ũ�� �Ŵ���
/// </summary>

#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif


class SceneManager
{
public:
	~SceneManager();

	template<typename T>
	void CreateScene(typename std::enable_if<std::is_base_of<Scene, T>::value, bool>::type t = std::is_base_of<Scene, T>::value);
	EATER_ENGINEDLL void SetName(std::string Name);

	void LoadScene(std::string SceneName);	//��ũ�� ����
	void Delete();
	void SceneStart();		//��ũ���� Awack Start�Լ��� ����
	void SceneUpdate();		//��ũ���� Update �Լ��� ����


	
	static EATER_ENGINEDLL SceneManager* GM();
private:
	//���� ��ũ��
	Scene* NowScene;
	std::string SceneName;

	//��ũ�� ����Ʈ
	std::map<std::string, Scene*> SceneList;
private:
	//�̱���
	SceneManager();
	static SceneManager* Instance;
};

template<typename T>
inline void SceneManager::CreateScene(typename std::enable_if<std::is_base_of<Scene, T>::value, bool>::type t)
{
	T* temp = new T();

	temp->AwakeFunction = std::bind(&T::Awake, temp);
	temp->StartFunction = std::bind(&T::Start, temp);
	temp->UpdateFunction = std::bind(&T::Update, temp);
	temp->EndFunction = std::bind(&T::End, temp);

	SceneList.insert({ SceneName, temp });
}
