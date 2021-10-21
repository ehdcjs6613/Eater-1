#pragma once

/// <summary>
/// �Ž�,�ؽ���,��� �׸������ؼ� �ʿ��Ѱ͵��� �ε�
/// </summary>




#include <string>
class FBXParser;
class LoadManager
{
public:
	LoadManager();
	~LoadManager();

	//�ʱ�ȭ �� ��� ����
	void init();
	//�� �ε�
	void LoadMesh(std::string Name,bool LoadAnime);
	//������ �ε�
	void LoadPrefap(std::string Name);
	//�Ž� ��� ����
	void LoadMeshPath(std::string mPath);

private:
	//���� ����ִ� ���
	std::string MeshPath;
	//�ؽ��İ� ����ִ� ���
	std::string TexturePath;




	FBXParser* EATER_Parser;
};