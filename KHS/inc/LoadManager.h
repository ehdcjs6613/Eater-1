#pragma once

/// <summary>
/// �Ž�,�ؽ���,������,��� �׸������ؼ� �ʿ��Ѱ͵��� �ε�
/// 
/// 
/// �׽�Ʈ������ �����̲� ������ ������ �پ�����
/// </summary>



#include <string>
#include <map>
#include "ParserData.h"
#include "SharedData.h"

struct ParserData::Model;
struct Model;
class LoadData;
class ModelParser;
class FBXParser;
class FBXModel;
class DH3DEngine;
class GraphicEngine;

class LoadManager
{
public:
	LoadManager();
	~LoadManager();

	

	//�ʱ�ȭ �� ��� ����
	void Initialize(GraphicEngine* Graphic);
	//�׽�Ʈ��
	void Initialize(DH3DEngine* Graphic);
public:
	///GET
	//�Ž� ��������
	static LoadData* GetMesh(std::string Name);
	//�ؽ��� ��������
	void GetTexture(std::string Name);

	///Load
	//�� �ε�(��ũ�� �̸�,���� �̸�,������ ����,�ִϸ��̼� ����)
	void LoadMesh(std::string Name, bool Scale = true,bool LoadAnime = false);
	//������ �ε�
	void LoadPrefap(std::string Name);

	///���
	//�Ž� ��� ����
	void LoadMeshPath(std::string mPath);
	//�ؽ��� ���
	void LoadTexturePath(std::string mPath);

	///Delete
	//����Ʈ���� �Ž������� ����(�Ž��� �ʹ����Ƽ� �޸𸮰� �����Ҷ�)
	void DeleteMesh(std::string mMeshName);
	//��� �Ž������� ����
	void DeleteMeshAll();
	
private:

	//���� ����ִ� ���
	std::string MeshPath;
	//�ؽ��İ� ����ִ� ���
	std::string TexturePath;
	
	///����Ʈ
	static std::map<std::string,LoadData*> MeshList;
private:
	//��Ȳ�� �ļ�
	ModelParser*	EaterParser;
	//�������� �׷��� ����
	GraphicEngine*	GEngine;


	///������ʹ� �����̲� �׽�Ʈ��
	DH3DEngine*			DHEngine;
	OneFrameData*		pTest_OFD;
	SharedRenderData*	pTest_SRD;
	DHParser::Mesh*		pTest_Mesh;

	void Test_DHData(ParserData::Model* mModel, std::string Name);
};
