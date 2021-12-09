#pragma once

#include <fstream>

#include "DxDefine.h"
#include "DllDefine.h"
#include "VirtualMesh.h"
#include "BuildGeometry.h"
#include "Collider.h"

class GameObject;
class VertexPositionColor;
class VertexBuffer;
class IndexBuffer;
class Transform;

class BoxCollider : public Collider
{
private:
	struct Vertex
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT4 Color;
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
	DirectX::XMMATRIX mWorld;	// ���� ��ȯ ��� (����->����)
	DirectX::XMMATRIX mView;	// �þ� ��ȯ ��� (ī�޶� ��)
	DirectX::XMMATRIX mProj;	// ���� ��ȯ ��� (����/����)


	// ����������Ʈ. �������� ��� �� ���ΰ��� ���� ��.
	ID3D11RasterizerState* m_pRenderstate;			/// �ܺο��� �����ؼ� ������ ��Ȳ�� ���� ������. ���̴����� �ص� �ȴ�.

public:
	float m_Size[3];

public:
	PhysicsExport BoxCollider();
	PhysicsExport virtual ~BoxCollider();
public:
	//���� �ܰ迡 ������� ����Ǵ� �Լ�
	virtual void Awake() override;
	//���� �Լ�
	virtual void Start() override;
	//ó��
	virtual void StartUpdate() override;
	//�̵� ��� ������Ʈ
	virtual void TransformUpdate() override;
	//���� ������Ʈ
	virtual void PhysicsUpdate() override;
	//�Ϲ� ������Ʈ
	virtual void Update() override;
	//������ ������Ʈ
	virtual void EndUpdate() override;
private:
	//�׷��ִ� �Լ�
	void Draw(const DirectX::XMFLOAT4X4 _View, const DirectX::XMFLOAT4X4 _Proj, const DirectX::XMFLOAT4X4 _WorldTM);
	//����ؼ� �浹üũ�ϴ� OBB(Orient Bounding Box)�Լ�
	//������ ���� ���̵�
	void CalculateOBB();
	//���ĵ� ������������� �浹
	void CalculateAABB();
public:
	void Initialize(ID3D11Device*, ID3D11DeviceContext*, VertexPositionColor* , UINT );
};
