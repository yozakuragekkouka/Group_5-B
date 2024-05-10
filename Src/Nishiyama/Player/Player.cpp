#include "Player.h"
#include "../Scene/Scene.h"
#include "../Input/Input.h"
#include "../../Common.h"


//������
void PLAYER::Init(int playerNumber)
{
	memset(&hundl, -1, sizeof(Hundle));

	flameCount = 0;
	AnimeNum = 0;

	//playernum�͗V�Ԑl���ŕς���

	//�v���C���[1�̏�����
	dir = IsLeft;
	ActionStateID = State_Normal;


	IsJump = false;
	IsDush = false;
	IsReturn = true;
	IsGround = false;

	for (int i = 0; i < BULLET_MAX_NUM; i++)
	{
		bulletInfo[i].BulletReturn = true;
		bulletInfo[i].IsUse = false;
		bulletInfo[i].BulletPos = { 0.0f, 0.0f, 0.0f };
		bulletInfo[i].Speed = 0.0f;
	}

	YSpeed = 0.0f;
	Gravity = 0.5f;
	JunpCount = 0;

	//�v���C���[�P�̈ړ��L�[
	ActionButton[0] = KEY_INPUT_W;		//�W�����v
	ActionButton[1] = KEY_INPUT_A;		//���ړ�
	ActionButton[2] = KEY_INPUT_D;		//�E�ړ�
	ActionButton[3] = KEY_INPUT_SPACE;	//���˃{�^��
		
	if(playerNumber == 2)
	{
		dir = IsLeft;
		IsReturn = false;

		//�v���C���[2�̈ړ��L�[
		ActionButton[0] = KEY_INPUT_UP;		//�W�����v
		ActionButton[1] = KEY_INPUT_LEFT;	//���ړ�
		ActionButton[2] = KEY_INPUT_RIGHT;	//�E�ړ�
		ActionButton[3] = KEY_INPUT_RSHIFT;	//���˃{�^��
	}

	OldPos = { 0.0f, 0.0f, 0.0f };
}

//�摜�ǂݍ���
void PLAYER::Load()
{
	LoadDivGraph(PLAYER1_PATH, 18, 3, 6, (float)190 / 3, (float)383 / 6, hundl.PlayerHndl[0]);
	LoadDivGraph(PLAYER2_PATH, 18, 3, 6, (float)189 / 3, (float)384 / 6, hundl.PlayerHndl[1]);

	for (int i = 0; i < BULLET_MAX_NUM; i++)
	{
		LoadDivGraph(BULLETHNDL_PATH, 24, 6, 4, 160, 80, bulletInfo[i].BulletHndl);
	}

	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_LOOP_PLAY;
}

//�ʏ폈��
void PLAYER::Step()
{
	flameCount++;
	OldPos = Pos;

	IsGround = false;

	//�ړ�����
	Move();

	//�W�����v����
	if (Input::IsKeyPush(ActionButton[0]))
	{
		//��Ԃ��W�����v�ɂ���
		IsJump = true;
		ActionStateID = Stete_Jump;
		Jump();
	}
	Pos.y += YSpeed;
	YSpeed += Gravity;



	//�e�̔��ˊԊu����
	BulletCount();

	//�e�̔��ˏ���
	if (Input::IsKeyPush(ActionButton[3]))
	{
		BulletShot();
	}
	//�e�̈ړ�
	MoveBullet();

	//�ړ�����
	LimitX_Y();

	//�v���C���[�A�j���؂�ւ�
	PlayerAnimetion();

	OldActionState = ActionStateID;
}

//�`�揈��
void PLAYER::Draw(int playerNumber)
{

	//�v���C���[�̕`��
	DrawRotaGraph((int)Pos.x, (int)Pos.y, 1.0f, 0.0f, hundl.PlayerHndl[playerNumber][AnimeNum], true, IsReturn, false);
	
	//�e�̕`��
	for (int i = 0; i < BULLET_MAX_NUM; i++)
	{
		//�e���g�p���Ȃ�`�悷��
		if (bulletInfo[i].IsUse)
		{
			DrawRotaGraph(bulletInfo[i].BulletPos.x, bulletInfo[i].BulletPos.y,
				1.0, 0.0, bulletInfo[i].BulletHndl[bulletInfo[i].BulletAnimeIndex], true,bulletInfo[i].BulletReturn, false);

			if (flameCount % 4 == 0)
			{
				bulletInfo[i].BulletAnimeIndex++;
				if (bulletInfo[i].BulletAnimeIndex == 6)
				{
					bulletInfo[i].BulletAnimeIndex = 0;
				}
			}
		}
	}
	
	//�f�o�b�N
	DrawFormatString(0, 15, GetColor(255, 255, 255), "�W�����v�J�E���g:%d", JunpCount);
	DrawFormatString(0, 55, GetColor(255, 255, 255), "X���W:%f", Pos.x);
	DrawFormatString(0, 70, GetColor(255, 255, 255), "Y���W:%f", Pos.y);
	DrawBox((int)Pos.x - 32, (int)Pos.y - 32, (int)Pos.x + 32, (int)Pos.y + 32, GetColor(255, 0, 0), false);
}

//�㏈��
void PLAYER::Delete()
{
	
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
	//
	if (Pos.y + PLAYER_SIZE / 2 >= SCREEN_SIZE_Y)
	{
		YSpeed = 0.0f;
		Pos.y = SCREEN_SIZE_Y - PLAYER_SIZE / 2;
		JunpCount = 0;
		IsJump = false;

		if (IsDush == false)
		{
			ActionStateID = State_Normal;
		}

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
	if (Input::IsKeyKeep(ActionButton[2]))
	{
		if (IsJump == false)
		{
			ActionStateID = State_Dush;
		}
		IsDush = true;
		dir = IsRight;
		IsReturn = true;
		Pos.x += SPEED;
	}
	else if (Input::IsKeyKeep(ActionButton[1]))
	{	
		if (IsJump == false)
		{
			ActionStateID = State_Dush;
		}		
		IsDush = true;
		dir = IsLeft;
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
		YSpeed = -15.0f;
		JunpCount++;
	}
}

//�_�b�V���A�j��
void PLAYER::DushAnime()
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

void PLAYER::JumpAnime()
{
	//�~����
	if (YSpeed > 0.0f)
	{
		AnimeNum = 7;
	}
	//�㏸��
	else if (YSpeed < 0.0f)
	{
		AnimeNum = 6;
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
		IsJump = false;

	}
	//����������̓����蔻��
	else if (YSpeed < 0.0f)
	{
		float puls = 0.0f;
		puls = (PosY + Height) - (Pos.y - 32.0f);
		Pos.y += puls;
		YSpeed = -0.5f;
	}
}


//�A�j���[�V�����؂�ւ�����
void PLAYER::PlayerAnimetion()
{
	switch (ActionStateID)
	{
	case State_Normal:
		if (ActionStateID != OldActionState)
		{
			AnimeNum = 15;
		}

		//�ҋ@���[�V����
		if (flameCount % 8 == 0)
		{
			AnimeNum++;
			if (AnimeNum > 17)
			{
				AnimeNum = 14;
			}
		}
		
		break;
	case State_Dush:
		if (ActionStateID != OldActionState)
		{
			AnimeNum = 0;
		}
		if (IsJump == false)
		{
			//�_�b�V��
			DushAnime();
		}

		break;
	case Stete_Jump:
		//�W�����v
		if (IsJump == true)
		{
			JumpAnime();
		}

		break;

	case State_Atack:
		//�U����


	default:
		break;
	}
}

//�e�̔��ˊԊu����
void PLAYER::BulletCount()
{
	LoopCount++;
	if (LoopCount > SHOT_INTERVAL)
	{
		LoopCount = SHOT_INTERVAL;
	}
}

//�e�̔��ˏ���
void PLAYER::BulletShot()
{
	for (int i = 0; i < BULLET_MAX_NUM; i++)
	{
		if (!bulletInfo[i].IsUse)
		{
			bulletInfo[i].BulletAnimeIndex = 0;
			bulletInfo[i].IsUse = true;

			switch (dir)
			{
			case IsLeft:
				bulletInfo[i].BulletPos.x = Pos.x + 5.0f;
				bulletInfo[i].BulletPos.y = Pos.y;
				bulletInfo[i].BulletPos.z = 0.0f;

				bulletInfo[i].Speed = -5.0f;
				bulletInfo[i].Isdir = IsLeft;
				bulletInfo[i].BulletReturn = true;

				break;

			case IsRight:
				bulletInfo[i].BulletPos.x = Pos.x - 5.0f;
				bulletInfo[i].BulletPos.y = Pos.y;
				bulletInfo[i].BulletPos.z = 0.0f;

				bulletInfo[i].Speed = 5.0f;
				bulletInfo[i].Isdir = IsRight;
				bulletInfo[i].BulletReturn = false;
				break;

			default:
				break;
			}

			//�ʔ��ˊԊu��������
			LoopCount = 0;
			break;
		}
	}
}

//�e�̈ړ�
void PLAYER::MoveBullet()
{
	for (int i = 0; i < BULLET_MAX_NUM; i++)
	{
		if(bulletInfo[i].IsUse == true)
		{
			bulletInfo[i].BulletPos.x += bulletInfo[i].Speed;

			//��ʊO�ɏo����t���O��܂�
			if (bulletInfo[i].BulletPos.x < 0 || bulletInfo[i].BulletPos.x > SCREEN_SIZE_X)
			{
				bulletInfo[i].IsUse = false;
			}
		}
		
	}
}


//�A�C�e�����E������
void PLAYER::GetItem(VECTOR PlayerPos, VECTOR ItemPos)
{
	//�����蔻����Ƃ�

	//����������A�C�e�����v���C���[�̘r�t�߂ɔz�u����

	//�擾�t���O���I���ɂ���
	IsGet = true;
}

//�A�C�e���𓊂��鏈��
void PLAYER::ThrowItem(VECTOR PlayerPos, VECTOR ItemPos)
{
	//�����t���O���I���Ȃ瓊����
	if (IsGet == true)
	{

	}
}