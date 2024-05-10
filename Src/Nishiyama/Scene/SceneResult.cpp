#include "DxLib.h"
#include "../../Common.h"
#include "../Input/Input.h"
#include "SceneResult.h"

//�N���A������
void SceneResult::Init()
{

	for (int i = 0; i < 1; i++)
	{
		BackGround_handle[i] = LoadGraph(RESULT_BG_PATH);
		BackGround_handle2[i] = LoadGraph(RESULT_BG2_PATH);
	}

	Win1P_Hndl = LoadGraph(PLAYER1WIN_PATH);
	Win2P_Hndl = LoadGraph(PLAYER2WIN_PATH);
	WinCPU_Hndl = LoadGraph(CPUWIN_PATH);

	bgSkyX[0] = 0;
	bgSkyX1[0] = 1280;

	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_LOOP_RESULT;
}

//�N���A�ʏ폈��
void SceneResult::Step()
{
	if (Input::PressAnyKey())
	{
		SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_RESULT;
	}

	//�w�i�ړ�����
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

//�N���A�`�揈��
void SceneResult::Draw()
{
	//�^�C�g���摜�\��
	for (int i = 0; i < 1; i++)
	{
		DrawGraph(bgSkyX[i], 0, BackGround_handle[i], true);
		DrawGraph(bgSkyX1[i], 0, BackGround_handle2[i], true);
	}

	////1P��2P�ɏ��������̕`��
	//if(//PlayScene�Ńt���O��true)
	//	{
	//		DrawGraph(650, 500, Win1P_Hndl, true);
	//	}
	//else
	//{
	//	DrawGraph(650, 500, Win2P_Hndl, true);
	//}
	////1P��CPU�ɏ��������̕`��
	//else if(//1P��HP > CPU��HP�@|| CPU��HP == 0)
	//{
	//	DrawGraph(650, 500, Win1P_Hndl, true);
	//	}
	//else {
	//	DrawGraph(650, 500, WinCPU_Hndl, true);
	//}
}

//�N���A�㏈��
void SceneResult::Fin()
{
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_INIT_TITLE;
}
