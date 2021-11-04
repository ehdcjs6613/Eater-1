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
	//포스트 프로세싱 전용 텍스쳐 생성
	Post = new TextureBase();
	Post->Create();
}

void RenderingManager::Begin()
{

}

void RenderingManager::End()
{

}
