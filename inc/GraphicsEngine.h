#pragma once

#include "framework.h"
#include "EngineData.h"
#include "ParserData.h"

#include "windows.h"
#include <string>
#include <queue>

/// <summary>
/// ���� �������� �����ϴ� �׷��� ���� �ֻ��� Ŭ����
/// ��Ŭ������ ��ӹ��� �׷��� ������ �����ϸ� �ȴ� 
/// </summary>

class MeshData;
//class Model;
class GlobalData;

//class Indexbuffer;
//class Vertexbuffer;


#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif

class Indexbuffer;
class Vertexbuffer;
class TextureBuffer;

namespace ParserData 
{
	struct Model;
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
	virtual Indexbuffer* CreateIndexBuffer(ParserData::Model* mModel)	= 0;	//�ε��� ���۸� ������ش�
	virtual Vertexbuffer* CreateVertexBuffer(ParserData::Model* mModel)	= 0;	//���ؽ� ���۸� ������ش�
	virtual TextureBuffer* CreateTextureBuffer(std::string path)  = 0;					//�ؽ��ĸ� ������ش�
	virtual void OnReSize(int Change_Width, int Change_Height) = 0;			//��������
	virtual void Delete() = 0;


	/// �������� �Ѵ� �Ž� ���������� ����Ʈ, �۷ι� ������
	virtual void Render(std::queue<MeshData*>* meshList, GlobalData* global) = 0;
};