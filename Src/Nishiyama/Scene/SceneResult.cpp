#include "DxLib.h"
#include "../../Common.h"
#include "../Input/Input.h"
#include "SceneResult.h"
#include "SceneTitle.h"



//クリア初期化
void SceneResult::Init()
{

	for (int i = 0; i < 1; i++)
	{
		BackGround_handle[i] = LoadGraph(RESULT_BG_PATH);
		BackGround_handle2[i] = LoadGraph(RESULT_BG2_PATH);
	}

	Win2P_Hndl = LoadGraph(PLAYER2WIN_PATH);
	Win1P_Hndl = LoadGraph(PLAYER1WIN_PATH);
	WinCPU_Hndl = LoadGraph(CPUWIN_PATH);

	BGM_Hndl = LoadSoundMem(BGM_PATH);

	//曲の効果音
	PlaySoundMem(BGM_Hndl, DX_PLAYTYPE_LOOP, true);

	bgSkyX[0] = 0;
	bgSkyX1[0] = 1280;

	Win1P_x = 630;
	Win1P_y = 250;
	Win2P_x = 630;
	Win2P_y = 250;
	WinCPU_x = 630;
	WinCPU_y = 250;

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

	if (IsPlayer1Win == true)
	{
		DrawRotaGraph(Win1P_x, Win1P_y, 0.7, 0.0, Win1P_Hndl, true);
	}
	if (IsPlayer2Win == true)
	{
		DrawRotaGraph(Win2P_x, Win2P_y, 0.7, 0.0, Win2P_Hndl, true);
	}
	if (IsCPUWin == true)
	{
		DrawRotaGraph(WinCPU_x, WinCPU_y, 0.7, 0.0, WinCPU_Hndl, true);
	}
	
}

//クリア後処理
void SceneResult::Fin()
{
	DeleteSoundMem(BGM_Hndl);
	PlayNumber = 0;
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_INIT_TITLE;

}
