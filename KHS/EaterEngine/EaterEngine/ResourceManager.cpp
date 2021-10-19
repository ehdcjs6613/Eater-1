#include "ResourceManager.h"
#include "KHParser.h"

ResourceManager::ResourceManager()
{
	EATER_Parser = nullptr;
}

ResourceManager::~ResourceManager()
{

}

void ResourceManager::init()
{
	EATER_Parser = new FBXParser();
	EATER_Parser->Initalize();
}

void ResourceManager::LoadMesh(std::string Name, bool LoadAnime)
{


}
