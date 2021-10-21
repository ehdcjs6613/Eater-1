#include "LoadManager.h"
#include "DebugManager.h"

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

void LoadManager::LoadMesh(std::string Name, bool LoadAnime)
{
	
	std::string temp = ".fbx";
	std::string FullName = MeshPath + Name + temp;

	DebugManager::GM()->Print(FullName.c_str());
	EATER_Parser->LoadScene(FullName.c_str(), true, LoadAnime);
	FBXModel* mo = EATER_Parser->GetModel();
	int num = 0;
}

void LoadManager::LoadPrefap(std::string Name)
{
	///나중에 구현
}

void LoadManager::LoadMeshPath(std::string mPath)
{
	MeshPath = mPath;
}
