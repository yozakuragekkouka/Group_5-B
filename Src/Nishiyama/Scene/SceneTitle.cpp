#include "DxLib.h"
#include "../../Common.h"
#include "SceneTitle.h"
#include "../Input/Input.h"


int PlayNumber = 1;

//�^�C�g��������
void SceneTitle::Init()
{
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_LOOP_TITLE;

	Title_Hndl = LoadGraph(TITLE_PATH);

	Playbutton_Hndl = LoadGraph(BUTTON_PATH);

	button_x = 440;
	button_y = 400;
}

//�^�C�g���ʏ폈��
void SceneTitle::Step()
{
	if (Input::IsKeyPush(KEY_INPUT_RETURN))
	{
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

	
}

//�^�C�g���`�揈��
void SceneTitle::Draw()
{
	DrawGraph(0, 0, Title_Hndl, true);
	DrawGraph(button_x, button_y, Playbutton_Hndl, true);

	DrawFormatString(0, 0, GetColor(255, 255, 255), "�v���C���[�̐l���F%d", PlayNumber);
}

//�^�C�g���㏈��
void SceneTitle::Fin()
{
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_INIT_PLAY;
}