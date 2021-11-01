#pragma once
#include "GraphicsEngine.h"

class DirectXDevice;
class DirectXDeviceContext;

class X3Engine : public GraphicEngine
{
private:
	//[�ʱ�ȭ ������]
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
	
	//GraphicEngine class�κ��� ��� , ���� �����ʿ��� ������ �ڵ��� �Ѱ��ٰ���
	virtual void Initialize(HWND _hWnd, int screenWidth, int screenHeight) override;


	///�׷��� ������ ���ӿ������� �ְ�޾ƾ��� �Լ���
	virtual Indexbuffer*  CreateIndexBuffer(ParserData::Model* mModel) override;	//�ε��� ���۸� ������ش�
	virtual Vertexbuffer* CreateVertexBuffer(ParserData::Model* mModel) override;	//���ؽ� ���۸� ������ش�
	virtual void		  CreateTextureBuffer() override;									//�ؽ��ĸ� ������ش�
	virtual void		  OnReSize(float Change_Width, float Change_Height) override;			//��������


	/// �������� �Ѵ� �Ž� ���������� ����Ʈ, �۷ι� ������
	virtual void		  Render(std::queue<MeshData*>* meshList, GlobalData* global) override;
};

