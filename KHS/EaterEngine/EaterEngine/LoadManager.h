#pragma once

/// <summary>
/// 매쉬,텍스쳐,프리팹,등등 그리기위해서 필요한것들을 로드
/// 
/// 
/// 테스트용으로 동혁이꺼 랜더링 엔진이 붙어있음
/// </summary>



#include <string>
#include <map>
#include "ParserData.h"
#include "SharedData.h"

struct ParserData::Model;
struct Model;
class LoadData;
class ModelParser;
class FBXParser;
class FBXModel;
class DH3DEngine;
class GraphicEngine;

class LoadManager
{
public:
	LoadManager();
	~LoadManager();

	

	//초기화 및 경로 설정
	void Initialize(GraphicEngine* Graphic);
	//테스트용
	void Initialize(DH3DEngine* Graphic);
public:
	///GET
	//매쉬 가져오기
	static LoadData* GetMesh(std::string Name);
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

	//모델이 들어있는 경로
	std::string MeshPath;
	//텍스쳐가 들어있는 경로
	std::string TexturePath;
	
	///리스트
	static std::map<std::string,LoadData*> MeshList;
private:
	//규황이 파서
	ModelParser*	EaterParser;
	//누군가의 그래픽 엔진
	GraphicEngine*	GEngine;


	///여기부터는 동혁이꺼 테스트용
	DH3DEngine*			DHEngine;
	OneFrameData*		pTest_OFD;
	SharedRenderData*	pTest_SRD;
	DHParser::Mesh*		pTest_Mesh;

	void Test_DHData(ParserData::Model* mModel, std::string Name);
};
