#include "LightHelper.fx"

cbuffer cbLightSub : register(b0)
{
    float4x4 gViewProjTex : packoffset(c0);
    float3 gEyePosW : packoffset(c4.x);
    uint gInt : packoffset(c4.w);
}

cbuffer cbLight : register(b1)
{
    DirectionalLight gDirLights;
    PointLight gPointLights[5];
    SpotLight gSpotLights[5];
    Material gMaterials[5];
	
    uint gPointLightCount;
    uint gSpotLightCount;
};

Texture2D gAlbedoRT : register(t0);
Texture2D gNormalRT : register(t1);
Texture2D gPositionRT : register(t2);
Texture2D gShadowRT : register(t3);

Texture2D gSsaoMap : register(t4);
Texture2D gShadowMap : register(t5);

SamplerComparisonState gSamBorderComparisonLinearPoint : register(s0);
SamplerState gSamWrapLinear : register(s1);

struct VertexIn
{
    float4 PosH : SV_POSITION;
    float2 Tex : TEXCOORD;
};

float4 Light_PS(VertexIn pin) : SV_TARGET
{
    float4 albedo = gAlbedoRT.Sample(gSamWrapLinear, pin.Tex);
    float4 normal = gNormalRT.Sample(gSamWrapLinear, pin.Tex);
    float4 position = gPositionRT.Sample(gSamWrapLinear, pin.Tex);
    float4 shadow = gShadowRT.Sample(gSamWrapLinear, pin.Tex);
    float4 ssao = mul(gViewProjTex, float4(position.xyz, 1.0f));
	
    // Gamma Correction
	// Gamma Space -> Linear Space
	// ��� ������ ������ ���� �������� �̷������ �Ѵ�..
#ifdef GAMMA_CORRECTION
	albedo.rgb = pow(albedo.rgb, 2.2f);
#endif
    float4 litColor = albedo;

	// Start with a sum of zero.
    float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

	// View Direction
    float3 ViewDirection = gEyePosW - position.xyz;
    ViewDirection = normalize(ViewDirection);

	// ���� �ȼ��� Shadow ��..
    float shadows = 1.0f;
	
#ifdef SHADOW
    shadows = CalcShadowFactor(gSamBorderComparisonLinearPoint, gShadowMap, float3(shadow.xyz));
#endif	
	
	// ���� �ȼ��� SSAO ��..
    float ambientAccess = 1.0f;
	
#ifdef SSAO
    ssao /= ssao.w;
    ambientAccess = gSsaoMap.SampleLevel(gSamWrapLinear, ssao.xy, 0.0f).r;
#endif	
    
	// ���� �ȼ��� Material ID..
    uint matID = round(position.w);

    float4 A, D, S;
	
    if (shadow.w < 1.0f)
    {
		// Directional Light
        ComputeDirectionalLight(gMaterials[matID], gDirLights, float3(normal.xyz), ViewDirection,
			A, D, S);

        ambient += ambientAccess * A;
        diffuse += shadows * D;
        spec += shadows * S;


		// Point Light
        if (gPointLightCount > 0)
        {
            for (uint i = 0; i < gPointLightCount; ++i)
            {
                ComputePointLight(gMaterials[matID], gPointLights[i], float3(position.xyz), float3(normal.xyz), ViewDirection,
					A, D, S);

                ambient += A;
                diffuse += D;
                spec += S;
            }
        }

		// Spot Light
        if (gSpotLightCount > 0)
        {
			[unroll]
            for (uint i = 0; i < gSpotLightCount; ++i)
            {
                ComputeSpotLight(gMaterials[matID], gSpotLights[i], float3(position.xyz), float3(normal.xyz), ViewDirection,
					A, D, S);

                ambient += A;
                diffuse += D;
                spec += S;
            }
        }
		
		// Modulate with late add.
        litColor = albedo * (ambient + diffuse) + spec;
    }

	// Common to take alpha from diffuse material and texture.
    litColor.a = gMaterials[matID].Diffuse.a * albedo.a;

	// Gamma Correction
	// Normal Map�� ������������ ���..
	// Diffuse Map�� ������������ ���..
#ifdef GAMMA_CORRECTION
    if (normal.w < 1.0f)
        litColor.rgb = pow(litColor.rgb, 1.0f / 2.2f);
#endif
    
    return litColor;
}
