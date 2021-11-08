#pragma once
#include "windows.h"
#include <string>
#include <queue>
/// <summary>
/// ���� �������� �����ϴ� �׷��� ���� �ֻ��� Ŭ����
/// ��Ŭ������ ��ӹ��� �׷��� ������ �����ϸ� �ȴ� 
/// </summary>

class MeshData;
struct GlobalData;
class Indexbuffer;
class Vertexbuffer;
class TextureBuffer;
class Grahpics2D;

namespace ParserData 
{
	struct Mesh;
}


class GraphicEngine
{
protected:
	//�������̽����� 2d�� ��� �޾Ƽ� ��� ������ ������ 2d supporter
	Grahpics2D* m_p2DSupport;

public:
	GraphicEngine() {};
	virtual ~GraphicEngine() 
	{
		delete m_p2DSupport;
		m_p2DSupport = nullptr;
	};

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
	virtual void Render(std::queue<MeshData*>* meshList, GlobalData* global) = 0;
};