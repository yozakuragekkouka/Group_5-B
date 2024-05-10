#include "DxLib.h"
#include "../../Common.h"
#include "../Input/Input.h"
#include "SceneResult.h"

//クリア初期化
void SceneResult::Init()
{

	for (int i = 0; i < 1; i++)
	{
		BackGround_handle[i] = LoadGraph(RESULT_BG_PATH);
		BackGround_handle2[i] = LoadGraph(RESULT_BG2_PATH);
	}

	bgSkyX[0] = 0;
	bgSkyX1[0] = 1280;

	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_LOOP_RESULT;
}

//クリア通常処理
void SceneResult::Step()
{
	if (Input::PressAnyKey())
	{
		SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_RESULT;
	}

	//背景移動処理
	for (int i = 0; i < 1; i++)
	{
		bgSkyX[i] -= 4;
		bgSkyX1[i] -= 4;

		if (bgSkyX[i] <= -1270)
		{
			bgSkyX[i] = 1285;
		}
		if (bgSkyX1[i] <= -1270)
		{
			bgSkyX1[i] = 1285;
		}
	}
}

//クリア描画処理
void SceneResult::Draw()
{
	//タイトル画像表示
	for (int i = 0; i < 1; i++)
	{
		DrawGraph(bgSkyX[i], 0, BackGround_handle[i], true);
		DrawGraph(bgSkyX1[i], 0, BackGround_handle2[i], true);
	}
}

//クリア後処理
void SceneResult::Fin()
{
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_INIT_TITLE;
}
