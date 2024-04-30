#include "DxLib.h"
#include "../../Common.h"
#include "../Input/Input.h"
#include "SceneResult.h"

//�N���A������
void SceneResult::Init()
{
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_LOOP_RESULT;
}

//�N���A�ʏ폈��
void SceneResult::Step()
{
	if (Input::PressAnyKey())
	{
		SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_RESULT;
	}
}

//�N���A�`�揈��
void SceneResult::Draw()
{
}

//�N���A�㏈��
void SceneResult::Fin()
{
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_INIT_TITLE;
}
