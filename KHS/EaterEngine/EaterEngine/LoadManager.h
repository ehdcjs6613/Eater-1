#pragma once

/// <summary>
/// 매쉬,텍스쳐,등등 그리기위해서 필요한것들을 로드
/// </summary>




#include <string>
#include <map>
class FBXParser;
class FBXModel;
class LoadManager
{
public:
	LoadManager();
	~LoadManager();

	//초기화 및 경로 설정
	void init();
public:
	///GET
	//매쉬 가져오기
	FBXModel* GetMesh(std::string Name);
	//텍스쳐 가져오기
	void GetTexture(std::string Name);
public:
	///Load
	//모델 로드(스크린 이름,모델의 이름,스케일 여부,애니메이션 여부)
	void LoadMesh(std::string Name, bool Scale = true,bool LoadAnime = false);
	//프리펩 로드
	void LoadPrefap(std::string Name);

public:
	///경로
	//매쉬 경로 설정
	void LoadMeshPath(std::string mPath);
	//텍스쳐 경로
	void LoadTexturePath(std::string mPath);
private:
	//모델이 들어있는 경로
	std::string MeshPath;
	//텍스쳐가 들어있는 경로
	std::string TexturePath;
public:
	///Delete
	//리스트에서 매쉬정보를 삭제(메모리 낭비를 막기위해,매쉬가 너무많아서 메모리가 부족할때)
	void DeleteMesh(std::string mMeshName);
	//모든 매쉬정보를 삭제
	void DeleteMeshAll();
private:
	///리스트
	//매쉬
	std::map<std::string,FBXModel*> MeshList;
	//쉐이더 
	//텍스쳐

private:
	FBXParser* EATER_Parser;
};