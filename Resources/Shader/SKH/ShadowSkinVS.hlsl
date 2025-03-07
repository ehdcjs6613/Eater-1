cbuffer cbShadowObject : register(b0)
{
    float4x4 gWorldViewProj : packoffset(c0);
};

cbuffer cbSkinned : register(b1)
{
    float4x4 gBoneTransforms[96];
};

struct SkinVertexIn
{
    uint4 BoneIndices1 : BONEINDICES1;
    uint4 BoneIndices2 : BONEINDICES2;
    float4 BoneWeights1 : WEIGHTS1;
    float4 BoneWeights2 : WEIGHTS2;
    
    float3 PosL : POSITION;
};

float4 main(SkinVertexIn vin) : SV_POSITION
{
    float3 posL = float3(0.0f, 0.0f, 0.0f);

    for (int i = 0; i < 4; ++i)
    {
        posL += vin.BoneWeights1[i] * mul(gBoneTransforms[vin.BoneIndices1[i]], float4(vin.PosL, 1.0f)).xyz;
    }
	
    for (int j = 0; j < 4; ++j)
    {
        posL += vin.BoneWeights2[j] * mul(gBoneTransforms[vin.BoneIndices2[j]], float4(vin.PosL, 1.0f)).xyz;
    }
	
    
    return mul(gWorldViewProj, float4(posL, 1.0f));
};