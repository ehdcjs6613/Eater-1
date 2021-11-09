#include "MainHeader.hlsli"

struct VertexInputType
{
    float3 PosL : POSITION;
    float2 Tex : TEXCOORD;
    float3 Nomal : NORMAL;
    float3 Tangent : TANGENT;
    
    uint4 BoneIndex0 : BONEINDEX;
    uint4 BoneIndex1 : BONEINDEX;
    uint4 BoneIndex2 : BONEINDEX;
    
    float4 BoneWeights0 : BONEWEIGHT;
    float4 BoneWeights1 : BONEWEIGHT;
    float4 BoneWeights2 : BONEWEIGHT;
    
    
};

struct PixelInputType
{
    float4 posH : SV_POSITION;
    float2 Tex : TEXCOORD;
    float3 Nomal : NORMAL;
    float3 Tangent : TANGENT;
};


PixelInputType main(VertexInputType input)
{
    PixelInputType output;
   
	//���庯ȯ
	
    output.posH = mul(float4(input.PosL.xyz, 1.0f), world);
    output.posH = mul(float4(output.posH.xyz, 1.0f), view);
    output.posH = mul(float4(output.posH.xyz, 1.0f), proj);
    
    output.Tex = float2(0, 0);
    output.Nomal = mul(input.Nomal, (float3x3) view);
    output.Nomal = mul(output.Nomal, (float3x3) proj);
    
    output.Tangent = mul(input.Tangent, (float3x3) world);
    
    
    
   
    return output;
}