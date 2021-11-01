#pragma once

/*
	2021/08/10 CDH - 최동혁
	<작업내용>
		SharedData에 들어가는 데이터 구조체들중 필요한게 있다면 미리 정의해두자.
	<주요 동작>
		1. Light 관련 구조체 정의
*/

#ifdef _DEBUG
#pragma comment( lib, "DirectXTKd.lib" )
#else
#pragma comment( lib, "DirectXTK.lib" )
#endif

/// 우선 SimpleMath를 기반으로한 데이터 구조를 사용.. ( DX에 종속적으로 보일 수 있으나 추후 데이터 구조를 정의해서 사용을 해도 됨 )
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
	// 쉐이더를 어떤걸 쓸것인가?
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

	// 이미지의 포지션, 로테이션, 스케일, 알파 값
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

	// 텍스트의 포지션, 색깔, 스케일, 알파 값
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

/// Light 관련 정의들.

struct DirectionalLight
{
	DirectionalLight() { ZeroMemory(this, sizeof(this)); }

	DirectX::SimpleMath::Vector4 Ambient;
	DirectX::SimpleMath::Vector4 Diffuse;
	DirectX::SimpleMath::Vector4 Specular;
	DirectX::SimpleMath::Vector3 Direction;

	// 원하는 경우 Vector3 뒤에 하나의 float를 추가하여 배열을 설정할 수 있도록 pad를 설정해둠.
	float Pad;
};

struct PointLight
{
	PointLight() { ZeroMemory(this, sizeof(this)); }

	DirectX::SimpleMath::Vector4 Ambient;
	DirectX::SimpleMath::Vector4 Diffuse;
	DirectX::SimpleMath::Vector4 Specular;

	// 4D vector로 패딩시 : (Position, Range)
	DirectX::SimpleMath::Vector3* Position;
	float Range;

	// 4D vector로 패딩시 : (A0, A1, A2, Pad)
	DirectX::SimpleMath::Vector3 Att;
	float Pad;
};

struct SpotLight
{
	SpotLight() { ZeroMemory(this, sizeof(this)); }

	DirectX::SimpleMath::Vector4 Ambient;
	DirectX::SimpleMath::Vector4 Diffuse;
	DirectX::SimpleMath::Vector4 Specular;

	// 4D vector로 패딩시 : (Position, Range)
	DirectX::SimpleMath::Vector3* Position;
	float Range;

	// 4D vector로 패딩시 : (Direction, Spot)
	DirectX::SimpleMath::Vector3 Direction;
	float Spot;

	// 4D vector로 패딩시 : (A0, A1, A2, Pad)
	DirectX::SimpleMath::Vector3 Att;
	float Pad;
};

/// Material 관련 정의들..

struct Material
{
	/// 기본 메테리얼 값 설정..
	DirectX::SimpleMath::Vector4 Ambient = DirectX::SimpleMath::Vector4(0.8f, 0.8f, 0.8f, 1.0f);
	DirectX::SimpleMath::Vector4 Diffuse = DirectX::SimpleMath::Vector4(0.8f, 0.8f, 0.8f, 1.0f);
	DirectX::SimpleMath::Vector4 Specular = DirectX::SimpleMath::Vector4(0.8f, 0.8f, 0.8f, 16.0f); // w = 반사광의 세기.
	DirectX::SimpleMath::Vector4 Reflect;
};


/// 파서용 구조체..
namespace DHParser
{
	// 인덱스 버퍼용 구조체
	struct Indices
	{
		uint16_t Index[3];
	};

	// 버텍스 버퍼용 구조체.
	struct Vertex
	{
		DirectX::SimpleMath::Vector3 Pos;
		DirectX::SimpleMath::Vector3 Normal;
		DirectX::SimpleMath::Vector2 Tex;
		DirectX::SimpleMath::Vector3 BiNormal;
		DirectX::SimpleMath::Vector3 Tangent;

		/// map을 통한 최적화 작업을 위해 오퍼레이터를 재정의.
		bool operator<(const Vertex& rhs)const
		{
			if (Normal != rhs.Normal)
			{
				// 노말의 X값 비교
				if (Normal.x != rhs.Normal.x)
				{
					return Normal.x > rhs.Normal.x;
				}

				// 노말의 Y값 비교 ( X가 같다면.. )
				if (Normal.y != rhs.Normal.y)
				{
					return Normal.y > rhs.Normal.y;
				}

				// 노말의 Z값을 비교한 결과를 리턴 ( X,Y가 같다면.. )
				return Normal.z > rhs.Normal.z;
			}

			if (Pos != rhs.Pos)
			{
				// 노말의 X값 비교
				if (Pos.x != rhs.Pos.x)
				{
					return Pos.x > rhs.Pos.x;
				}

				// 노말의 Y값 비교 ( X가 같다면.. )
				if (Pos.y != rhs.Pos.y)
				{
					return Pos.y > rhs.Pos.y;
				}

				// 노말의 Z값을 비교한 결과를 리턴 ( X,Y가 같다면.. )
				return Pos.z > rhs.Pos.z;
			}

			if (Tex != rhs.Tex)
			{
				// 노말의 X값 비교
				if (Tex.x != rhs.Tex.x)
				{
					return Tex.x > rhs.Tex.x;
				}

				return Tex.y > rhs.Tex.y;
			}
			
			/// 같을땐 false 여야한다.
			return false;
		}
	};

	// 메시 구조체 정의.
	struct Mesh
	{
		// 버퍼세팅에 필요한 데이터들. 초기에는 세팅이 안되어있고 엔진에 초반 Initialize를 요청하면서 채워진다.
		// Index와 Vertex가 들어있는 주소 시작지.
		//void* Vertices_Ptr = nullptr;
		//void* Indices_Ptr = nullptr;

		// DX11 인지 DX12 인지 ... 과 같이 어떤 형태로의 Buffer를 쓸지 모르기 때문에 void*로 선언 해놨다. (c++17 의 std::any 보다는 이게더 빠르지않을까?)
		void* Vertex_Buffer = nullptr;
		void* Index_Buffer = nullptr;

		/// 한 메시에 대한 노드 관계 이름.
		ATL::CString Node_Name = "";
		ATL::CString Parent_Name = "";
		ATL::CString Child_Name = "";

		/// 메터리얼 정보.
		Material Mesh_Material;
		/// 텍스쳐 번호 (키값)
		int Texture_Key = -1;

		/// Vertex , Tri Count
		UINT Vcount;
		UINT Tcount;

		/// 최종 버텍스 및 인덱스정보
		std::vector<Vertex> Optimize_Vertex;
		std::vector<UINT> Optimize_Index;

		/// 이 메시의 로컬 / 월드 TM
		DirectX::SimpleMath::Matrix Local_TM;
		DirectX::SimpleMath::Matrix World_TM;
	};
}