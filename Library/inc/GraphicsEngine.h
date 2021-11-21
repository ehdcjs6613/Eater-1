#pragma once
#include "windows.h"
#include <string>
#include <queue>
/// <summary>
/// ���� �������� �����ϴ� �׷��� ���� �ֻ��� Ŭ����
/// ��Ŭ������ ��ӹ��� �׷��� ������ �����ϸ� �ȴ�
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
	virtual ~GraphicEngine() {};

	/// <summary>
	/// ������ �׷��� �����ʿ��� ������ �ϴ°͵�
	/// </summary>

	//���� �����ʿ��� ������ �ڵ��� �Ѱ��ٰ���
	virtual void Initialize(HWND _hWnd, int screenWidth, int screenHeight)= 0;

	///�׷��� ������ ���ӿ������� �ְ�޾ƾ��� �Լ���
	virtual Indexbuffer* CreateIndexBuffer(ParserData::Mesh* mModel)	= 0;	//�ε��� ���۸� ������ش�
	virtual Vertexbuffer* CreateVertexBuffer(ParserData::Mesh* mModel)	= 0;	//���ؽ� ���۸� ������ش�
	virtual TextureBuffer* CreateTextureBuffer(std::string path)  = 0;					//�ؽ��ĸ� ������ش�
	virtual void OnReSize(int Change_Width, int Change_Height) = 0;			//��������
	virtual void Delete() = 0;

	/// �������� �Ѵ� �Ž� ���������� ����Ʈ, �۷ι� ������
	virtual void Render(std::queue<MeshData*>* meshList,GlobalData* global) = 0;
	virtual void ShadowRender(std::queue<MeshData*>* meshList, GlobalData* global) { return; };
	virtual void SSAORender() { return; };
	virtual void UIRender(std::queue<MeshData*>* meshList, GlobalData* global) { return; };

	/// ����Ÿ�ٿ� �ش��ϴ� �����͸� �Ѱ��ٰ���
	virtual void SetViewPort(void* VPT, int Change_Width, int Change_Height) { return; }; //����Ÿ�ٺ�, �������ٽ�,����Ʈ
	virtual void SetDevice(void* Devie, void* DevieContext) { return; }; //����̽�,���ؽ�Ʈ
};