#pragma once
/// <summary>
/// ������ ���� �Ŵ���
/// </summary>
#include "Data.h" 

struct ID3D11Device;
struct ID3D11DeviceContext;
class BufferData;

class GraphicDebugManager;
class ShaderManager;
class TextureBase;
class HsGraphic;
class GlobalData;
class MeshData;

struct ID3D11RasterizerState;

class RenderingManager
{
public:
	enum class ShaderType
	{
		BASIC,
		SKINNING,
	};


	RenderingManager();
	~RenderingManager();
	void Initialize(ID3D11Device* mDeviece, ID3D11DeviceContext* mDeviceContext,
		ShaderManager* SM,GraphicDebugManager* DM);


	void CreateTexture();

	//ī�޶� ���۸� ������Ʈ 
	void CameraUpdate(GlobalData* data);
	//��Ű�� ���۸� ������Ʈ
	void SkinningUpdate(MeshData* data);
	//�Ž� ���۸� ������Ʈ
	void MeshUpdate(MeshData* data);
	void BoneUpdate(MeshData* data);


	void DebugUpdate();


	void Rendering(MeshData* data, ShaderType type);
	void CreateRenderState();
	void GetShader();
private:
	ID3D11Device*		 Device;
	ID3D11DeviceContext* DeviceContext;


	ShaderManager*			mShaderManager;		//���̴� �Ŵ���
	GraphicDebugManager*	mDebugManager;		//����� �Ŵ���


	ID3D11RasterizerState* mWireframe;
	ID3D11RasterizerState* mSolid;


	ShaderData BasicMesh_SH;
	ShaderData SknningMesh_SH;
	ShaderData DebugMesh_SH;

	ID3D11SamplerState* BasicSampler;
};