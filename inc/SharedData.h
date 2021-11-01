#pragma once

/*
	2021/08/10 CDH - 최동혁
	<작업내용>
		Scene 에서 엔진으로 그리기 위해서 필요한 정보들만 담아둔 구조체 생성.
	<주요 동작>	
		해당 구조체를 통해 Render() 를 할때 데이터를 전달하여, 이를 기반으로 해서 엔진에서 그린다.
			=> VB , IB, Shader 등의 사용정보들이 들어갈 예정.
*/

#include "DataStructHelper.h"

/// 한 프레임에 여러번 쓰일수 있는 구조체 ( 메시 마다 하나씩 필요 )
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
	ATL::CString Play_Text_String;
	bool Is_Text = false;	// 텍스트가 존재하는 UI인가?
	// 이미지의 속성값들.
	std::map<ATL::CString, DHRENDER::ImageTRSA*> Img_List;
	// 이미지 로드시 필요한 변수.
	std::map<ATL::CString, ATL::CString> Img_Path_List;
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