#include "DxLib.h"
#include "../../Common.h"
#include "SceneTitle.h"
#include "../Input/Input.h"


int PlayNumber = 1;


//タイトル初期化
void SceneTitle::Init()
{
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_LOOP_TITLE;


	for (int i = 0; i < 1; i++)
	{
		BackGround_handle[i] = LoadGraph(TITLE_PATH);
		BackGround_handle2[i] = LoadGraph(TITLE2_PATH);
	}
	

	Playbutton_Hndl = LoadGraph(BUTTON_PATH);
	TitleName_Hndl = LoadGraph(TITLE_NAME_PATH);

	button_x = 650;
	button_y = 500;

	bgSkyX[0] = 0;
	bgSkyX1[0] = 1280;

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

//タイトル描画処理
void SceneTitle::Draw()
{
	//タイトル画像表示
	for (int i = 0; i < 1; i++)
	{
		DrawGraph(bgSkyX[i], 0, BackGround_handle[i], true);
		DrawGraph(bgSkyX1[i], 0, BackGround_handle2[i], true);
	}

	DrawGraph(150, 0, TitleName_Hndl, true);

	DrawRotaGraph(button_x, button_y, 0.25, 0.0, Playbutton_Hndl, true);

	DrawFormatString(0, 0, GetColor(255, 255, 255), "プレイヤーの人数：%d", PlayNumber);
}

//タイトル後処理
void SceneTitle::Fin()
{
	SceneManager::g_CurrenySceneID = nextScene;
}