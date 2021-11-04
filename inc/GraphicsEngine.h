#pragma once

#include "framework.h"
#include "EngineData.h"
#include "ParserData.h"

#include "windows.h"
#include <string>
#include <queue>

/// <summary>
/// 게임 엔진에서 제공하는 그래픽 엔진 최상위 클래스
/// 이클래스를 상속받은 그래픽 엔진을 제작하면 된다 
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
	/// 무조건 그래픽 엔진쪽에서 만들어야 하는것들
	/// </summary>

	//게임 엔진쪽에서 윈도우 핸들을 넘겨줄것임
	virtual void Initialize(HWND _hWnd, int screenWidth, int screenHeight)= 0;


	///그래픽 엔진과 게임엔진에서 주고받아야할 함수들
	virtual Indexbuffer* CreateIndexBuffer(ParserData::Model* mModel)	= 0;	//인덱스 버퍼를 만들어준다
	virtual Vertexbuffer* CreateVertexBuffer(ParserData::Model* mModel)	= 0;	//버텍스 버퍼를 만들어준다
	virtual TextureBuffer* CreateTextureBuffer(std::string path)  = 0;					//텍스쳐를 만들어준다
	virtual void OnReSize(int Change_Width, int Change_Height) = 0;			//리사이즈
	virtual void Delete() = 0;


	/// 랜더링을 한다 매쉬 랜더데이터 리스트, 글로벌 데이터
	virtual void Render(std::queue<MeshData*>* meshList, GlobalData* global) = 0;
};