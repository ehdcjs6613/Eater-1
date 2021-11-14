#pragma once
#include <windows.h>
#include <map>
#include <string>
#include <queue>

/// <summary>
///	�������� �׷��ȿ����� ���� ����ϱ����� ���� �׷��ȿ��� ���� �Ŵ���.
/// </summary>

class MeshData;
class GlobalData;
class GraphicEngine;

class Indexbuffer;
class Vertexbuffer;
class TextureBuffer;

namespace ParserData
{
	class Mesh;
}


class GraphicEngineManager
{
public:
	GraphicEngineManager();
	~GraphicEngineManager();


	//����� �׷��ȿ����� ����Ʈ�� �ִ´�
	template<typename T>
	void PushEngine(std::string Name);

	void Update();
	//��� �׷��� ���� �ʱ�ȭ
	void EngineAllInitialize(HWND Hwnd,int WinSizeWidth,int WinSizeHeight);
	//����� �׷��ȿ��� ����
	void ChoiceEngine(std::string Name);
public:
	//������ �׷��ȿ����� �ʱ�ȭ
	void Initialize(HWND Hwnd, int WinSizeWidth, int WinSizeHeight);

	//������ �׷��ȿ��� ������
	void Render(std::queue<MeshData*>* meshList, GlobalData* global);
	void ShadowRender(std::queue<MeshData*>* meshList, GlobalData* global);
	void SSAORender(std::queue<MeshData*>* meshList, GlobalData* global);
	void UIRender(std::queue<MeshData*>* meshList, GlobalData* global);

	//������ �׷��ȿ������� �ε������۸� ������
	Indexbuffer* CreateIndexBuffer(ParserData::Mesh* mModel);

	//������ �׷��� �������� ���ؽ� ���۸� ������
	Vertexbuffer* CreateVertexBuffer(ParserData::Mesh* mModel);

	//������ �׷��ȿ������� �ؽ��� ����
	TextureBuffer* CreateTextureBuffer(std::string Name);

	//������ �׷��� �������� Resize
	void OnReSize(int Change_Width, int Change_Height);

	//��� ���� ����
	void Delete();
private:
	//���� ���õ� �׷��� ����
	GraphicEngine* NowEngine;

	std::string EngineName;
	//�׷��� �������� ������ ����Ʈ
	std::map<std::string,GraphicEngine*> GEngineList;
};

template<typename T>
inline void GraphicEngineManager::PushEngine(std::string Name)
{
	T* temp = new T();
	GEngineList.insert({Name,temp});
}
