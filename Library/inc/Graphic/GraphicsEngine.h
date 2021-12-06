#pragma once
#include <windows.h>
#include <string>
#include <queue>
#include "GraphicDLL.h"

/// <summary>
/// ���� �������� �����ϴ� �׷��� ���� �ֻ��� Ŭ����
/// �ش� Ŭ������ ���� Graphic Engine�� ���� �� �ִ�..
/// </summary>

class MeshData;
class GlobalData;
class Indexbuffer;
class Vertexbuffer;
class TextureBuffer;

namespace ParserData 
{
	class Mesh;
}

class GraphicEngine
{
public:
	GraphicEngine() {};
	virtual GRAPHIC_DLL ~GraphicEngine() {};

	///�׷��� ������ ���� �� �ִ� �Լ�
	static GRAPHIC_DLL GraphicEngine* Create();

	/// ���� Ŵ ���� �׷��� ���� ����
	static GRAPHIC_DLL GraphicEngine* CreateHS();

	///�׷��� ������ ���ӿ������� �ְ�޾ƾ��� �Լ���
	virtual GRAPHIC_DLL void Initialize(HWND _hWnd, int screenWidth, int screenHeight) = 0;	// �ʱ�ȭ �Լ�
	virtual GRAPHIC_DLL Indexbuffer* CreateIndexBuffer(ParserData::Mesh* mModel) = 0;		// �ε��� ���۸� ������ش�
	virtual GRAPHIC_DLL Vertexbuffer* CreateVertexBuffer(ParserData::Mesh* mModel)	= 0;	// ���ؽ� ���۸� ������ش�
	virtual GRAPHIC_DLL TextureBuffer* CreateTextureBuffer(std::string path)  = 0;			// �ؽ��ĸ� ������ش�
	virtual GRAPHIC_DLL void OnReSize(int Change_Width, int Change_Height) = 0;				// ��������
	virtual GRAPHIC_DLL void Delete() = 0;

	/// �������� �Ѵ� �Ž� ���������� ����Ʈ, �۷ι� ������
	virtual GRAPHIC_DLL void Render(std::queue<MeshData*>* meshList,GlobalData* global) = 0;
	virtual GRAPHIC_DLL void ShadowRender(std::queue<MeshData*>* meshList, GlobalData* global) { return; };
	virtual GRAPHIC_DLL void SSAORender() { return; };
	virtual GRAPHIC_DLL void UIRender(std::queue<MeshData*>* meshList, GlobalData* global) { return; };
};
