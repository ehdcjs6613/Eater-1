#pragma once

#include "OneCompile.h"
#include <queue>
class MeshData;

class BoxCol
{
	struct Vertex
	{
		XMFLOAT3 Pos;
		XMFLOAT4 Color;
	};
	ID3D11Device* md3dDevice;						/// D3D11 ����̽�
	ID3D11DeviceContext* md3dImmediateContext;		/// ����̽� ���ؽ�Ʈ

	ID3D11Buffer* mVB;	// ���ؽ�����
	ID3D11Buffer* mIB;	// �ε�������

	ID3DX11Effect* mFX;								// ����Ʈ
	ID3DX11EffectTechnique* mTech;					// ��ũ
	ID3DX11EffectMatrixVariable* mfxWorldViewProj;	// ����Ʈ�뺯��

	ID3D11InputLayout* mInputLayout;				// ��ǲ���̾ƿ�

	// ��ȯ ����
	XMMATRIX mWorld;	// ���� ��ȯ ��� (����->����)
	XMMATRIX mView;	// �þ� ��ȯ ��� (ī�޶� ��)
	XMMATRIX mProj;	// ���� ��ȯ ��� (����/����)


	// ����������Ʈ. �������� ��� �� ���ΰ��� ���� ��.
	ID3D11RasterizerState* m_pRenderstate;			/// �ܺο��� �����ؼ� ������ ��Ȳ�� ���� ������. ���̴����� �ص� �ȴ�.
public:
	BoxCol();
	~BoxCol();
public:
	void Update(DirectX::SimpleMath::Matrix _view, DirectX::SimpleMath::Matrix _proj);
	void Initialize(ID3D11Device*, ID3D11DeviceContext*);
	void Render(std::queue<MeshData*>* meshList);
public:
	void init();
};

