#include "MainHeader.hlsli"

#define TEXTURE_MASK_MAIN   0x00000001 //�����ؽ��� ����
#define TEXTURE_MASK_SUB    0x00000010 //�����ؽ��� ����
#define TEXTURE_MASK_NOMAL  0x00000100 //�븻�ؽ��� ����

struct PixelInputType
{
    float4 posH : SV_POSITION;
    float3 COLOR : COLOR;
};


//struct PixeloutputType
//{
//    float4 color : SV_Target0;
//};

float3 main(PixelInputType input) : SV_TARGET
{ 
    return input.COLOR;
}