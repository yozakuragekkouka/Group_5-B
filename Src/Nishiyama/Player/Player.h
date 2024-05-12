
#pragma once
#include <DxLib.h>


#define PLAYER1_PATH		"Data/Image/Player/Player1.png"
#define PLAYER2_PATH		"Data/Image/Player/Player2.png"

#define PLAYER_MAX_LIFE		(100)

#define BULLETHNDL_PATH		"Data/Image/Player/FireBall.png"

#define PLAYER_ANIME_NUM	(18)

#define JUMPMAX_NUM			(2)
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
	State_Atack,
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
	VECTOR PlayerSize;
	
	//�v���C���[�̃��C�t
	int Life;
	int DamageCoolTime;

	//�ߐڍU���̍U����
	int closeAttackDm;

	//���������߂�ϐ�
	DIR dir;
	VECTOR Pos;
	VECTOR Pos1;	//���[�����_�ɂ��邽�߂����̕ϐ�
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
		VECTOR BulletPos1;	//���[�����_�ɂ��邽�߂����̕ϐ�
		bool IsUse;
		int Isdir;
		int BulletHndl[BULLET_ANIME_NUM];
		bool BulletReturn;
		int BulletAnimeIndex;
		float Speed;
		
		
	};
	int BulletDamege;
	VECTOR BulletSize;		//�e�摜�̃T�C�Y
	BulletInfo bulletInfo[BULLET_MAX_NUM];


	//������A�C�e��
	bool IsGet;


	//����t���O
	bool IsDush;
	bool IsReturn;
	bool IsJump;
	bool IsGround;

	int flameCount;
	int LoopCount;

	//�A�N�V�����{�^��
	int ActionButton[6];

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

	//�A�C�e�����E������
	void GetItem(VECTOR ItemPos, VECTOR ItemSize);

	//�A�C�e���𓊂��鏈��
	void ThrowItem(VECTOR ItemPos);

	//�A�j���[�V�����؂�ւ�����
	void PlayerAnimetion();

	//�e�̍ő吔�擾
	int GetBulletMaxNum()
	{
		return BULLET_MAX_NUM;
	}

	//�v���C���[�̍��W�ݒ�
	void SetPlayerPos(VECTOR Position)
	{
		Pos = Position;
	}

	//�v���C���[�̍��W�擾
	VECTOR GetPlayerPos()
	{
		return Pos1;
	}

	VECTOR GetPlayerSize()
	{
		return PlayerSize;
	}

	//�e�̍��W�擾
	VECTOR GetBulletPos()
	{
		for (int i = 0; i < BULLET_MAX_NUM; i++)
		{
			return bulletInfo[i].BulletPos1;
		}
	}

	//�e�̎g�p�t���O�擾
	bool GetBulletIsUse()
	{
		for (int i = 0; i < BULLET_MAX_NUM; i++)
		{
			return bulletInfo[i].IsUse;
		}
	}

	//�e�̎g�p�t���O�ݒ�
	void SetBulletIsUse()
	{
		for (int i = 0; i < BULLET_MAX_NUM; i++)
		{
			bulletInfo[i].IsUse = false;
		}	
	}

	//�e�̉��T�C�Y�擾
	VECTOR GetBulletSize()
	{
		return BulletSize;
	}

	//�e�̃_���[�W�擾
	int GetBulletDamege()
	{
		return BulletDamege;
	}

	//�v���C���[��HP�擾
	int GetHP()
	{
		return Life;
	}

	int SetLife(int Hp)
	{
		return Life = Hp;
	}

	//�v���C���[��HP�ݒ�
	void Damege(int damege)
	{
		Life -= damege;
	}

	//�_���[�W�N�[���^�C���擾
	int GetDamegeCoolTime()
	{
		return DamageCoolTime;
	}

	//�_���[�W�N�[���^�C���ݒ�
	void SetDamageCoolTime()
	{
		DamageCoolTime = 0;
	}

	//�_���[�W�N�[���^�C������
	void AddDamageCoolTime(int AddTime)
	{
		DamageCoolTime += AddTime;
	}
};

