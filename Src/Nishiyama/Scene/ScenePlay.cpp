#include <math.h>

#include "DxLib.h"
#include "../../Common.h"
#include "../Input/Input.h"
#include "ScenePlay.h"
#include "SceneTitle.h"
#include "../Collision/Collision.h"
#include"../Effect/Effect.h"




//�v���C�V�[��������
void ScenePlay::Init()
{
	bg1.Init(BackGroundKind::SKY);
	bg2.Init(BackGroundKind::CLOUD);
	bg3.Init(BackGroundKind::BUILDING);

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

	//�G�t�F�N�g�̏�����
	InitEffect();
	//�G�t�F�N�g�̓ǂݍ���
	LoadEffect(EFFECT_TYPE_JUMP, 10);
	LoadEffect(EFFECT_TYPE_HIT, 2);

	playBgm_Hndl = LoadSoundMem(PLAYBGM_PATH);
	HitSe_Hndl = LoadSoundMem(HITSE_PATH);
	//�Ȃ̌��ʉ�
	PlaySoundMem(playBgm_Hndl, DX_PLAYTYPE_LOOP, true);


	MapDrawFlag = false;
	isEdit = 0;
	currentMapID = 0;

	for (int Ori_or_Edi = 0; Ori_or_Edi < 2; Ori_or_Edi++)
	{
		for (int mapID = 0; mapID < 5; mapID++)
		{
			map[Ori_or_Edi][mapID].Init((bool)Ori_or_Edi, mapID);
		}
	}

	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_LOOP_PLAY;
}

//�v���C�V�[���ʏ폈��
void ScenePlay::Step()
{
	bg1.Step();
	bg2.Step();
	bg3.Step();

	player[0].Step();
	if (PlayNumber == 2)
	{
		player[1].Step();
	}
	//�}�b�v�Ƃ̓����蔻��
	MapCollision();


	StepEffect();

	for (int Ori_or_Edi = 0; Ori_or_Edi < 2; Ori_or_Edi++)
	{
		for (int mapID = 0; mapID < 5; mapID++)
		{
			map[Ori_or_Edi][mapID].Step();
		}
	}

	if (Input::IsKeyPush(KEY_INPUT_I))
	{
		MapDrawFlag = !MapDrawFlag;
	}
	if (MapDrawFlag)
	{
		if (Input::IsKeyPush(KEY_INPUT_O))
		{
			isEdit++;
			if (isEdit > 1)
				isEdit = 0;
		}
		if (Input::IsKeyPush(KEY_INPUT_P))
		{
			currentMapID++;
			if (currentMapID > 4)
				currentMapID = 0;
		}
	}

	if (PlayNumber == 2)
	{
		//�ߐڍU���̓����蔻��
		if (Input::IsKeyPush(player[0].GetBottan()))
		{
			//��
			if (player[0].GetPlayerdir() == 0)
			{
				//�v���C���[1�̓����蔻��(�v���C���[2���_���[�W���󂯂�)
				if (player[0].GetDamegeCoolTime() >= 30)
				{
					if (Collision::IsHitRectNormal(player[0].GetPunchPosX() - 64, player[0].GetPunchPosY() - 32, 32, 64,
						player[1].GetPunchPosX() - 32, player[1].GetPunchPosY() - 32, 64, 64))
					{
						PlayEffect(EFFECT_TYPE_HIT, 
							player[1].GetNormalPlayerPos().x, 
							player[1].GetNormalPlayerPos().y);
						PlaySoundMem(HitSe_Hndl, DX_PLAYTYPE_BACK, true);

						player[1].Damege(10);
					}
				}
			}
			//�E
			if (player[0].GetPlayerdir() == 1)
			{
				if (player[0].GetDamegeCoolTime() >= 30)
				{
					if (Collision::IsHitRectNormal(player[0].GetPunchPosX() + 32, player[0].GetPunchPosY() - 32, 32, 64,
						player[1].GetPunchPosX() - 32, player[1].GetPunchPosY() - 32, 64, 64))
					{
						PlayEffect(EFFECT_TYPE_HIT, 
							player[1].GetNormalPlayerPos().x, 
							player[1].GetNormalPlayerPos().y);
						PlaySoundMem(HitSe_Hndl, DX_PLAYTYPE_BACK, true);

						player[1].Damege(10);
					}
				}
			}

		}

		//�ߐڍU���̓����蔻��
		if (Input::IsKeyPush(player[1].GetBottan()))
		{
			//�v���C���[2�̓����蔻��(�v���C���[1���_���[�W���󂯂�)
			if (player[1].GetPlayerdir() == 0)
			{
				if (player[1].GetDamegeCoolTime() >= 30)
				{
					if (Collision::IsHitRectNormal(player[1].GetPunchPosX() - 64, player[1].GetPunchPosY() - 32, 32, 64,
						player[0].GetPunchPosX() - 32, player[0].GetPunchPosY() - 32, 64, 64))
					{
						PlayEffect(EFFECT_TYPE_HIT, 
							player[0].GetNormalPlayerPos().x, 
							player[0].GetNormalPlayerPos().y);
						PlaySoundMem(HitSe_Hndl, DX_PLAYTYPE_BACK, true);

						player[0].Damege(10);
					}
				}
			}
			//�E
			if (player[1].GetPlayerdir() == 1)
			{
				if (player[1].GetDamegeCoolTime() >= 30)
				{
					if (Collision::IsHitRectNormal(player[1].GetPunchPosX() + 32, player[1].GetPunchPosY() - 32, 32, 64,
						player[0].GetPunchPosX() - 32, player[0].GetPunchPosY() - 32, 64, 64))
					{
						PlayEffect(EFFECT_TYPE_HIT, 
							player[0].GetNormalPlayerPos().x,
							player[0].GetNormalPlayerPos().y);
						PlaySoundMem(HitSe_Hndl, DX_PLAYTYPE_BACK, true);

						player[0].Damege(10);
					}
				}
			}
		}
	}
	
	if (PlayNumber == 2)
	{
		//�e�̓����蔻��--------------------------------------------------------------
	//�v���C���[1�̒e�̓����蔻��(�v���C���[2���_���[�W���󂯂�)
		if (player[0].GetDamegeCoolTime() >= 30)
		{
			for (int i = 0; i < BULLET_MAX_NUM; i++)
			{
				if (player[0].GetBulletIsUse(i) == true)
				{
					if (Collision::IsHitRect(player[0].GetBulletPos(i), player[1].GetNormalPlayerPos(), player[0].GetBulletSize(), player[1].GetPlayerSize()))
					{
						PlayEffect(EFFECT_TYPE_HIT,
							player[1].GetNormalPlayerPos().x,
							player[1].GetNormalPlayerPos().y);
						//�v���C���[2�Ƀ_���[�W��^����
						player[1].Damege(player[0].GetBulletDamege());
						//�_���[�W�N�[���^�C����0�ɂ���
						player[1].SetDamageCoolTime();
						//�e�̎g�p�t���O��false�ɂ���
						player[0].SetBulletIsUse(i);
					}
				}
			}
		}

		//�v���C���[2�̒e�̓����蔻��(�v���C���[1���_���[�W���󂯂�)
		if (player[1].GetDamegeCoolTime() >= 30)
		{
			for (int i = 0; i < BULLET_MAX_NUM; i++)
			{
				if (player[1].GetBulletIsUse(i) == true)
				{
					if (Collision::IsHitRect(player[1].GetBulletPos(i), player[0].GetNormalPlayerPos(), player[1].GetBulletSize(), player[0].GetPlayerSize()))
					{
						PlayEffect(EFFECT_TYPE_HIT,
							player[0].GetNormalPlayerPos().x,
							player[0].GetNormalPlayerPos().y);
						//�v���C���[1�Ƀ_���[�W��^����
						player[0].Damege(player[1].GetBulletDamege());
						//�_���[�W�N�[���^�C����0�ɂ���
						player[0].SetDamageCoolTime();
						//�e�̎g�p�t���O��false�ɂ���
						player[1].SetBulletIsUse(i);
					}
				}
			}
		}

		//�_���[�W�N�[���^�C�������Z
		for (int Number = 0; Number < 2; Number++)
		{
			if (player[Number].GetDamegeCoolTime() <= 30)
			{
				player[Number].AddDamageCoolTime(1);
			}
		}
		//---------------------------------------------------------------------------

	}
	
	//�I������-------------------------------------------------------------------
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
	//-----------------------------------------------------------------------
}

//�v���C�V�[���`�揈��
void ScenePlay::Draw()
{
	bg1.Draw();
	bg2.Draw();
	bg3.Draw();

	//����
	if (MapDrawFlag == false)
	{
		CMap->Draw();
	}
	else
	{
		map[isEdit][currentMapID].Draw();
	}

	DrawEffect();
	player[0].Draw(0);
	if (PlayNumber == 2)
	{
		player[1].Draw(1);
	}

	//DrawFormatString(0, 0, GetColor(255, 255, 255), "�v���C���[1�̗̑́F%d", player[0].GetHP());
	if (PlayNumber == 2)
	{
		//DrawFormatString(0, 15, GetColor(255, 255, 255), "�v���C���[2�̗̑́F%d", player[1].GetHP());
	}

}

//�v���C�V�[���㏈��
//���g���C���ǂ�����Ԃ�
void ScenePlay::Fin()
{
	bg1.Fin();
	bg2.Fin();
	bg3.Fin();

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

	FinEffect();

	DeleteSoundMem(playBgm_Hndl);
	DeleteSoundMem(HitSe_Hndl);

	for (int Ori_or_Edi = 0; Ori_or_Edi < 2; Ori_or_Edi++)
	{
		for (int mapID = 0; mapID < 5; mapID++)
		{
			map[Ori_or_Edi][mapID].Fin();
		}
	}

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
	//DrawFormatString(0, 300, GetColor(255, 255, 255), "%f", player[0].GetNextPos().y);
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
				//DrawFormatString(0, 400, GetColor(255, 255, 255), "%f", B.x);
				player[index].HandleCollision(index, dirArray, A, B, Asize, Bsize, checkY);
			}
		}
	}
}