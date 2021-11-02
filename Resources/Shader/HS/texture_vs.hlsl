#include "MainHeader.hlsli"

struct VertexInputType
{
	float3 PosL			: POSITION;
	float2 Tex			: TEXCOORD;
};

struct PixelInputType
{
	float4 posH			: SV_POSITION;
	float2 Tex			: TEXCOORD0;
};


PixelInputType main(VertexInputType input)
{
    PixelInputType output;
    input.PosL = 1.0f;
	//월드변환
	
	output.posH = float4(1,1,1,1);
	output.Tex = float2(1, 1);

	//uv값
    //output.Tex = mul(float4(input.Tex, 0.0f, 1.0f), UITexMatrix);
       
    return output;
}