#pragma once

/// <summary>
/// 매쉬,텍스쳐,등등 그리기위해서 필요한것들을 로드
/// </summary>




#include <string>
class FBXParser;
class LoadManager
{
public:
	LoadManager();
	~LoadManager();

	//초기화 및 경로 설정
	void init();
	//모델 로드
	void LoadMesh(std::string Name,bool LoadAnime);
	//프리펩 로드
	void LoadPrefap(std::string Name);
	//매쉬 경로 설정
	void LoadMeshPath(std::string mPath);

private:
	//모델이 들어있는 경로
	std::string MeshPath;
	//텍스쳐가 들어있는 경로
	std::string TexturePath;




	FBXParser* EATER_Parser;
};