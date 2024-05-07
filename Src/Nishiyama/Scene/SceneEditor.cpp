#include "DxLib.h"
#include "SceneEditor.h"
#include "../Input/Input.h"

//�^�C�g��������
void SceneEditor::Init()
{
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_LOOP_EDITOR;
}

//�^�C�g���ʏ폈��
void SceneEditor::Step()
{
	if (Input::PressAnyKey())
	{
		SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_EDITOR;
	}
}

//�^�C�g���`�揈��
void SceneEditor::Draw()
{

}

//�^�C�g���㏈��
void SceneEditor::Fin()
{
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_INIT_TITLE;
}