#include <math.h>

#include "DxLib.h"
#include "../../Common.h"
#include "../Input/Input.h"
#include "ScenePlay.h"
#include "SceneTitle.h"
#include "../Collision/Collision.h"





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
	//�}�b�v�Ƃ̓����蔻��
	MapCollision();

	//�ߐڍU���̓����蔻��
	
	//�e�̓����蔻��--------------------------------------------------------------
	//�v���C���[1�̒e�̓����蔻��(�v���C���[2���_���[�W���󂯂�)
	if (player[0].GetDamegeCoolTime() >= 30)
	{
		if (player[0].GetBulletIsUse() == true)
		{

			if (Collision::IsHitRect(player[0].GetBulletPos(), player[1].GetPlayerPos(), player[0].GetBulletSize(), player[1].GetPlayerSize()))
			{
				//�v���C���[2�Ƀ_���[�W��^����
				player[1].Damege(player[0].GetBulletDamege());
				//�_���[�W�N�[���^�C����0�ɂ���
				player[1].SetDamageCoolTime();
				//�e�̎g�p�t���O��false�ɂ���
				player[0].SetBulletIsUse();
			}
		}
	}
	//�v���C���[2�̒e�̓����蔻��(�v���C���[1���_���[�W���󂯂�)
	if (player[1].GetDamegeCoolTime() >= 30)
	{
		if (player[1].GetBulletIsUse() == true)
		{
			if (Collision::IsHitRect(player[1].GetBulletPos(), player[0].GetPlayerPos(), player[1].GetBulletSize(), player[0].GetPlayerSize()))
			{
				//�v���C���[1�Ƀ_���[�W��^����
				player[0].Damege(player[1].GetBulletDamege());
				//�_���[�W�N�[���^�C����0�ɂ���
				player[0].SetDamageCoolTime();
				//�e�̎g�p�t���O��false�ɂ���
				player[1].SetBulletIsUse();
			}
		}
	}
	//---------------------------------------------------------------------------

	for (int Number = 1; Number < 3; Number++)
	{
		if (player[Number].GetDamegeCoolTime() <= 30)
		{
			player[Number].AddDamageCoolTime(1);
		}
	}

	if (PlayNumber == 1)
	{
		if (player[0].GetHP() <= 0)
		{
			IsPlayer1Win = false;
			IsPlayer2Win = false;
			IsCPUWin = true;
			SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_PLAY;
		}
	}
	else if (PlayNumber == 2)
	{
		if (player[0].GetHP() <= 0 || player[1].GetHP() <= 0)
		{
			SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_PLAY;
		}
		//�v���C���[2��HP���Ȃ��Ȃ����Ƃ�
		if (player[1].GetHP() <= 0)
		{
			IsPlayer1Win = true;
			IsPlayer2Win = false;
			IsCPUWin = false;
		}
		//�v���C���[1��HP���Ȃ��Ȃ����Ƃ�
		if (player[0].GetHP() <= 0)
		{
			IsPlayer2Win = true;
			IsPlayer1Win = false;
			IsCPUWin = false;
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

//����
// �}�b�v�̓����蔻��
void ScenePlay::MapCollision() {
	for (int index = 0; index < PlayNumber; index++) {
		CheckCollision(index, true);  // Y�����̓����蔻��
		CheckCollision(index, false); // X�����̓����蔻��
	}
}

void ScenePlay::CheckCollision(int index, bool checkY) {
	DrawFormatString(0, 300, GetColor(255, 255, 255), "%f", player[0].GetNextPos().y);
	for (int mapIndexY = 0; mapIndexY < MAP_DATA_Y; mapIndexY++) {
		for (int mapIndexX = 0; mapIndexX < MAP_DATA_X; mapIndexX++) {
			if (CMap->m_MapData[mapIndexY][mapIndexX] == 0) continue;

			bool dirArray[4] = { false, false, false, false };
			player[index].GetMoveDirection(dirArray);

			VECTOR A = { player[index].GetNormalPlayerPos().x,player[index].GetNormalPlayerPos().y ,0 };
			VECTOR Asize = { player[index].GetPlayerSize().x ,player[index].GetPlayerSize().y ,0};

			VECTOR B = { (mapIndexX * MAP_SIZE)+ MAP_SIZE , (mapIndexY * MAP_SIZE) + MAP_SIZE ,0 };
			VECTOR Bsize = { MAP_SIZE ,MAP_SIZE ,0 };

			if (checkY) {
				A.y = player[index].GetNextPos().y;
			}
			else {
				A.x = player[index].GetNextPos().x;
			}
			if (Collision::IsHitRect(A, B, Asize, Bsize)) {
				DrawFormatString(0, 400, GetColor(255, 255, 255), "%f", B.x);
				player[index].HandleCollision(index, dirArray, A, B, Asize, Bsize, checkY);
			}
		}
	}
}