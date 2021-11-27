struct VS_INPUT
{
    float3 inPos    : POSITION;
    float3 inColor  : COLOR;
};
struct VS_INPUT_TEX
{
    float3 inPos : POSITION;
    float2 inTexCoord : TEXCOORD;
};
struct VS_OUTPUT
{
    float4 outPosition : SV_POSITION;
    float3 outColor : COLOR;
};
struct VS_OUTPUT_TEX
{
    float4 outPosition : SV_POSITION;
    float2 outTexCoord : TEXCOORD;
};



VS_OUTPUT_TEX main(VS_INPUT_TEX input)
{
    VS_OUTPUT_TEX output;
    output.outPosition = float4(input.inPos, 1.0f);
    output.outTexCoord = input.inTexCoord;
    
    
    return output;
}