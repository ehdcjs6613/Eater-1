#include "MathHelper.h"
#include "Effects.h"
#include "d3dx11effect.h"
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
	mView = _view;
	mProj = _proj;
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
		// 메시 데이터를 하나 꺼내옴.
		MeshData* _Mesh_Data = meshList->front();

		/// 오브젝트들을 그린다. (Draw Primitive)
		if (_Mesh_Data->ObjType != OBJECT_TYPE::BASE)
		{
			meshList->pop();
			continue;
		}

		// 해당 메시의 VB,IB 를 받아옴.
		Render_VB = reinterpret_cast<ID3D11Buffer*>(_Mesh_Data->VB->VertexbufferPointer);
		Render_IB = reinterpret_cast<ID3D11Buffer*>(_Mesh_Data->IB->IndexBufferPointer);

		// 매쉬 텍스쳐 정보에서 캐스팅해서 그걸 밑에 이펙트에 넣으면 나올거임
		//_Mesh_Data->Diffuse->TextureBufferPointer;

		// 입력 배치 객체 셋팅
		m_pDeviceContext->IASetInputLayout(InputLayouts::PosNormalTexBiNormalTangent);
		m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// 버텍스버퍼와 인덱스버퍼 셋팅
		Vertex_Buffer_Stride = _Mesh_Data->VB->VertexDataSize;
		Vertex_Buffer_Offset = 0;

		/// WVP TM등을 셋팅
		mWorld = _Mesh_Data->mWorld;//_Mesh_Data->mWorld;
		//mWorld = DirectX::SimpleMath::Matrix();
		Mul_WVP = mWorld * mView * mProj;

		// 월드의 역행렬
		World_Inverse = mWorld.Invert();

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

		// 월드 Eye 포지션.
		DirectX::SimpleMath::Vector3 _Camera_Vec(mView._41, mView._42, mView._43);
		Effects::BasicTextureFX->SetEyePosW(_Camera_Vec);

		ID3DX11EffectTechnique* mTech = nullptr;

		/// 텍스쳐 사용
		mTech = Effects::BasicTextureFX->Light1TexTech;

		D3DX11_TECHNIQUE_DESC techDesc;
		mTech->GetDesc(&techDesc);

		for (UINT p = 0; p < techDesc.Passes; ++p)
		{

			m_pDeviceContext->IASetVertexBuffers(0, 1, &Render_VB, &Vertex_Buffer_Stride, &Vertex_Buffer_Offset);
			m_pDeviceContext->IASetIndexBuffer(Render_IB, DXGI_FORMAT_R32_UINT, 0);

			World_Inverse_Transpose = MathHelper::InverseTranspose(mWorld);
			Effects::BasicTextureFX->SetWorld(mWorld);
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
