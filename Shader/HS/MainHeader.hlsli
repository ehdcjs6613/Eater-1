//ī�޶� ���� ����
cbuffer CameraBuffer : register(b0)
{
    float4x4 viewproj;
    float4x4 ViewMatrix;
    float3 camPos;
};

//������Ʈ ���� ����
cbuffer ObjectBuffer : register(b1)
{
    float4x4    ObjworldMatrix;
    float4x4    TexMatrix;
    uint        Texture_Mask;
};


Texture2D MainTexture   : register(t0); //����
Texture2D NomalTexture  : register(t1); //�븻



SamplerState SampleType : register(s0)
{
    Filter = MIN_MAG_MIP_POINT; //�ؽ��ĸ� ���ø� �Ҷ� ����� ���� ���

    AddressU = BORDER; //0~1������ ����� u�ؽ��� ��ǥ���ذ��ϴ¹��
    AddressV = BORDER; //0~1������ ����� v�ؽ��� ��ǥ���ذ��ϴ¹��
    AddressW = BORDER; //0~1������ ����� w�ؽ��� ��ǥ���ذ��ϴ¹��


    BorderColor = float4(0.0f, 0.0f, 0.0f, 0.0f); //D3D1_TEX�ϰ�� ����� �׵θ� ���ּ� 0~1����
    ComparisonFunc = LESS_EQUAL; //���ø��� ����Ʈ�� ���� ���ɸ��� �����Ϳ� ���ϴ� �Լ�
    //LESS_EQUAL = �ҽ� �����Ͱ� ��� �����ͺ��� �۰ų� ������ ���
};