#pragma once

interface IShaderManager;
interface IGraphicResourceManager;
interface IGraphicResourceFactory;

///
/// 2021/11/08 2:22
/// SeoKyuHwang
///
/// # RenderBase Class
///
/// - ���� Rendering Class���� �ش� Rendering�� �´� GraphicResource ������ ����
///   ���� Manager & DeviceContext�� �������� �ΰ� ���
/// 
class RenderPassBase
{
public:
	RenderPassBase() = default;
	virtual ~RenderPassBase() = default;

public:
	virtual void Create(int width, int height) abstract;
	virtual void Start(int width, int height) abstract;

	virtual void OnResize(int width, int height) abstract;
	virtual void Release() abstract;

	virtual void SetOption(const char* shaderName) {}

public:
	static void Initialize(Microsoft::WRL::ComPtr<ID3D11DeviceContext> context, IGraphicResourceFactory* factory, IGraphicResourceManager* resourceManager, IShaderManager* shaderManager);
	static void Reset();

public:
	friend class RenderManager;

protected:
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext> g_Context;

	static IGraphicResourceFactory* g_Factory;
	static IGraphicResourceManager* g_Resource;
	static IShaderManager* g_Shader;
};