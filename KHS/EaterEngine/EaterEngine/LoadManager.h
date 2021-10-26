#pragma once

/// <summary>
/// 매쉬,텍스쳐,프리팹,등등 그리기위해서 필요한것들을 로드
/// 
/// 
/// 테스트용으로 동혁이꺼 랜더링 엔진이 붙어있음
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

	

	//초기화 및 경로 설정
	void init();
public:
	///GET
	//매쉬 가져오기
	FBXModel* GetMesh(std::string Name);
	//텍스쳐 가져오기
	void GetTexture(std::string Name);

	///Load
	//모델 로드(스크린 이름,모델의 이름,스케일 여부,애니메이션 여부)
	void LoadMesh(std::string Name, bool Scale = true,bool LoadAnime = false);
	//프리펩 로드
	void LoadPrefap(std::string Name);

	///경로
	//매쉬 경로 설정
	void LoadMeshPath(std::string mPath);
	//텍스쳐 경로
	void LoadTexturePath(std::string mPath);

	///Delete
	//리스트에서 매쉬정보를 삭제(매쉬가 너무많아서 메모리가 부족할때)
	void DeleteMesh(std::string mMeshName);
	//모든 매쉬정보를 삭제
	void DeleteMeshAll();
private:
	//엔진에 맞게 데이터를 변경시킴
	void ChangeData(FBXModel* mData);




private:



	//모델이 들어있는 경로
	std::string MeshPath;
	//텍스쳐가 들어있는 경로
	std::string TexturePath;
	//인덱스 버퍼 
	//버텍스 버퍼
	 
	//메터리얼
	 
	//텍스쳐
	
	//애니메이션
	//



	///리스트
	std::map<std::string,FBXModel*> MeshList;

	//쉐이더 
	//텍스쳐

private:
	FBXParser* EATER_Parser;
};
