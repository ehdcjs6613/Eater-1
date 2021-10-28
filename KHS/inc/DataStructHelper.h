#pragma once

/*
	2021/08/10 CDH - �ֵ���
	<�۾�����>
		SharedData�� ���� ������ ����ü���� �ʿ��Ѱ� �ִٸ� �̸� �����ص���.
	<�ֿ� ����>
		1. Light ���� ����ü ����
*/

#ifdef _DEBUG
#pragma comment( lib, "DirectXTKd.lib" )
#else
#pragma comment( lib, "DirectXTK.lib" )
#endif

/// �켱 SimpleMath�� ��������� ������ ������ ���.. ( DX�� ���������� ���� �� ������ ���� ������ ������ �����ؼ� ����� �ص� �� )
#include <Windows.h>
#include <vector>
#include <map>
#include <atlstr.h>
#include "SimpleMath.h"

namespace VertexStruct
{
	struct PosNormal
	{
		DirectX::SimpleMath::Vector3 Pos;
		DirectX::SimpleMath::Vector3 Normal;
	};
}


namespace DHRENDER
{
	// ���̴��� ��� �����ΰ�?
	enum class SHADER
	{
		Basic_Shader,
	};

	struct TexturePathAndSRV
	{
		TexturePathAndSRV() {}
		TexturePathAndSRV(ATL::CString _Texture_Path, void* _Texture_SRV)
		{
			Texture_Path = _Texture_Path;
			Texture_SRV = _Texture_SRV;
		}

		ATL::CString Texture_Path;
		void* Texture_SRV;
	};

	// �̹����� ������, �����̼�, ������, ���� ��
	struct ImageTRSA
	{
		ImageTRSA() {}
		ImageTRSA(ATL::CString _Image_File_Name)
		{
			Image_File_Name = _Image_File_Name;
		}
		ImageTRSA(ATL::CString _Image_File_Name , DirectX::SimpleMath::Vector2 _Position,
			DirectX::SimpleMath::Vector2 _Scale, float _Rotate_Angle, float _Alpha)
		{
			Image_File_Name = _Image_File_Name;
			Position = _Position;
			Scale = _Scale;
			Rotate_Angle = _Rotate_Angle;
			Alpha = _Alpha;
		}

		ATL::CString Image_File_Name;
		DirectX::SimpleMath::Vector2 Position = DirectX::SimpleMath::Vector2(0,0);
		DirectX::SimpleMath::Vector2 Scale = DirectX::SimpleMath::Vector2(1, 1);
		float Rotate_Angle = 0.f;
		float Alpha = 1.f;
	};

	// �ؽ�Ʈ�� ������, ����, ������, ���� ��
	struct TextTCSA
	{
		TextTCSA() {}
		TextTCSA(ATL::CString _Text_File_Name, DirectX::SimpleMath::Vector2 _Position,
			float _Size, DirectX::SimpleMath::Vector3 _Color, float _Alpha)
		{
			Text_File_Name = _Text_File_Name;
			Position = _Position;
			Size = _Size;
			Color = _Color;
			Alpha = _Alpha;
		}

		ATL::CString Text_File_Name = "";
		DirectX::SimpleMath::Vector2 Position = DirectX::SimpleMath::Vector2(0, 0);
		DirectX::SimpleMath::Vector3 Color = DirectX::SimpleMath::Vector3(0, 0, 0);
		float Size = 20.f;
		float Alpha = 1.f;
	};
}

/// Light ���� ���ǵ�.

struct DirectionalLight
{
	DirectionalLight() { ZeroMemory(this, sizeof(this)); }

	DirectX::SimpleMath::Vector4 Ambient;
	DirectX::SimpleMath::Vector4 Diffuse;
	DirectX::SimpleMath::Vector4 Specular;
	DirectX::SimpleMath::Vector3 Direction;

	// ���ϴ� ��� Vector3 �ڿ� �ϳ��� float�� �߰��Ͽ� �迭�� ������ �� �ֵ��� pad�� �����ص�.
	float Pad;
};

struct PointLight
{
	PointLight() { ZeroMemory(this, sizeof(this)); }

	DirectX::SimpleMath::Vector4 Ambient;
	DirectX::SimpleMath::Vector4 Diffuse;
	DirectX::SimpleMath::Vector4 Specular;

	// 4D vector�� �е��� : (Position, Range)
	DirectX::SimpleMath::Vector3* Position;
	float Range;

	// 4D vector�� �е��� : (A0, A1, A2, Pad)
	DirectX::SimpleMath::Vector3 Att;
	float Pad;
};

struct SpotLight
{
	SpotLight() { ZeroMemory(this, sizeof(this)); }

	DirectX::SimpleMath::Vector4 Ambient;
	DirectX::SimpleMath::Vector4 Diffuse;
	DirectX::SimpleMath::Vector4 Specular;

	// 4D vector�� �е��� : (Position, Range)
	DirectX::SimpleMath::Vector3* Position;
	float Range;

	// 4D vector�� �е��� : (Direction, Spot)
	DirectX::SimpleMath::Vector3 Direction;
	float Spot;

	// 4D vector�� �е��� : (A0, A1, A2, Pad)
	DirectX::SimpleMath::Vector3 Att;
	float Pad;
};

/// Material ���� ���ǵ�..

struct Material
{
	/// �⺻ ���׸��� �� ����..
	DirectX::SimpleMath::Vector4 Ambient = DirectX::SimpleMath::Vector4(0.8f, 0.8f, 0.8f, 1.0f);
	DirectX::SimpleMath::Vector4 Diffuse = DirectX::SimpleMath::Vector4(0.8f, 0.8f, 0.8f, 1.0f);
	DirectX::SimpleMath::Vector4 Specular = DirectX::SimpleMath::Vector4(0.8f, 0.8f, 0.8f, 16.0f); // w = �ݻ籤�� ����.
	DirectX::SimpleMath::Vector4 Reflect;
};


/// �ļ��� ����ü..
namespace DHParser
{
	// �ε��� ���ۿ� ����ü
	struct Indices
	{
		uint16_t Index[3];
	};

	// ���ؽ� ���ۿ� ����ü.
	struct Vertex
	{
		DirectX::SimpleMath::Vector3 Pos;
		DirectX::SimpleMath::Vector3 Normal;
		DirectX::SimpleMath::Vector2 Tex;
		DirectX::SimpleMath::Vector3 BiNormal;
		DirectX::SimpleMath::Vector3 Tangent;

		/// map�� ���� ����ȭ �۾��� ���� ���۷����͸� ������.
		bool operator<(const Vertex& rhs)const
		{
			if (Normal != rhs.Normal)
			{
				// �븻�� X�� ��
				if (Normal.x != rhs.Normal.x)
				{
					return Normal.x > rhs.Normal.x;
				}

				// �븻�� Y�� �� ( X�� ���ٸ�.. )
				if (Normal.y != rhs.Normal.y)
				{
					return Normal.y > rhs.Normal.y;
				}

				// �븻�� Z���� ���� ����� ���� ( X,Y�� ���ٸ�.. )
				return Normal.z > rhs.Normal.z;
			}

			if (Pos != rhs.Pos)
			{
				// �븻�� X�� ��
				if (Pos.x != rhs.Pos.x)
				{
					return Pos.x > rhs.Pos.x;
				}

				// �븻�� Y�� �� ( X�� ���ٸ�.. )
				if (Pos.y != rhs.Pos.y)
				{
					return Pos.y > rhs.Pos.y;
				}

				// �븻�� Z���� ���� ����� ���� ( X,Y�� ���ٸ�.. )
				return Pos.z > rhs.Pos.z;
			}

			if (Tex != rhs.Tex)
			{
				// �븻�� X�� ��
				if (Tex.x != rhs.Tex.x)
				{
					return Tex.x > rhs.Tex.x;
				}

				return Tex.y > rhs.Tex.y;
			}
			
			/// ������ false �����Ѵ�.
			return false;
		}
	};

	// �޽� ����ü ����.
	struct Mesh
	{
		// ���ۼ��ÿ� �ʿ��� �����͵�. �ʱ⿡�� ������ �ȵǾ��ְ� ������ �ʹ� Initialize�� ��û�ϸ鼭 ä������.
		// Index�� Vertex�� ����ִ� �ּ� ������.
		//void* Vertices_Ptr = nullptr;
		//void* Indices_Ptr = nullptr;

		// DX11 ���� DX12 ���� ... �� ���� � ���·��� Buffer�� ���� �𸣱� ������ void*�� ���� �س���. (c++17 �� std::any ���ٴ� �̰Դ� ������������?)
		void* Vertex_Buffer = nullptr;
		void* Index_Buffer = nullptr;

		/// �� �޽ÿ� ���� ��� ���� �̸�.
		ATL::CString Node_Name = "";
		ATL::CString Parent_Name = "";
		ATL::CString Child_Name = "";

		/// ���͸��� ����.
		Material Mesh_Material;
		/// �ؽ��� ��ȣ (Ű��)
		int Texture_Key = -1;

		/// Vertex , Tri Count
		UINT Vcount;
		UINT Tcount;

		/// ���� ���ؽ� �� �ε�������
		std::vector<Vertex> Optimize_Vertex;
		std::vector<UINT> Optimize_Index;

		/// �� �޽��� ���� / ���� TM
		DirectX::SimpleMath::Matrix Local_TM;
		DirectX::SimpleMath::Matrix World_TM;
	};
}