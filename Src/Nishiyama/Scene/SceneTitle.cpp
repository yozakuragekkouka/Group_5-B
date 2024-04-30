#include "DxLib.h"
#include "../../Common.h"
#include "SceneTitle.h"
#include "../Input/Input.h"

//タイトル初期化
void SceneTitle::Init()
{
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_LOOP_TITLE;
}

//タイトル通常処理
void SceneTitle::Step()
{
	if (Input::PressAnyKey())
	{
		SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_TITLE;
	}
}

//タイトル描画処理
void SceneTitle::Draw()
{
}

//タイトル後処理
void SceneTitle::Fin()
{
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_INIT_PLAY;
}