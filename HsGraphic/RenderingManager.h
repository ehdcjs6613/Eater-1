#pragma once
/// <summary>
/// 랜더링 관리 매니저
/// </summary>
 
struct ID3D11Device;
struct ID3D11DeviceContext;

class TextureBase;
class HsGraphic;
class RenderingManager
{
public:
	RenderingManager();
	~RenderingManager();
	void Initialize(ID3D11Device* mDeviece, ID3D11DeviceContext* mDeviceContext);
	void CreateTexture();


	void Begin();
	void End();
private:
	ID3D11Device*		 Device;
	ID3D11DeviceContext* DeviceContext;


	TextureBase* Post;
};