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

namespace ParserData 
{
	struct Mesh;
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
	virtual void Render(std::queue<MeshData*>* meshList, GlobalData* global) = 0;
};