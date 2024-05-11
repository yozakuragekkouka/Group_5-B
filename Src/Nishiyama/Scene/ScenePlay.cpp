#include <math.h>

#include "DxLib.h"
#include "../../Common.h"
#include "../Input/Input.h"
#include "ScenePlay.h"
#include "SceneTitle.h"

//����
#include"../DefaultMap/DefaultMap.h"
_Map* CMap;

//�v���C�V�[��������
void ScenePlay::Init()
{
	bg.Init(BackGroundKind::NONE);

	player = new PLAYER[2];

	//����
	CMap = new _Map;
	CMap->Init();

	player[0].Init(1);
	player[0].SetPlayerPos(Player1Pos);
	player[0].Load();
	
	if (PlayNumber == 2)
	{
		player[1].Init(2);
		player[1].SetPlayerPos(Player2Pos);
		player[1].Load();
	}
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_LOOP_PLAY;
}

//�v���C�V�[���ʏ폈��
void ScenePlay::Step()
{
	bg.Step();

	player[0].Step();
	if (PlayNumber == 2)
	{
		player[1].Step();
	}
	if (Input::IsKeyPush(KEY_INPUT_RETURN))
	{
		SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_PLAY;
	}
}

//�v���C�V�[���`�揈��
void ScenePlay::Draw()
{
	bg.Draw();

	//����
	CMap->Draw();

	player[0].Draw(0);
	if (PlayNumber == 2)
	{
		player[1].Draw(1);
	}
}

//�v���C�V�[���㏈��
//���g���C���ǂ�����Ԃ�
void ScenePlay::Fin()
{
	bg.Fin();
	player[0].Delete();
	if (PlayNumber == 2)
	{
		player[1].Delete();
	}

	delete[]player;
	player = nullptr;

	//����
	delete CMap;
	CMap = nullptr;

	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_INIT_RESULT;
}
