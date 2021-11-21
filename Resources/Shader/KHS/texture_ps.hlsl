#include "MainHeader.hlsli"

#define TEXTURE_MASK_MAIN   0x00000001 //�����ؽ��� ����
#define TEXTURE_MASK_SUB    0x00000010 //�����ؽ��� ����
#define TEXTURE_MASK_NOMAL  0x00000100 //�븻�ؽ��� ����

struct PixelInputType
{
    float4 posH     : SV_POSITION;
    float2 Tex      : TEXCOORD;
    float3 Nomal    : NORMAL;
    float3 Tangent  : TANGENT;
};


//struct PixeloutputType
//{
//    float4 color : SV_Target0;
//};

float4 main(PixelInputType input) : SV_TARGET
{ 
    //PixeloutputType output;
    float4 color = { 0, 0, 0, 0 };
    color = MainTexture.Sample(SampleType, input.Tex);

    return color;
}