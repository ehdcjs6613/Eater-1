struct FullScreenVertexIn
{
	float3 PosL     : POSITION;
	float2 Tex      : TEXCOORD;
};

struct FullScreenVertexOut
{
	float4 PosH    : SV_POSITION;
	float2 Tex     : TEXCOORD;
};

FullScreenVertexOut Light_VS(FullScreenVertexIn vin)
{
	FullScreenVertexOut vout;

	//���� �������� ��ȯ
	vout.PosH = float4(vin.PosL, 1.0f);

    vout.Tex = vin.Tex;

	return vout;
}