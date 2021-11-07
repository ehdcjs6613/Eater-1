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
namespace ParserData
{
	struct Model;
}

class LoadMeshData;
class ModelData;
class ModelParser;
class FBXParser;
class FBXModel;
class GraphicEngine;
class TextureBuffer;
class GraphicEngineManager;

class LoadManager
{
public:
	LoadManager();
	~LoadManager();

	

	//�ʱ�ȭ �� ��� ����
	void Initialize(GraphicEngineManager* Graphic);
public:
	///GET
	//�Ž� ��������
	static ModelData* GetMesh(std::string Name);
	//�ؽ��� ��������
	TextureBuffer* GetTexture(std::string Name);

	///Load
	//�� �ε�(��ũ�� �̸�,���� �̸�,������ ����,�ִϸ��̼� ����)
	void LoadMesh(std::string Name, bool Scale = true,bool LoadAnime = false);
	void LoadTexture(std::string Name);
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
	//�Ž� �����͸� ������ ����ü�� �����
	LoadMeshData* CreateMesh(ParserData::Mesh* mesh);

	//���� ����ִ� ���
	std::string MeshPath;
	//�ؽ��İ� ����ִ� ���
	std::string TexturePath;
	
	///����Ʈ
	static std::map<std::string, ModelData*>		ModelList;
	static std::map<std::string, TextureBuffer*>	TextureList;
private:
	//��Ȳ�� �ļ�
	ModelParser* EaterParser;
	//�������� �׷��� ����
	GraphicEngineManager* GEngine;
};
