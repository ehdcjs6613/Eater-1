#pragma once

#include "GraphicsEngine.h"

/// <summary>
/// ���� ���� ���� �׷��׷��Ƚ�����
/// </summary>

class WJEngine : public GraphicEngine
{
public:
	WJEngine();
	virtual ~WJEngine() final;

	//
public:
	


public:
	//���
	/// <summary>
	/// ������ �׷��� �����ʿ��� ������ �ϴ°͵�
	/// </summary>

	//���� �����ʿ��� ������ �ڵ��� �Ѱ��ٰ���
	virtual void Initialize(HWND _hWnd, int screenWidth, int screenHeight) override;


	///�׷��� ������ ���ӿ������� �ְ�޾ƾ��� �Լ���
	virtual Indexbuffer* CreateIndexBuffer(ParserData::Model* mModel) override;			//�ε��� ���۸� ������ش�
	virtual Vertexbuffer* CreateVertexBuffer(ParserData::Model* mModel) override;		//���ؽ� ���۸� ������ش�
	virtual void CreateTextureBuffer() override;												//�ؽ��ĸ� ������ش�
	virtual void OnReSize(float Change_Width, float Change_Height)override;				//��������


	/// �������� �Ѵ� �Ž� ���������� ����Ʈ, �۷ι� ������
	virtual void Render(std::queue<MeshData*>* meshList, GlobalData* global) override;
};

