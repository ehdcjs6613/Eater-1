#pragma once
#include <windows.h>
#include <map>
#include <string>
#include <queue>

/// <summary>
///	�������� �׷��ȿ����� ���� ����ϱ����� ���� �׷��ȿ��� ���� �Ŵ���.
/// </summary>

class ObjectManager;
class MeshData;
class GlobalData;
class GraphicEngine;
class MultiRenderEngine;
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
public:
	//������ �׷��ȿ����� �ʱ�ȭ
	void Initialize(HWND Hwnd, int WinSizeWidth, int WinSizeHeight,ObjectManager* GM);

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

	//������ �־��ش�
	void PushEngine(int Number, GraphicEngine* Engine, std::string Name);

	void SplitWindow(int X, int Y);
private:
	MultiRenderEngine* MultiEngine;

	ObjectManager* ObjManager;

	std::string EngineName;
	//�׷��� �������� ������ ����Ʈ
	std::map<std::string,GraphicEngine*> GEngineList;
};

