#include "ModelParser.h"

#include "ASEFile.h"
#include "ASEParser.h"

#include "BoneWeights.h"
#define FBXSDK_SHARED
#pragma comment(lib, "libfbxsdk")
#include <fbxsdk.h>
#include "FBXParser.h"

std::string ModelParser::g_TextureRoute;

PARSER_DLL ModelParser* ModelParser::Create(Type type)
{
	ModelParser* newParser = nullptr;

	switch (type)
	{
	case ModelParser::Type::ASE:
		newParser = new ASEParser;
		newParser->Initialize();
		break;
	case ModelParser::Type::FBX:
		newParser = new FBXParser;
		newParser->Initialize();
		break;
	default:
		break;
	}

	return newParser;
}

PARSER_DLL void ModelParser::SetTextureRoute(std::string texRoute)
{
	// 기본 Texture 파일 루트 설정
	g_TextureRoute = texRoute;
}
