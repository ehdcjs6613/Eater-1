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
#include "SimpleMath.h"

namespace ParserData
{
	struct Model;
	class Mesh;
	class OneAnimation;
}

class ModelAnimationData;
class LoadMeshData;
class ModelData;
class ModelParser;
class FBXParser;
class FBXModel;
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
	static TextureBuffer* GetTexture(std::string Name);
	//�ִϸ��̼� ��������
	static ModelAnimationData* GetAnimation(std::string Name);
	
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
	//���� ������ Ÿ���ʰ� ž������Ʈ�鸸 �о�´�
	LoadMeshData* CreateMeshObjeect(ParserData::Mesh* mesh);
	LoadMeshData* CreateBoneObjeect(ModelData* SaveData);

	//�ִϸ��̼��� �ε���
	void LoadAnimation(ModelData* SaveMesh,ParserData::Model* MeshData,std::string Name);
	//�ε��� �ִϸ��̼���Ű�� ������ Ű���־���
	void CreateAnimationKeyFrame(std::vector<ParserData::OneAnimation*>* Anime, int InputKeyCount);
	//�Ľ��ѵ����Ϳ��� ���� �������������͵��� �״�� ������
	void SetData(LoadMeshData* MeshData, ParserData::Mesh* LoadData);
private:
	///���� ����ִ� ���
	std::string MeshPath;
	///�ؽ��İ� ����ִ� ���
	std::string TexturePath;
	///����Ʈ
	static std::map<std::string, ModelData*>			ModelList;
	static std::map<std::string, TextureBuffer*>		TextureList;
	static std::map<std::string, ModelAnimationData*>	AnimationList;
	//��Ȳ�� �ļ�
	ModelParser* EaterParser;
	//�������� �׷��� ����
	GraphicEngineManager* GEngine;
};
