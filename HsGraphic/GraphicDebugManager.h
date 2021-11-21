#pragma once
#include "InputLayout.h"
#include <vector>
#include <DirectXMath.h>
#include <string>
#include <map>
#include "d3d11.h"
using namespace DirectX;

/// <summary>
/// ������ ������ �����ϱ����� ������� �Ѵ�
/// </summary>

class BufferData;
class GraphicDebugManager
{
public:
	GraphicDebugManager();
	~GraphicDebugManager();

	//�ʱ�ȭ
	void Initialize(ID3D11Device* Device, ID3D11DeviceContext* mContext);

public:
	//2D���������� ����� ���ؽ� �����Ѵ�
	void Create_2D_Y_Circle_Buffers(XMFLOAT3 _Centor, float Radius, XMFLOAT3 Color = { 1,0,0 });
	void Create_2D_X_Circle_Buffers(XMFLOAT3 _Centor, float Radius, XMFLOAT3 Color = { 1,0,0 });
	void Create_2D_Z_Circle_Buffers(XMFLOAT3 _Centor, float Radius, XMFLOAT3 Color = { 1,0,0 });

	//2D�簢���������� �������ý� ����
	void Create_2D_X_Rect_Buffer(XMFLOAT3 _Centor, XMFLOAT2 _Extents, XMFLOAT3 Color = { 1,0,0});
	void Create_2D_Y_Rect_Buffer(XMFLOAT3 _Centor, XMFLOAT2 _Extents, XMFLOAT3 Color = { 1,0,0});
	void Create_2D_Z_Rect_Buffer(XMFLOAT3 _Centor, XMFLOAT2 _Extents, XMFLOAT3 Color = { 1,0,0});

	//3D �ڽ� �������� ���۸� �����Ѵ�
	void Create_3D_Box_Buffers(XMFLOAT3 _Centor, XMFLOAT3 _Extents, XMFLOAT3 Color = { 1,0,0});

	//3D ���� �������� ���۸� �����Ѵ�
	void Create_3D_Circle_Buffers(XMFLOAT3 _Centor, float Radius, XMFLOAT3 Color = { 1,0,0});

	//���� �������� ����� ���ý��� ������
	void Create_2D_Line_Buffers(XMFLOAT3 start, XMFLOAT3 end, XMFLOAT3 Color = { 1,0,0});

	//���۸� �����Ѵ�
	BufferData* CreateBuffer(std::string BufferName);

	//�׸�����۸� �����´�
	BufferData* GetGridBuffer();
	//�����۸� �����´�
	BufferData* GetBoneBuffer();
private:
	//�׸��带 �׸���
	void Create_Grid(int CountX,int CountY);
	void Create_Bone();
private:
	ID3D11Device*		 m_Device;				//����̽�
	ID3D11DeviceContext* m_DeviceContext;		//����̽� ���ؽ�Ʈ

	std::vector<Debug32>	vertices;
	std::vector<UINT>		indices;

	int vcount;
	int icount;

	BufferData* GridBuffer;
	BufferData* BoneBuffer;

	std::map<std::string, BufferData*> BufferList;
};