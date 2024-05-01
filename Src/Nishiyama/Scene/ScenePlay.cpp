#include <math.h>

#include "DxLib.h"
#include "../../Common.h"
#include "../Input/Input.h"
#include "ScenePlay.h"

//�v���C�V�[��������
void ScenePlay::Init()
{
	bg.Init(BackGroundKind::NONE);
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_LOOP_PLAY;
}

//�v���C�V�[���ʏ폈��
void ScenePlay::Step()
{
	bg.Step();
	if (Input::PressAnyKey())
	{
		SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_PLAY;
	}
}

//�v���C�V�[���`�揈��
void ScenePlay::Draw()
{
	bg.Draw();
}

//�v���C�V�[���㏈��
//���g���C���ǂ�����Ԃ�
void ScenePlay::Fin()
{
	bg.Fin();
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_INIT_RESULT;
}
