#include "RenderingManager.h"
#include "HsGraphic.h"
#include "TextureBase.h"
RenderingManager::RenderingManager()
{
	Device			= nullptr;
	DeviceContext	= nullptr;
}

RenderingManager::~RenderingManager()
{
	Device = nullptr;
	DeviceContext = nullptr;
}

void RenderingManager::Initialize(ID3D11Device* mDeviece, ID3D11DeviceContext* mDeviceContext)
{
	Device			= mDeviece;
	DeviceContext	= mDeviceContext;
	

	CreateTexture();
}

void RenderingManager::CreateTexture()
{
	//����Ʈ ���μ��� ���� �ؽ��� ����
	Post = new TextureBase();
	Post->Create();
}

void RenderingManager::Begin()
{

}

void RenderingManager::End()
{

}
