#include "SkyBox.h"
#include "GeometryGenerator.h"
#include "DDSTextureLoader.h"

SkyBox::SkyBox(ID3D11Device* device, const ATL::CString& cubemapFilename, float skySphereRadius)
{
	ID3D11Resource* texResource = nullptr;
	HR(DirectX::CreateDDSTextureFromFile(device, cubemapFilename, &texResource, &mCubeMapSRV));
	ReleaseCOM(texResource); // view saves reference

	GeometryGenerator::MeshData sphere;
	GeometryGenerator geoGen;
	geoGen.CreateSphere(skySphereRadius, 30, 30, sphere);

	std::vector<XMFLOAT3> vertices(sphere.Vertices.size());

	for (size_t i = 0; i < sphere.Vertices.size(); ++i)
	{
		vertices[i] = sphere.Vertices[i].Position;
	}

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(XMFLOAT3) * vertices.size();
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = &vertices[0];

	HR(device->CreateBuffer(&vbd, &vinitData, &mVB));


	mIndexCount = sphere.Indices.size();

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(USHORT) * mIndexCount;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.StructureByteStride = 0;
	ibd.MiscFlags = 0;

	std::vector<USHORT> indices16;
	indices16.assign(sphere.Indices.begin(), sphere.Indices.end());

	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &indices16[0];

	HR(device->CreateBuffer(&ibd, &iinitData, &mIB));
}

SkyBox::~SkyBox()
{
	ReleaseCOM(mVB);
	ReleaseCOM(mIB);
	ReleaseCOM(mCubeMapSRV);
}

ID3D11ShaderResourceView* SkyBox::CubeMapSRV()
{
	return mCubeMapSRV;
}

void SkyBox::Draw(ID3D11DeviceContext* dc, OneFrameData* _OFD)
{
	// center Sky about eye in world space
	DirectX::SimpleMath::Vector3 eyePos = _OFD->World_Eye_Position;
	DirectX::SimpleMath::Matrix T = XMMatrixTranslation(eyePos.x, eyePos.y, eyePos.z);


	DirectX::SimpleMath::Matrix WVP = T * _OFD->View_Matrix * _OFD->Projection_Matrix;

	Effects::SkyFx->SetWorldViewProj(WVP);
	Effects::SkyFx->SetCubeMap(mCubeMapSRV);


	UINT stride = sizeof(XMFLOAT3);
	UINT offset = 0;
	dc->IASetVertexBuffers(0, 1, &mVB, &stride, &offset);
	dc->IASetIndexBuffer(mIB, DXGI_FORMAT_R16_UINT, 0);
	dc->IASetInputLayout(InputLayouts::Pos);
	dc->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3DX11_TECHNIQUE_DESC techDesc;
	Effects::SkyFx->SkyTech->GetDesc(&techDesc);

	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		ID3DX11EffectPass* pass = Effects::SkyFx->SkyTech->GetPassByIndex(p);

		pass->Apply(0, dc);

		dc->DrawIndexed(mIndexCount, 0, 0);
	}
}
