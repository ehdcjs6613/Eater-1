#pragma once

/*
	2021/08/10 CDH - �ֵ���
	<�۾�����>
		Scene ���� �������� �׸��� ���ؼ� �ʿ��� �����鸸 ��Ƶ� ����ü ����.
	<�ֿ� ����>	
		�ش� ����ü�� ���� Render() �� �Ҷ� �����͸� �����Ͽ�, �̸� ������� �ؼ� �������� �׸���.
			=> VB , IB, Shader ���� ����������� �� ����.
*/

#include "DataStructHelper.h"

/// �� �����ӿ� ������ ���ϼ� �ִ� ����ü ( �޽� ���� �ϳ��� �ʿ� )
struct SharedRenderData
{
	// ���̴� (Layout / Vertex Struct) /  Tech ����
	DHRENDER::SHADER m_Shader = DHRENDER::SHADER::Basic_Shader;
	int Tech_Number = 0;

	/// �� �𵨿� ���� �ؽ��� ���.
	std::map<int, DHRENDER::TexturePathAndSRV*> Ambient_Texture;
	std::map<int, DHRENDER::TexturePathAndSRV*> Emissive_Texture;
	std::map<int, DHRENDER::TexturePathAndSRV*> Diffuse_Texture;
	std::map<int, DHRENDER::TexturePathAndSRV*> Specular_Texture;
	std::map<int, DHRENDER::TexturePathAndSRV*> NormalMap_Texture;

	std::vector<DHParser::Mesh>* Render_Mesh_List = nullptr;

	// Scale / Rotate / Trans ��Ʈ����.
	DirectX::SimpleMath::Matrix Trans_Matrix;
	DirectX::SimpleMath::Matrix Rot_Matrix;
	DirectX::SimpleMath::Matrix Scale_Matrix;
	DirectX::SimpleMath::Matrix SRT_Matrix;

	// �ؽ��İ� ���� �Ǿ����� ����.
	bool Texture_SetUp = false;
	
};

/// 2D �����͸� �׸� �� �ʿ��� ������.
struct Shared2DRenderData
{
	// �ؽ�Ʈ ��� (����� �� UI�� �ϳ��� �ؽ�Ʈ�� ���� ����)
	DHRENDER::TextTCSA Play_Text_Att;
	ATL::CString Play_Text_String;
	bool Is_Text = false;	// �ؽ�Ʈ�� �����ϴ� UI�ΰ�?
	// �̹����� �Ӽ�����.
	std::map<ATL::CString, DHRENDER::ImageTRSA*> Img_List;
	// �̹��� �ε�� �ʿ��� ����.
	std::map<ATL::CString, ATL::CString> Img_Path_List;
	bool Is_Img_Load = false;
	// �̹������� ��ü������ ��� ������ UI �Ӽ�
	DHRENDER::ImageTRSA UI_TRSA;
};

/// �� �����ӿ� �ѹ� �ʿ��� ������ ( �޽ø��� �ʿ����� ���� )
struct OneFrameData
{
	std::vector<DirectionalLight> DirLight_List;
	std::vector<PointLight> PointLight_List;
	std::vector<SpotLight> SpotLight_List;

	DirectX::SimpleMath::Matrix View_Matrix;
	DirectX::SimpleMath::Matrix Projection_Matrix;

	DirectX::SimpleMath::Vector3 World_Eye_Position;	// ������� �ü� ( �ü����� ���ϱ�� )
	// ������
	DirectX::SimpleMath::Vector3 Main_Position;	// ������� �ü� ( �ü����� ���ϱ�� )
};