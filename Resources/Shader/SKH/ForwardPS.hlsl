Texture2D gDiffuseMap : register(t0);

SamplerState samWrapMinLinear : register(s0);

struct PixelIn
{
    float4 PosW : SV_POSITION;
    float3 NormalW : NORMALW;
    float2 Tex : TEXCOORD;
};

float4 main(PixelIn pin) : SV_Target0
{
    float4 pout;
    
    //pout = gDiffuseMap.Sample(samWrapMinLinear, pin.Tex);
    pout = float4(1.0f, 0.0f, 0.0f, 1.0f);
    
    return pout;
}