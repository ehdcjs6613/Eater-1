cbuffer cbMeshObject
{
    float4x4 gMeshWorld : packoffset(c0);
    float4x4 gMeshWorldView : packoffset(c4);
    float4x4 gMeshWorldViewProj : packoffset(c8);
    float4x4 gMeshTexTransform : packoffset(c12);
    float4x4 gMeshShadowTransform : packoffset(c16);
};

struct VertexIn
{
    float3 PosL : POSITION;
    float2 Tex : TEXCOORD;
    float3 NormalL : NORMAL;
    float3 TangentL : TANGENT;
    float4 MaskColor : MASK;
};

struct VertexOut
{
    float4 PosH : SV_POSITION;
    float3 PosW : POSITIONW;
    float3 PosV : POSITIONV;
    float3 NormalW : NORMALW;
    float3 NormalV : NORMALV;
    float2 Tex : TEXCOORD;
    float3 ShadowPosH : POS_SHADOW;
    
    float3x3 TBNW : TANGENTW;
    float3x3 TBNV : TANGENTV;
    float4 MaskColor : MASK_COLOR;
};


VertexOut Terrain_VS(VertexIn vin)
{
    VertexOut vout;

    // ���� ���� ��ȯ
    vout.PosH = mul(gMeshWorldViewProj, float4(vin.PosL, 1.0f));
    
	// ���� ���� ��ȯ
    vout.PosW = mul(gMeshWorld, float4(vin.PosL, 1.0f)).xyz;

    // �� ���� ��ȯ
    vout.PosV = mul(gMeshWorldView, float4(vin.PosL, 1.0f)).xyz;
    
    vout.NormalW = mul((float3x3) gMeshWorld, vin.NormalL);
    vout.NormalW = normalize(vout.NormalW);
	
    vout.NormalV = mul((float3x3) gMeshWorldView, vin.NormalL);
    vout.NormalV = normalize(vout.NormalV);
    
	// Output vertex attributes for interpolation across triangle.
    vout.Tex = mul(gMeshTexTransform, float4(vin.Tex, 0.0f, 1.0f)).xy;
    
    float4 Shadow = mul(gMeshShadowTransform, float4(vin.PosL, 1.0f));
    vout.ShadowPosH = Shadow.xyz / Shadow.w;
    
    // Vertex Shader ���� TBN�� ��������..
	// Pixel Shader���� ������ �ּ������� �ؾ��ϱ� ����..
    float3 Tangent = float3(0.0f, 0.0f, 0.0f);
    float3 N = float3(0.0f, 0.0f, 0.0f);
    float3 T = float3(0.0f, 0.0f, 0.0f);
    float3 B = float3(0.0f, 0.0f, 0.0f);
    
    Tangent = mul((float3x3) gMeshWorld, vin.TangentL);
    N = vout.NormalW;
    T = normalize(Tangent - dot(Tangent, N) * N);
    B = cross(N, T);
    
    vout.TBNW = float3x3(T, B, N);
    
    Tangent = mul((float3x3) gMeshWorldView, vin.TangentL);
    N = vout.NormalV;
    T = normalize(Tangent - dot(Tangent, N) * N);
    B = cross(N, T);

    vout.TBNV = float3x3(T, B, N);
    vout.MaskColor = vin.MaskColor;
    
    return vout;
}