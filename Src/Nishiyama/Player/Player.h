
#pragma once
#include <DxLib.h>


#define PLAYER1_PATH		"Data/Image/Player/Player1.png"
#define PLAYER2_PATH		"Data/Image/Player/Player2.png"

#define BULLETHNDL_PATH		"Data/Image/Player/FireBall.png"

#define PLAYER_ANIME_NUM	(18)


#define PLAYER_SIZE			(64)

#define JUMPMAX_NUM			(3)
#define SPEED				(4.0f)

#define BULLET_MAX_NUM		(3)
#define BULLET_ANIME_NUM	(24)
#define SHOT_INTERVAL		(100)

struct Hundle
{
	int PlayerHndl[2][PLAYER_ANIME_NUM];
	int HP_Flame_Hbndl[2];
	int HP_Hndl[2];
};

//����
enum DIR
{
	IsLeft,
	IsRight,
};

//�v���C���[�̏��
enum ACTIONSTATE
{
	State_Normal,
	State_Dush,
	Stete_Jump,
};

//�e�̌���
enum BULLETDIR
{
	BULLET_LEFT,
	BULLET_RIGHT,
};

class PLAYER
{
protected:
	//�`��Ɏg���ϐ�
	Hundle hundl;
	int AnimeNum;
	

	//���������߂�ϐ�
	DIR dir;
	VECTOR Pos;
	VECTOR OldPos;

	ACTIONSTATE ActionStateID;
	ACTIONSTATE OldActionState;

	//�W�����v�Ɏg���ϐ�
	float YSpeed;
	float Gravity;
	int JunpCount;

	

	//�e�Ɏg���ϐ�
	struct BulletInfo
	{
		VECTOR BulletPos;
		bool IsUse;
		int Isdir;
		int BulletHndl[BULLET_ANIME_NUM];
		bool BulletReturn;
		int BulletAnimeIndex;
		float Speed;
		
	};


	BulletInfo bulletInfo[BULLET_MAX_NUM];

	//����t���O
	bool IsDush;
	bool IsReturn;
	bool IsJump;
	bool IsGround;

	int flameCount;
	int LoopCount;

	//�A�N�V�����{�^��
	int ActionButton[4];

public:

	//������
	void Init(int playerNumber);
	//�f�[�^���[�h
	void Load();
	//�J��Ԃ�����
	void Step();
	//�`��
	void Draw(int playerNumber);
	//�f�[�^�폜
	void Delete();
	//X��Y�̈ړ�����
	void LimitX_Y();
	//�ړ�����
	void Move();
	//�W�����v����
	void Jump();
	//�_�b�V�����̃A�j���؂�ւ�����
	void DushAnime();
	//�W�����v���̃A�j���؂�ւ�����
	void JumpAnime();
	//�����蔻��(X����)
	void PulsX(int PosX, float Width);
	//�����蔻��(Y����)
	void PulsY(int PosY, float Height);

	//�e�̔��ˊԊu����
	void BulletCount();

	//�e�̔��ˏ���
	void BulletShot();

	//�e�̈ړ�
	void MoveBullet();

	//�A�j���[�V�����؂�ւ�����
	void PlayerAnimetion();

	//�v���C���[�̍��W�ݒ�
	void SetPlayerPos(VECTOR Position)
	{
		Pos = Position;
	}
};

