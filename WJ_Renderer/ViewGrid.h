#pragma once

/// <summary>
/// 씬 안에서 보여줄 그리드를 그려주는 클래스이다.
/// </summary>
//class Transform;
#include "OneCompile.h"
#include "XGeometry.h"

class ID3DX11Effect;
class ID3DX11EffectTechnique;
class ID3DX11EffectMatrixVariable;

class ViewGrid : public XGeometry
{
private:
	DirectX::XMMATRIX m_World;
	DirectX::XMMATRIX m_View;
	DirectX::XMMATRIX m_Projection;


	ID3DX11Effect* m_FX;
	ID3DX11EffectTechnique* mTech;
	ID3DX11EffectMatrixVariable* mfxWorldViewProj;

	ID3D11Buffer* m_VB;
	ID3D11Buffer* m_IB;
	ID3D11RasterizerState* m_pRenderstate;;

	ID3D11InputLayout* mInputLayout;
	ID3D11Device* m_d3dDevice;						// D3D11 디바이스
	ID3D11DeviceContext* m_d3dImmediateContext;		// 디바이스 컨텍스트

public:
	ViewGrid();
	ViewGrid(const ViewGrid& _pViewGrid);
	~ViewGrid();
	
public:
	virtual BOOL Initialize(ID3D11Device*, ID3D11DeviceContext* , ID3D11RasterizerState* ) override;
	virtual BOOL BuildGeometry() override;
	virtual BOOL BuildFX() override;
	virtual BOOL BuildLayout() override;
	virtual BOOL Update(const DirectX::XMMATRIX& world, const DirectX::XMMATRIX& view, const DirectX::XMMATRIX& proj) override;
	virtual BOOL Destroy() override;

public:
	virtual void Render() override;
};

