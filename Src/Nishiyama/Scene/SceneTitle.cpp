#include "DxLib.h"
#include "../../Common.h"
#include "SceneTitle.h"
#include "../Input/Input.h"

//タイトル初期化
void SceneTitle::Init()
{
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_LOOP_TITLE;

	Title_Hndl = LoadGraph(TITLE_PATH);

	Playbutton_Hndl = LoadGraph(BUTTON_PATH);

	button_x = 440;
	button_y = 400;
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
	DrawGraph(0, 0, Title_Hndl, true);
	DrawGraph(button_x, button_y, Playbutton_Hndl, true);
}

//タイトル後処理
void SceneTitle::Fin()
{
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_INIT_PLAY;
}