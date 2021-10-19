//=============================================================================
// Basic.fx by Frank Luna (C) 2011 All Rights Reserved.
//
// Basic effect that currently supports transformations, lighting, and texturing.
//=============================================================================

#include "LightHelper.fx"
 
cbuffer cbPerFrame
{
	DirectionalLight gDirLights[3];
	float3 gEyePosW;

	float  gFogStart;
	float  gFogRange;
	float4 gFogColor;
};

cbuffer cbPerObject
{
	float4x4 gWorld;
	float4x4 gWorldInvTranspose;
	float4x4 gWorldViewProj;
	float4x4 gTexTransform;
	Material gMaterial;
}; 

// Nonnumeric values cannot be added to a cbuffer.
Texture2D gDiffuseMap;
// 노말맵 셋팅.
Texture2D gNormalMap;

SamplerState samAnisotropic
{
	//Filter = ANISOTROPIC;
	Filter = MIN_MAG_MIP_LINEAR;

	MaxAnisotropy = 4;

	AddressU = CLAMP;
	AddressV = CLAMP;
};

SamplerState samLinear
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};

struct VertexIn
{
	float3 PosL    : POSITION;
	float3 NormalL : NORMAL;
	float2 Tex     : TEXCOORD;
	float3 Bitangent : BITANGENT;
	float3 Tangent : TANGENT;
};

struct VertexOut
{
	float4 PosH    : SV_POSITION;
	float3 PosW    : POSITION;
	float2 Tex     : TEXCOORD;
	float3 ViewDirection : TEXCOORD1;
	float3 LightDirection[3] : DIRLIGHT;

	// Tangent 를 찍어보기 위해서..
	float3 NormalW : NORMAL;
	float3 Bitangent : BITANGENT;
	float3 Tangent : TANGENT;
};

VertexOut VS(VertexIn vin, uniform int gVLightCount)
{
	VertexOut vout;

	// 월드기준 포지션 좌표.
	vout.PosW = mul(float4(vin.PosL, 1.0f), gWorld).xyz;
	vout.PosH = mul(float4(vin.PosL, 1.0f), gWorldViewProj);
	// Output vertex attributes for interpolation across triangle.
	vout.Tex = mul(float4(vin.Tex, 0.0f, 1.0f), gTexTransform).xy;

	/// 월드 기준 좌표
	float3 ObejctPosition = mul(float4(vin.PosL, 1.0f), gWorld).xyz;
	float3 ViewDirection = gEyePosW - ObejctPosition;

	/// 탄젠트 스페이스상의 노말
	float3 Normal = mul(vin.NormalL, (float3x3)gWorldInvTranspose);
	/// 탄젠트 스페이스상의 Bitangent
	float3 BiTangent = mul(float4(vin.Bitangent, 1.0f), gWorldInvTranspose).xyz;
	/// 탄젠트 스페이스상의 tangent
	float3 Tangent = mul(float4(vin.Tangent, 1.0f), gWorldInvTranspose).xyz;

	// 라이트 Dir을 계산해서 새로 넣어준다.
	float3 LightDirection = float3(1, 1, 1);
	if (gVLightCount > 0)
	{
		// Sum the light contribution from each light source.  
		[unroll]
		for (int i = 0; i < gVLightCount; ++i)
		{
			LightDirection = -gDirLights[i].Direction;

			///// 탄젠트스페이스 상으로 Directional Light를 보낸다.
			//gDirLights[i].Direction.x = dot(Tangent, LightDirection);
			//gDirLights[i].Direction.y = dot(BiTangent, LightDirection);
			//gDirLights[i].Direction.z = dot(Normal, LightDirection);

			///// 노말라이즈 작업까지.
			//gDirLights[i].Direction = normalize(gDirLights[i].Direction);

			/// 탄젠트스페이스 상으로 Directional Light를 보낸다.
			vout.LightDirection[i].x = dot(Tangent, LightDirection);
			vout.LightDirection[i].y = dot(BiTangent, LightDirection);
			vout.LightDirection[i].z = dot(Normal, LightDirection);

			/// 노말라이즈 작업까지.
			vout.LightDirection[i] = normalize(vout.LightDirection[i]);
		}
	}

	vout.ViewDirection.x = dot(Tangent, ViewDirection);
	vout.ViewDirection.y = dot(BiTangent, ViewDirection);
	vout.ViewDirection.z = dot(Normal, ViewDirection);

	/// 노말라이즈 작업까지.
	vout.ViewDirection = normalize(vout.ViewDirection);

	vout.NormalW = Normal;
	vout.Bitangent = BiTangent;
	vout.Tangent = Tangent;

	return vout;
}
 
float4 PS(VertexOut pin, uniform int gLightCount, uniform bool gUseTexure) : SV_Target
{
    // Default to multiplicative identity.
    float4 texColor = float4(1, 1, 1, 1);
    if(gUseTexure)
	{
		// Sample texture.
		texColor = gDiffuseMap.Sample( samAnisotropic, pin.Tex );
	}
	 
	/// 확산광 ( N 도트 L )
	/// 반사광 ( R 도트 V ) ^ n
	/// 텍스쳐상의 노말 좌표.
	float3 TextureNormal = normalize((gNormalMap.Sample(samLinear, pin.Tex).rgb * 2.0f) - 1.0f);
	/// 탄젠트 스페이스로 보내진 ViewDirection (노말라이즈도 완료된 값)
	float3 ViewDirection = pin.ViewDirection;

	//
	// Lighting.
	//

	float4 litColor = texColor;
	if( gLightCount > 0  )
	{  
		// Start with a sum of zero. 
		float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
		float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
		float4 spec    = float4(0.0f, 0.0f, 0.0f, 0.0f);

		// Sum the light contribution from each light source.  
		[unroll]
		for(int i = 0; i < gLightCount; ++i)
		{
			/// 탄젠트스페이스로 보내진 Direction (노말라이즈도 완료된 값)
			float3 LightDirection = pin.LightDirection[i];
			/// diffuse값 뽑기.
			float NDotL = dot(TextureNormal, LightDirection);
			/// 반사벡터 만들기.
			float3 Reflection = normalize(((2.0f * TextureNormal) * (NDotL)) - LightDirection);
			float RDotV = max(0.0f, dot(Reflection, ViewDirection));

			ambient += gMaterial.Ambient * gDirLights[i].Ambient;
			diffuse += gMaterial.Diffuse * gDirLights[i].Diffuse * NDotL;
			spec    += gMaterial.Specular * gDirLights[i].Specular * RDotV;
		}

		// Modulate with late add.
		litColor = texColor*(ambient + diffuse) + spec;
	}

	// Common to take alpha from diffuse material and texture.
	litColor.a = gMaterial.Diffuse.a * texColor.a;

	if (gLightCount == 2)
	{
		litColor.r = pin.Tangent.x;
		litColor.g = pin.Tangent.y;
		litColor.b = pin.Tangent.z;
		litColor.a = 1.0f;
	}
	else if (gLightCount == 3)
	{
		litColor.r = pin.NormalW.x;
		litColor.g = pin.NormalW.y;
		litColor.b = pin.NormalW.z;
		litColor.a = 1.0f;
	}

    return litColor;
}

technique11 Light1
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS(1) ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS(1, false) ) );
    }
}

technique11 Light2
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS(2) ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS(2, false) ) );
    }
}

technique11 Light3
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS(3) ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS(3, false) ) );
    }
}

technique11 Light0Tex
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS(0) ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS(0, true) ) );
    }
}

technique11 Light1Tex
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS(1) ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS(1, true) ) );
    }
}

technique11 Light2Tex
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS(2) ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS(2, true) ) );
    }
}

technique11 Light3Tex
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS(3) ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS(3, true) ) );
    }
}
