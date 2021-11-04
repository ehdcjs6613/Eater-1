#pragma once

#include "GraphicsEngine.h"

/// <summary>
/// 우진 리가 만들 그래그래픽스엔진
/// </summary>

class WJEngine : public GraphicEngine
{
public:
	WJEngine();
	virtual ~WJEngine() final;

	//
public:
	


public:
	//상속
	/// <summary>
	/// 무조건 그래픽 엔진쪽에서 만들어야 하는것들
	/// </summary>

	//게임 엔진쪽에서 윈도우 핸들을 넘겨줄것임
	virtual void Initialize(HWND _hWnd, int screenWidth, int screenHeight) override;


	///그래픽 엔진과 게임엔진에서 주고받아야할 함수들
	virtual Indexbuffer* CreateIndexBuffer(ParserData::Model* mModel) override;			//인덱스 버퍼를 만들어준다
	virtual Vertexbuffer* CreateVertexBuffer(ParserData::Model* mModel) override;		//버텍스 버퍼를 만들어준다
	virtual void CreateTextureBuffer() override;												//텍스쳐를 만들어준다
	virtual void OnReSize(float Change_Width, float Change_Height)override;				//리사이즈


	/// 랜더링을 한다 매쉬 랜더데이터 리스트, 글로벌 데이터
	virtual void Render(std::queue<MeshData*>* meshList, GlobalData* global) override;
};

