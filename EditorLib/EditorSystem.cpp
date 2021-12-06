#include "LibDefine.h"
#include "MainHeader.h"
#include "TScene.h"
#include "EditorSystem.h"

EditorSystem::EditorSystem()
{
}

EditorSystem::~EditorSystem()
{
}

void EditorSystem::Start(HWND _g_hWnd)
{
	EngineInitialize(_g_hWnd);
	int num = 0;


	CreateScene<TScene>("TScene");
	ChoiceScene("TScene");
}

void EditorSystem::Update()
{
	UpdateEngine();
}
