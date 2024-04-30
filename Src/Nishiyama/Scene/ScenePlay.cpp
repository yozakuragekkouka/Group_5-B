#include <math.h>

#include "DxLib.h"
#include "../../Common.h"
#include "../Input/Input.h"
#include "ScenePlay.h"

//�v���C�V�[��������
void ScenePlay::Init()
{
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_LOOP_PLAY;
}

//�v���C�V�[���ʏ폈��
void ScenePlay::Step()
{
	if (Input::PressAnyKey())
	{
		SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_PLAY;
	}
}

//�v���C�V�[���`�揈��
void ScenePlay::Draw()
{

}

//�v���C�V�[���㏈��
//���g���C���ǂ�����Ԃ�
void ScenePlay::Fin()
{
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_INIT_RESULT;
}
