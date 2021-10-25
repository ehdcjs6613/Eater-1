#include "LoadManager.h"
#include "DebugManager.h"
#include "DH3DEngine.h"
#include "KHParser.h"

LoadManager::LoadManager()
{
	EATER_Parser = nullptr;
}

LoadManager::~LoadManager()
{

}

void LoadManager::init()
{
	EATER_Parser = new FBXParser();
	EATER_Parser->Initalize();
}

FBXModel* LoadManager::GetMesh(std::string Name)
{
	std::map<std::string, FBXModel*>::iterator temp = MeshList.find(Name);
	if (temp == MeshList.end())
	{
		std::string temp = "[Find]���� ������ �Ž��� ã�����߽��ϴ� ->" + Name;
		DebugManager::GM()->Print(temp.c_str());
		return nullptr;
	}

	return temp->second;
}

void LoadManager::GetTexture(std::string Name)
{

}

void LoadManager::LoadMesh( std::string Name, bool Scale, bool LoadAnime)
{
	// "../ �̰ſ� .fbx �̰Ÿ� �ٿ��ش�"
	std::string temp = ".fbx";
	std::string FullName = MeshPath + Name + temp;

	DebugManager::GM()->Print(FullName.c_str());
	EATER_Parser->LoadScene(FullName.c_str(), Scale, LoadAnime);

	//�𵨸���Ʈ�� �ִ´�
	FBXModel* box = EATER_Parser->GetModel();
	MeshList.insert({ Name,box });
}

void LoadManager::LoadPrefap(std::string Name)
{
	///���߿� ����
}

void LoadManager::LoadMeshPath(std::string mPath)
{
	//�� ��� �Է�
	MeshPath = mPath;
}

void LoadManager::LoadTexturePath(std::string mPath)
{
	//�ؽ��� ��� �Է�
	TexturePath = mPath;
}

void LoadManager::DeleteMesh(std::string mMeshName)
{
	//�޸𸮿� �Ҵ��� �Ž��� ������ ������Ŵ

	std::map<std::string, FBXModel*>::iterator temp = MeshList.find(mMeshName);
	if (temp == MeshList.end())
	{
		std::string temp = "[Delete]���� ������ �Ž��� ã�����߽��ϴ� ->" + mMeshName;
		DebugManager::GM()->Print(temp.c_str());
		return;
	}
	MeshList.erase(mMeshName);
}

void LoadManager::DeleteMeshAll()
{
	MeshList.clear();
}


