//ī�޶� ���� ����
cbuffer CameraBuffer : register(b0)
{
    float4x4 view;
    float4x4 proj;
};

//������Ʈ ���� ����
cbuffer ObjectBuffer : register(b1)
{
    float4x4    world;
    float4x4    TexMatrix;
};

//��Ű�� ���� ����
cbuffer SkinningBuffer : register(b2)
{
    float4x4 Skinning_world;
    float4x4 Skinning_Tex;
    float4x4 BoneOffset[96];
};

Texture2D MainTexture   : register(t0); //����
//Texture2D NomalTexture  : register(t1); //�븻

SamplerState SampleType : register(s0); //���÷� Ÿ��
