//#include "MainHeader.hlsli"

#define TEXTURE_MASK_MAIN   0x00000001 //�����ؽ��� ����
#define TEXTURE_MASK_SUB    0x00000010 //�����ؽ��� ����
#define TEXTURE_MASK_NOMAL  0x00000100 //�븻�ؽ��� ����

struct PixelInputType
{
    float4 posH : SV_POSITION;
    float3 PosL : POSITION;
    float2 Tex : TEXCOORD0;
};


struct PixeloutputType
{
    float4 color : SV_Target0;
};

PixeloutputType main(PixelInputType input)
{
    PixeloutputType output;
    output.color = float4(1, 0, 0, 1);

    return output;
}