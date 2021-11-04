#pragma once


/// DX11 링킹
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")

#ifdef _DEBUG
//#pragma comment( lib, "DirectXTKd.lib" )
//#pragma comment( lib, "Effects11d.lib" )
#else
#pragma comment( lib, "DirectXTK.lib" )
#pragma comment( lib, "Effects11.lib" )
#endif




/// DX11 인클루드.
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3dcommon.h>
#include <dxgi.h>

#include <DirectXMath.h>
#include <DirectXColors.h>
#include <DirectXPackedVector.h>

//스마트포인터 인클르드
#include <wrl.h>
#include <wrl/client.h>
#include <memory>

//c++ iostream 및 자료구조 헤더
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>


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
		TexturePathAndSRV(std::wstring _Texture_Path, void* _Texture_SRV)
		{
			Texture_Path = _Texture_Path;
			Texture_SRV = _Texture_SRV;
		}

		std::wstring Texture_Path;
		void* Texture_SRV;
	};

	// 이미지의 포지션, 로테이션, 스케일, 알파 값
	struct ImageTRSA
	{
		ImageTRSA() {}
		ImageTRSA(std::string _Image_File_Name)
		{
			Image_File_Name = _Image_File_Name;
		}
		ImageTRSA(std::string _Image_File_Name, DirectX::SimpleMath::Vector2 _Position,
			DirectX::SimpleMath::Vector2 _Scale, float _Rotate_Angle, float _Alpha)
		{
			Image_File_Name = _Image_File_Name;
			Position = _Position;
			Scale = _Scale;
			Rotate_Angle = _Rotate_Angle;
			Alpha = _Alpha;
		}

		std::string Image_File_Name;
		DirectX::SimpleMath::Vector2 Position = DirectX::SimpleMath::Vector2(0, 0);
		DirectX::SimpleMath::Vector2 Scale = DirectX::SimpleMath::Vector2(1, 1);
		float Rotate_Angle = 0.f;
		float Alpha = 1.f;
	};

	// 텍스트의 포지션, 색깔, 스케일, 알파 값
	struct TextTCSA
	{
		TextTCSA() {}
		TextTCSA(std::string _Text_File_Name, DirectX::SimpleMath::Vector2 _Position,
			float _Size, DirectX::SimpleMath::Vector3 _Color, float _Alpha)
		{
			Text_File_Name = _Text_File_Name;
			Position = _Position;
			Size = _Size;
			Color = _Color;
			Alpha = _Alpha;
		}

		std::string Text_File_Name = "";
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
		std::string Node_Name = "";
		std::string Parent_Name = "";
		std::string Child_Name = "";

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

struct SharedRenderData
{
	// 쉐이더 (Layout / Vertex Struct) /  Tech 정보
	DHRENDER::SHADER m_Shader = DHRENDER::SHADER::Basic_Shader;
	int Tech_Number = 0;

	/// 한 모델에 대한 텍스쳐 경로.
	std::map<int, DHRENDER::TexturePathAndSRV*> Ambient_Texture;
	std::map<int, DHRENDER::TexturePathAndSRV*> Emissive_Texture;
	std::map<int, DHRENDER::TexturePathAndSRV*> Diffuse_Texture;
	std::map<int, DHRENDER::TexturePathAndSRV*> Specular_Texture;
	std::map<int, DHRENDER::TexturePathAndSRV*> NormalMap_Texture;

	std::vector<DHParser::Mesh>* Render_Mesh_List = nullptr;

	// Scale / Rotate / Trans 메트릭스.
	DirectX::SimpleMath::Matrix Trans_Matrix;
	DirectX::SimpleMath::Matrix Rot_Matrix;
	DirectX::SimpleMath::Matrix Scale_Matrix;
	DirectX::SimpleMath::Matrix SRT_Matrix;

	// 텍스쳐가 셋팅 되었는지 여부.
	bool Texture_SetUp = false;

};

/// 2D 데이터를 그릴 때 필요한 데이터.
struct Shared2DRenderData
{
	// 텍스트 재생 (현재는 한 UI에 하나의 텍스트만 띄울수 있음)
	DHRENDER::TextTCSA Play_Text_Att;
	std::wstring Play_Text_String;
	bool Is_Text = false;	// 텍스트가 존재하는 UI인가?
	// 이미지의 속성값들.
	std::map<std::wstring, DHRENDER::ImageTRSA*> Img_List;
	// 이미지 로드시 필요한 변수.
	std::map<std::wstring, std::wstring> Img_Path_List;
	bool Is_Img_Load = false;
	// 이미지들을 전체적으로 묶어서 관리할 UI 속성
	DHRENDER::ImageTRSA UI_TRSA;
};

/// 한 프레임에 한번 필요한 데이터 ( 메시마다 필요하지 않음 )
struct OneFrameData
{
	std::vector<DirectionalLight> DirLight_List;
	std::vector<PointLight> PointLight_List;
	std::vector<SpotLight> SpotLight_List;

	DirectX::SimpleMath::Matrix View_Matrix;
	DirectX::SimpleMath::Matrix Projection_Matrix;

	DirectX::SimpleMath::Vector3 World_Eye_Position;	// 월드상의 시선 ( 시선벡터 구하기용 )
	// 디버깅용
	DirectX::SimpleMath::Vector3 Main_Position;	// 월드상의 시선 ( 시선벡터 구하기용 )
};

