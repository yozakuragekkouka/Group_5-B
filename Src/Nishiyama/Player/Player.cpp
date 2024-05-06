/*
#include "../Scene.h"
#include "Player.h"
#include "../Input/Input.h"
#include "../Collision/Collision.h"
#include "../Common.h"

//������
void PLAYER::Init()
{
	memset(&hundl, -1, sizeof(Hundle));
	flameCount = 0;

	AnimeNum = 0;

	dir = IsLeft;
	IsDush = false;
	IsReturn = true;
	Pos = { 32.0f, 0.0f, 0.0f };
	YSpeed = 0.0f;
	Gravity = 0.5f;
	JunpCount = 0;

	player1.dir = IsLeft;
	player1.IsDush = false;
	player1.IsReturn = true;
	player1.Pos = { 32.0f, 32.0f, 0.0f };
	player1.YSpeed = 0.5f;
	player1.Gravity = 0.5f;
	player1.JunpCount = 0;

	player2.dir = IsRight;
	player2.IsDush = false;
	player2.IsReturn = false;
	player2.Pos = { 1248.0f, 32.0f, 0.0f };
	player2.YSpeed = 0.5f;
	player2.Gravity = 0.5f;
	player2.JunpCount = 0;
}

//�摜�ǂݍ���
void PLAYER::Load()
{
	LoadDivGraph(PLAYER1_PATH, 18, 3, 6, (float)190 / 3, (float)383 / 6, hundl.Player1Hndl);
	LoadDivGraph(PLAYER2_PATH, 18, 3, 6, (float)189 / 3, (float)384 / 6, hundl.Player2Hndl);

	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//�ʏ폈��
void PLAYER::Step()
{

	flameCount++;

	//�ړ�����
	Move();
	//�ړ��A�j���؂�ւ�����
	DushAnime();

	//�W�����v����
	if (IsKeyPush(KEY_INPUT_SPACE))
	{
		Jump();
	}
	Pos.y += YSpeed;
	YSpeed += Gravity;


	//�ړ�����
	LimitX_Y();
}

//�`�揈��
void PLAYER::Draw()
{
	//�v���C���[�̕`��
	DrawRotaGraph((int)Pos.x, (int)Pos.y, 1.0f, 0.0f, hundl.Player1Hndl[AnimeNum], true, IsReturn, false);

	
	//�f�o�b�N
	DrawFormatString(0, 15, GetColor(255, 255, 255), "�W�����v�J�E���g:%d", JunpCount);
	DrawFormatString(0, 55, GetColor(255, 255, 255), "X���W:%f", Pos.x);
	DrawFormatString(0, 70, GetColor(255, 255, 255), "Y���W:%f", Pos.y);
	DrawBox(Pos.x - 32, Pos.y - 32, Pos.x + 32, Pos.y + 32, GetColor(255, 0, 0), false);
}

//�㏈��
void PLAYER::Delete()
{
	memset(&hundl, -1, sizeof(Hundle));
}

//�ړ�����
void PLAYER::LimitX_Y()
{
	//X���W����
	if (Pos.x + PLAYER_SIZE / 2 >= SCREEN_SIZE_X)
	{
		Pos.x = SCREEN_SIZE_X - PLAYER_SIZE / 2;
	}
	else if (Pos.x - PLAYER_SIZE / 2 < 0.0f)
	{
		Pos.x = PLAYER_SIZE / 2;
	}

	//Y���W����
	if (Pos.y + PLAYER_SIZE / 2 >= SCREEN_SIZE_Y)
	{
		YSpeed = 0.0f;
		Pos.y = SCREEN_SIZE_Y - PLAYER_SIZE / 2;
		JunpCount = 0;
	}
	else if (Pos.y - PLAYER_SIZE / 2 < 0.0f)
	{
		Pos.y = PLAYER_SIZE / 2;
		YSpeed = 0.0f;
	}
}

//�ړ�����
void PLAYER::Move()
{
	if (IsKeyKeep(KEY_INPUT_D))
	{
		dir = IsLeft;
		IsDush = true;
		IsReturn = true;
		Pos.x += SPEED;

	}
	else if (IsKeyKeep(KEY_INPUT_A))
	{
		dir = IsRight;
		IsDush = true;
		IsReturn = false;
		Pos.x -= SPEED;
	}
	else
	{
		IsDush = false;
	}
}

//�W�����v����
void PLAYER::Jump()
{
	if (JunpCount < JUMPMAX_NUM)
	{
		YSpeed = -10.0f;
		JunpCount++;
	}
}

//�_�b�V���A�j��
void PLAYER::DushAnime()
{
	if (IsDush == true)
	{
		if (flameCount % 4 == 0)
		{
			AnimeNum++;
			if (AnimeNum == 6)
			{
				AnimeNum = 0;
			}
		}
	}
}

//X�̓����蔻��
void PLAYER::PulsX(int PosX, float Width)
{
	//������̓����蔻��
	if (dir == IsLeft)
	{
		float puls = 0.0f;
		puls = (Pos.x + 32.0f) - PosX;
		Pos.x -= puls;
	}
	//�E����̓����蔻��
	else if (dir == IsRight)
	{
		float puls = 0.0f;
		puls = (PosX + Width) - (Pos.x - 32.0f);
		Pos.x += puls;
	}
}
//Y�̓����蔻��
void PLAYER::PulsY(int PosY, float Height)
{
	//���������̓����蔻��
	if (YSpeed > 0.0f)
	{
		float puls = 0.0f;
		puls = (Pos.y + 32.0f) - PosY;
		Pos.y -= puls;
		YSpeed = 0.0f;
		JunpCount = 0;
	}
	//����������̓����蔻��
	else if (YSpeed < 0.0f)
	{
		float puls = 0.0f;
		puls = (PosY + Height) - (Pos.y - 32.0f);
		Pos.y += puls;
		YSpeed = 0.0f;
	}
}

*/