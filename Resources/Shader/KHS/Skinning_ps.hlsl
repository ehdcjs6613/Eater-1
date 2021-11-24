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


struct PixeloutputType
{
    float4 color : SV_Target0;
};

PixeloutputType main(PixelInputType input)
{
    PixeloutputType output;
    output.color = MainTexture.Sample(SampleType, input.Tex);

    return output;
}