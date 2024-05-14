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

	bgm_Hndl = LoadSoundMem(BGM_PATH);
	Se_Hndl = LoadSoundMem(SE_S_PATH);
	Se2_Hndl = LoadSoundMem(SE_D_PATH);

	//曲の効果音
	PlaySoundMem(bgm_Hndl, DX_PLAYTYPE_LOOP, true);

	Play_Hndl = LoadGraph(PLAY_PATH);
	Play2_Hndl = LoadGraph(PLAY2_PATH);

	arrow_Hndl = LoadGraph(ARROW_PATH);

	arrow_x = 450;
	arrow_y = 450;

	button_x = 650;
	button_y = 450;

	button2_x = 650;
	button2_y = 600;

	bgSkyX[0] = 0;
	bgSkyX1[0] = 1280;
	isEdit = 0;
	currentMapID = 0;

	nextScene = SCENEID::SCENE_ID_INIT_PLAY;
}

//タイトル通常処理
void SceneTitle::Step()
{
	if (Input::IsKeyPush(KEY_INPUT_O))
	{
		isEdit++;
		if (isEdit > 1)
			isEdit = 0;
	}
	if (Input::IsKeyPush(KEY_INPUT_P))
	{
		currentMapID++;
		if (currentMapID > 4)
			currentMapID = 0;
	}

	if (Input::IsKeyPush(KEY_INPUT_BACK))
	{
		nextScene = SCENEID::SCENE_ID_INIT_EDITOR;
		SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_TITLE;
	}
	else if (Input::IsKeyPush(KEY_INPUT_RETURN))
	{
		PlaySoundMem(Se2_Hndl, DX_PLAYTYPE_BACK, true);
		nextScene = SCENEID::SCENE_ID_INIT_PLAY;
		SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_TITLE;
	}
	
	if (Input::IsKeyPush(KEY_INPUT_UP))
	{
		arrow_y = 450;
		PlayNumber = 1;
		PlaySoundMem(Se_Hndl, DX_PLAYTYPE_BACK, true);
	}

	if (Input::IsKeyPush(KEY_INPUT_DOWN))
	{
		arrow_y = 600;

		PlayNumber = 2;
		PlaySoundMem(Se_Hndl, DX_PLAYTYPE_BACK, true);
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

	DrawRotaGraph(button_x, button_y, 0.25, 0.0, Play_Hndl, true);

	DrawRotaGraph(button2_x, button2_y, 0.25, 0.0, Play2_Hndl, true);

	DrawRotaGraph(arrow_x, arrow_y, 0.05, 0.0, arrow_Hndl, true);

	DrawGraph(150, 0, TitleName_Hndl, true);

	DrawFormatString(0, 0, GetColor(255, 255, 255), "プレイヤーの人数：%d", PlayNumber);

	DrawFormatString(0, 300, GetColor(255, 255, 255), "%d, %d", isEdit, currentMapID);
}

//タイトル後処理
void SceneTitle::Fin()
{
	DeleteSoundMem(bgm_Hndl);
	DeleteSoundMem(Se_Hndl);
	DeleteSoundMem(Se2_Hndl);

	Datakanri::data_oriedi = isEdit;
	Datakanri::data_ID = currentMapID;

	SceneManager::g_CurrenySceneID = nextScene;
}