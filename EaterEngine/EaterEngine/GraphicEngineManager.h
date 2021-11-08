#pragma once
#include <windows.h>
#include <map>
#include <string>
#include <queue>

/// <summary>
///	�������� �׷��ȿ����� ���� ����ϱ����� ���� �׷��ȿ��� ���� �Ŵ���
/// </summary>

class MeshData;
struct GlobalData;
class GraphicEngine;

class Indexbuffer;
class Vertexbuffer;
class TextureBuffer;
class Grahpics2D;

namespace ParserData
{
	struct Mesh;
}


class GraphicEngineManager
{
public:
	GraphicEngineManager();
	~GraphicEngineManager();


	//����� �׷��ȿ����� ����Ʈ�� �ִ´�
	template<typename T>
	void PushEngine(std::string Name);

	//��� �׷��� ���� �ʱ�ȭ
	void EngineAllInitialize(HWND Hwnd,int WinSizeWidth,int WinSizeHeight);
	//����� �׷��ȿ��� ����
	void ChoiceEngine(std::string Name);
public:
	//������ �׷��ȿ����� �ʱ�ȭ
	void Initialize(HWND Hwnd, int WinSizeWidth, int WinSizeHeight);

	//������ �׷��ȿ��� ������
	void Render(std::queue<MeshData*>* meshList, GlobalData* global);

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

	//�׷��� �������� ������ ����Ʈ
	std::map<std::string,GraphicEngine*> GEngineList;
};

template<typename T>
inline void GraphicEngineManager::PushEngine(std::string Name)
{
	T* temp = new T();
	GEngineList.insert({Name,temp});
}
