#pragma once

#include <string>
class FBXParser;
class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();


	//초기화
	void init();
	//모델 로드
	void LoadMesh(std::string Name,bool LoadAnime);
private:
	FBXParser* EATER_Parser;
};