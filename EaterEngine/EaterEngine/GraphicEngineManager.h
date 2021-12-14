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
	void BeginRender(UINT& renderOption);
	void Render(std::queue<MeshData*>* meshList, GlobalData* global);
	void ShadowRender(std::queue<MeshData*>* meshList, GlobalData* global);
	void SSAORender(GlobalData* global);
	void UIRender(std::queue<MeshData*>* meshList, GlobalData* global);
	void LightRender(GlobalData* global);
	void EndRender();

	//������ �׷��ȿ������� �ε������۸� ������
	Indexbuffer* CreateIndexBuffer(ParserData::Mesh* mModel);

	//������ �׷��� �������� ���ؽ� ���۸� ������
	Vertexbuffer* CreateVertexBuffer(ParserData::Mesh* mModel);
	//Terrain ���� ���ؽ� ���� �����Լ�
	Vertexbuffer* CreateTerrainVertexBuffer(ParserData::Mesh* mModel, std::string maskName);

	//������ �׷��ȿ������� �ؽ��� ����
	TextureBuffer* CreateTextureBuffer(std::string Name);

	//������ �׷��� �������� Resize
	void OnReSize(int Change_Width, int Change_Height);

private:
	GraphicEngine* GEngine;

	ObjectManager* ObjManager;
};

