#pragma once

/// <summary>
/// �Ž�,�ؽ���,������,��� �׸������ؼ� �ʿ��Ѱ͵��� �ε�
/// 
/// 
/// �׽�Ʈ������ �����̲� ������ ������ �پ�����
/// </summary>



#include <string>
#include <map>


class FBXParser;
class FBXModel;
class DH3DEngine;
class LoadManager
{
public:
	LoadManager();
	~LoadManager();

	

	//�ʱ�ȭ �� ��� ����
	void Initialize();
public:
	///GET
	//�Ž� ��������
	FBXModel* GetMesh(std::string Name);
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
	//������ �°� �����͸� �����Ŵ
	void ChangeData(FBXModel* mData);




private:



	//���� ����ִ� ���
	std::string MeshPath;
	//�ؽ��İ� ����ִ� ���
	std::string TexturePath;
	//�ε��� ���� 
	//���ؽ� ����
	 
	//���͸���
	 
	//�ؽ���
	
	//�ִϸ��̼�
	//



	///����Ʈ
	std::map<std::string,FBXModel*> MeshList;

	//���̴� 
	//�ؽ���

private:
	FBXParser* EATER_Parser;
};
