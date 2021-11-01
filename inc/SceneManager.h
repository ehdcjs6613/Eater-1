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
	SceneManager();

	//��ũ�� �Ŵ��� �ʱ�ȭ
	void Initialize();

	//������ �� �ֱ�
	void PushScene(Scene* mScene,std::string SceneName);

	//�� ����
	void ChoiceScene(std::string SceneName);

	//���� Awack Start�Լ��� ����
	void SceneStart();
	//���� �ٸ������� �Ѿ���� ������ ����
	void SceneEnd();


	//��ũ�� �Ŵ��� ������Ʈ
	void Update();		

	//�Ŵ��� ����
	void Delete();
private:
	//���� ��ũ��
	Scene* NowScene;
	std::string SceneName;

	//��ũ�� ����Ʈ
	std::map<std::string, Scene*> SceneList;
private:
};