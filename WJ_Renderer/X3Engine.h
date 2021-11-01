#pragma once
#include "GraphicsEngine.h"

class DirectXDevice;
class DirectXDeviceContext;

class X3Engine : public GraphicEngine
{
private:
	//[초기화 변수들]
	HWND				  m_hWnd;
	
	DirectXDevice*		  m_pDevice;
	DirectXDeviceContext* m_pDeviceContext;
private:
	int					  m_iWidth;
	int					  m_iHeight;

public:

public:
	X3Engine();
	~X3Engine();
public:
	
	//GraphicEngine class로부터 상속 , 게임 엔진쪽에서 윈도우 핸들을 넘겨줄것임
	virtual void Initialize(HWND _hWnd, int screenWidth, int screenHeight) override;


	///그래픽 엔진과 게임엔진에서 주고받아야할 함수들
	virtual Indexbuffer*  CreateIndexBuffer(ParserData::Model* mModel) override;	//인덱스 버퍼를 만들어준다
	virtual Vertexbuffer* CreateVertexBuffer(ParserData::Model* mModel) override;	//버텍스 버퍼를 만들어준다
	virtual void		  CreateTextureBuffer() override;									//텍스쳐를 만들어준다
	virtual void		  OnReSize(float Change_Width, float Change_Height) override;			//리사이즈


	/// 랜더링을 한다 매쉬 랜더데이터 리스트, 글로벌 데이터
	virtual void		  Render(std::queue<MeshData*>* meshList, GlobalData* global) override;
};

