#include "DxLib.h"
#include "../../Common.h"
#include "SceneTitle.h"
#include "../Input/Input.h"


int PlayNumber = 1;


//タイトル初期化
void SceneTitle::Init()
{
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_LOOP_TITLE;


	for (int i = 0; i < 2; i++)
	{
		BackGround_handle[i] = LoadGraph(TITLE_PATH);
		BackGround_handle2[i] = LoadGraph(TITLE2_PATH);
	}
	

	Playbutton_Hndl = LoadGraph(BUTTON_PATH);

	button_x = 440;
	button_y = 400;

	bgSkyX[0] = 0;
	bgSkyX[1] = -SCREEN_SIZE_X;
	bgSkyX1[0] = 0;
	bgSkyX1[1] = -SCREEN_SIZE_X;

	nextScene = SCENEID::SCENE_ID_INIT_PLAY;
}

//タイトル通常処理
void SceneTitle::Step()
{
	if (Input::IsKeyPush(KEY_INPUT_BACK))
	{
		nextScene = SCENEID::SCENE_ID_INIT_EDITOR;
		SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_TITLE;
	}
	else if (Input::IsKeyPush(KEY_INPUT_RETURN))
	{
		nextScene = SCENEID::SCENE_ID_INIT_PLAY;
		SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_TITLE;
	}

	if (Input::IsKeyPush(KEY_INPUT_UP))
	{
		PlayNumber = 2;
	}

	if (Input::IsKeyPush(KEY_INPUT_DOWN))
	{
		PlayNumber = 1;
	}

	//背景移動処理
	for (int i = 0; i < 2; i++)
	{
		bgSkyX[i] -= 2;
		bgSkyX1[i] -= 2;

		if (bgSkyX[i] <= -1280)
		{
			bgSkyX[i] = 1270;
		}
		if (bgSkyX1[i] <= -1280)
		{
			bgSkyX1[i] = 1270;
		}
	}
}

//タイトル描画処理
void SceneTitle::Draw()
{
	//タイトル画像表示
	for (int i = 0; i < 2; i++)
	{
		DrawGraph(bgSkyX[i], 0, BackGround_handle[i], true);
		DrawGraph(bgSkyX1[i], 0, BackGround_handle2[i], true);
	}

	DrawGraph(button_x, button_y, Playbutton_Hndl, true);

	DrawFormatString(0, 0, GetColor(255, 255, 255), "プレイヤーの人数：%d", PlayNumber);
}

//タイトル後処理
void SceneTitle::Fin()
{
	SceneManager::g_CurrenySceneID = nextScene;
}