struct PS_INPUT
{
    float4 inPosition : SV_POSITION;
    float3 inColor : COLOR;
};

struct PS_INPUT_TEX
{
    float4 inPosition : SV_POSITION;
    float2 inTexCoord : TEXCOORD;
};

Texture2D ObjectTexture : TEXTURE : register(t0);
SamplerState ObjectSamplerState : SAMPLER : register(s0);

float4 main(PS_INPUT_TEX input) : SV_TARGET
{
    float3 PixelColor = ObjectTexture.Sample(ObjectSamplerState, input.inTexCoord);
    return float4(PixelColor, 1.0f);

}