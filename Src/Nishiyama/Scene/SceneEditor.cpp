#include "DxLib.h"
#include "SceneEditor.h"
#include "../Input/Input.h"

//タイトル初期化
void SceneEditor::Init()
{
	editor.Init();
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_LOOP_EDITOR;
}

//タイトル通常処理
void SceneEditor::Step()
{
	if (Input::PressAnyKey())
	{
		SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_EDITOR;
	}

	editor.Step();
}

//タイトル描画処理
void SceneEditor::Draw()
{
	editor.Draw();
}

//タイトル後処理
void SceneEditor::Fin()
{
	editor.Fin();
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_INIT_TITLE;
}