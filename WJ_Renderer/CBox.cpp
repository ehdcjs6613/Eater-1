#include "MathHelper.h"
#include "Effects.h"
#include "../Physics/d3dx11effect.h"
#include "InputLayout.h"
#include "EngineData.h"
#include "CBox.h"

CBox::CBox()
{
}

CBox::~CBox()
{
}

void CBox::Update(DirectX::SimpleMath::Matrix _view, DirectX::SimpleMath::Matrix _proj)
{
	m_View = _view;
	m_Proj = _proj;
}

void CBox::Initialize(ID3D11Device* _pDevice, ID3D11DeviceContext* _pDeviceContext)
{
	m_pDevice		 = _pDevice		  ;
	m_pDeviceContext = _pDeviceContext;
}

void CBox::Render(std::queue<MeshData*>* meshList)
{
	while (!meshList->empty())
	{
		// �޽� �����͸� �ϳ� ������.
		MeshData* _Mesh_Data = meshList->front();

		/// ������Ʈ���� �׸���. (Draw Primitive)
		if (_Mesh_Data->ObjType != OBJECT_TYPE::BASE)
		{
			meshList->pop();
			continue;
		}

		// �ش� �޽��� VB,IB �� �޾ƿ�.
		Render_VB = reinterpret_cast<ID3D11Buffer*>(_Mesh_Data->VB->VertexbufferPointer);
		Render_IB = reinterpret_cast<ID3D11Buffer*>(_Mesh_Data->IB->IndexBufferPointer);

		// �Ž� �ؽ��� �������� ĳ�����ؼ� �װ� �ؿ� ����Ʈ�� ������ ���ð���
		//_Mesh_Data->Diffuse->TextureBufferPointer;

		// �Է� ��ġ ��ü ����
		m_pDeviceContext->IASetInputLayout(InputLayouts::PosNormalTexBiNormalTangent);
		m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// ���ؽ����ۿ� �ε������� ����
		Vertex_Buffer_Stride = _Mesh_Data->VB->VertexDataSize;
		Vertex_Buffer_Offset = 0;

		/// WVP TM���� ����


		m_World = _Mesh_Data->mWorld;//_Mesh_Data->mWorld;
		//mWorld = DirectX::SimpleMath::Matrix();
		Mul_WVP = m_World * m_View * m_Proj;

		// ������ �����
		World_Inverse = m_World.Invert();

		// Set per frame constants.
		DirectionalLight _temp_Dir;
		DirectX::SimpleMath::Vector4 _Ambient = DirectX::SimpleMath::Vector4(0.8f, 0.8f, 0.8f, 1.0f);
		DirectX::SimpleMath::Vector4 _Diffuse = DirectX::SimpleMath::Vector4(0.5f, 0.5f, 0.5f, 1.0f);
		DirectX::SimpleMath::Vector4 _Specular = DirectX::SimpleMath::Vector4(0.5f, 0.5f, 0.5f, 1.0f);
		DirectX::SimpleMath::Vector3 _Direction = DirectX::SimpleMath::Vector3(-0.57735f, -0.57735f, 0.57735f);
		_temp_Dir.Ambient = _Ambient;
		_temp_Dir.Diffuse = _Diffuse;
		_temp_Dir.Specular = _Specular;
		_temp_Dir.Direction = _Direction;

		Material _Temp_Mat;
		DirectX::SimpleMath::Vector4 _Ambient1 = DirectX::SimpleMath::Vector4(0.8f, 0.8f, 0.8f, 1.0f);
		DirectX::SimpleMath::Vector4 _Diffuse1 = DirectX::SimpleMath::Vector4(0.5f, 0.5f, 0.5f, 1.0f);
		DirectX::SimpleMath::Vector4 _Specular1 = DirectX::SimpleMath::Vector4(0.5f, 0.5f, 0.5f, 1.0f);
		DirectX::SimpleMath::Vector4 _Reflect1 = DirectX::SimpleMath::Vector4(0.5f, 0.5f, 0.5f, 1.0f);
		_Temp_Mat.Ambient = _Ambient1;
		_Temp_Mat.Diffuse = _Diffuse1;
		_Temp_Mat.Specular = _Specular1;
		_Temp_Mat.Reflect = _Reflect1;


		Effects::BasicTextureFX->SetDirLights(&_temp_Dir);

		// ���� Eye ������.
		DirectX::SimpleMath::Vector3 _Camera_Vec(m_View._41, m_View._42, m_View._43);
		Effects::BasicTextureFX->SetEyePosW(_Camera_Vec);

		ID3DX11EffectTechnique* mTech = nullptr;

		/// �ؽ��� ���
		mTech = Effects::BasicTextureFX->Light1TexTech;

		D3DX11_TECHNIQUE_DESC techDesc;
		mTech->GetDesc(&techDesc);

		for (UINT p = 0; p < techDesc.Passes; ++p)
		{

			m_pDeviceContext->IASetVertexBuffers(0, 1, &Render_VB, &Vertex_Buffer_Stride, &Vertex_Buffer_Offset);
			m_pDeviceContext->IASetIndexBuffer(Render_IB, DXGI_FORMAT_R32_UINT, 0);

			World_Inverse_Transpose = MathHelper::InverseTranspose(m_World);
			Effects::BasicTextureFX->SetWorld(m_World);
			Effects::BasicTextureFX->SetWorldInvTranspose(World_Inverse_Transpose);
			Effects::BasicTextureFX->SetWorldViewProj(Mul_WVP);
			Effects::BasicTextureFX->SetMaterial(_Temp_Mat);
			Effects::BasicTextureFX->SetTexTransform(DirectX::SimpleMath::Matrix::Identity);
			Effects::BasicTextureFX->SetDiffuseMap((ID3D11ShaderResourceView*)(_Mesh_Data->Diffuse->TextureBufferPointer));

			mTech->GetPassByIndex(p)->Apply(0, m_pDeviceContext);
			m_pDeviceContext->DrawIndexed(_Mesh_Data->IB->Count, 0, 0);
		}
		meshList->pop();

	}
}
