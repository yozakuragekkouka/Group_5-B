#include <math.h>

#include "DxLib.h"
#include "../../Common.h"
#include "../Input/Input.h"
#include "ScenePlay.h"
#include "SceneTitle.h"
#include "../Collision/Collision.h"

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

	/*for (int BulletIndex = 0; BulletIndex < player[0].GetBulletMaxNum(); BulletIndex++)
	{
	}

	for (int BulletIndex = 0; BulletIndex < player[1].GetBulletMaxNum(); BulletIndex++)
	{
	}*/

	//�v���C���[1�̒e�̓����蔻��(�v���C���[2���_���[�W���󂯂�)
	if (player[0].GetBulletIsUse() == true)
	{
		if (Collision::IsHitRect(player[0].GetBulletPos(), player[1].GetPlayerPos(), player[0].GetBulletSize(), player[1].GetPlayerSize()))
		{
			//�v���C���[2�Ƀ_���[�W��^����
			player[1].Damege(player[0].GetBulletDamege());
			//�e�̎g�p�t���O��false�ɂ���
			player[0].SetBulletIsUse();
		}
	}
	//�v���C���[2�̒e�̓����蔻��(�v���C���[1���_���[�W���󂯂�)
	if (player[1].GetBulletIsUse() == true)
	{
		if (Collision::IsHitRect(player[1].GetBulletPos(), player[0].GetPlayerPos(), player[1].GetBulletSize(), player[0].GetPlayerSize()))
		{
			//�v���C���[1�Ƀ_���[�W��^����
			player[0].Damege(player[1].GetBulletDamege());
			//�e�̎g�p�t���O��false�ɂ���
			player[1].SetBulletIsUse();
		}
	}

	if (PlayNumber == 1)
	{
		if (player[0].GetHP() <= 0)
		{
			SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_PLAY;
		}
	}
	else if (PlayNumber == 2)
	{
		if (player[0].GetHP() <= 0 || player[1].GetHP() <= 0)
		{
			SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_PLAY;
		}
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

	DrawFormatString(0, 200, GetColor(255, 255, 255), "�v���C���[1�̗̑́F%d", player[0].GetHP());
	DrawFormatString(0, 215, GetColor(255, 255, 255), "�v���C���[2�̗̑́F%d", player[1].GetHP());

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



//�e�̓����蔻��
//Pos�Ŏw�肵���v���C���[���U����H�炤�悤�ɂ��Ă܂�
//��6�����̓_���[�W���󂯂���̃v���C���[�z��ԍ�(0��1)
//��7�����̓_���[�W��^������̃v���C���[�z��ԍ�(0��1)
void ScenePlay::IsHitBullet(VECTOR BulletPos, VECTOR BulletSize, VECTOR Pos, VECTOR PosSize, int Damage, int take_damageNum, int deal_damageNum)
{
	//�e�ƃv���C���[�̓����蔻����Ƃ�
	if (Collision::IsHitRect(BulletPos, BulletSize, Pos, PosSize))
	{
		player[take_damageNum].Damege(Damage);
		player[deal_damageNum].SetBulletIsUse();
	}
}
