#pragma once
#include "windows.h"
#include <queue>
/// <summary>
/// ���� �������� �����ϴ� �׷��� ���� �ֻ��� Ŭ����
/// ��Ŭ������ ��ӹ��� �׷��� ������ �����ϸ� �ȴ� 
/// </summary>


class MeshData;
class GlobalData;

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



	virtual void CreateIndexBuffer()	= 0;	//�ε��� ���۸� ������ش�
	virtual void CreateVertexBuffer()	= 0;	//���ؽ� ���۸� ������ش�
	virtual void CreateTextureBuffer()  = 0;	//�ؽ��ĸ� ������ش�


	/// �������� �Ѵ� �Ž� ���������� ����Ʈ, �۷ι� ������
	virtual void Render(std::queue<MeshData*> meshList, GlobalData* global) = 0;
};