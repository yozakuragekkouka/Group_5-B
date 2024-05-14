
#pragma once
#include <DxLib.h>


#define PLAYER1_PATH		"Data/Image/Player/Player1.png"
#define PLAYER2_PATH		"Data/Image/Player/Player2.png"

#define PLAYER_MAX_LIFE		(100)

#define BULLETHNDL_PATH		"Data/Image/Player/FireBall.png"

#define PLAYER_ANIME_NUM	(18)

#define JUMPMAX_NUM			(2)
#define SPEED				(4.0f)

#define BULLET_MAX_NUM		(2)
#define BULLET_ANIME_NUM	(24)
#define SHOT_INTERVAL		(20)

extern bool IsPlayer1Win;
extern bool	IsPlayer2Win;
extern bool IsCPUWin;

struct Hundle
{
	int PlayerHndl[2][PLAYER_ANIME_NUM];
	int HP_Hndl[10];
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
	VECTOR LifePos;
	
	//�v���C���[�̃��C�t
	int Life;
	int DamageCoolTime;

	//���������߂�ϐ�
	DIR dir;
	VECTOR Pos;
	VECTOR NextPos; //���̃t���[���̃v���C���[���W
	VECTOR Pos1;	//���[�����_�ɂ��邽�߂����̕ϐ�
	VECTOR OldPos;

	ACTIONSTATE ActionStateID;
	ACTIONSTATE OldActionState;

	//�W�����v�Ɏg���ϐ�
	float YSpeed;
	float Gravity;
	int JumpCount;

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
	bool IsAttack;

	int flameCount;
	int LoopCount;

	//�A�N�V�����{�^��
	int ActionButton[5];

	//�ߐڍU���Ɏg���ϐ�
	int PunchPosX;
	int PunchPosY;


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

	//�A�j���[�V�����֘A---------------------------
	//�A�j���[�V�����؂�ւ�����
	void PlayerAnimetion();
	//�_�b�V�����̃A�j���؂�ւ�����
	void DushAnime();
	//�W�����v���̃A�j���؂�ւ�����
	void JumpAnime();
	//---------------------------------------------


	//�e�֘A�֐�-----------------------------------
	//�e�̍ő吔�擾
	int GetBulletMaxNum()
	{
		return BULLET_MAX_NUM;
	}
	//�e�̔��ˊԊu����
	void BulletCount();

	//�e�̔��ˏ���
	void BulletShot();

	//�e�̈ړ�
	void MoveBullet();

	//�e�̍��W�擾
	VECTOR GetBulletPos(int i)
	{
		return bulletInfo[i].BulletPos1;
	}

	//�e�̎g�p�t���O�擾
	bool GetBulletIsUse(int i)
	{
		return bulletInfo[i].IsUse;
	}

	//�e�̎g�p�t���O�ݒ�
	void SetBulletIsUse(int i)
	{
		bulletInfo[i].IsUse = false;
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
	//--------------------------------------------

	//HP�֘A--------------------------------------
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
	//---------------------------------------------

	//�A�C�e�����E������
	void GetItem(VECTOR ItemPos, VECTOR ItemSize);

	//�A�C�e���𓊂��鏈��
	void ThrowItem(VECTOR ItemPos);



	//�����蔻��(X����)
	void PulsX(int PosX, float Width);
	//�����蔻��(Y����)
	void PulsY(int PosY, float Height);
	

	//�v���C���[�̍��W�ݒ�
	void SetPlayerPos(VECTOR Position)
	{
		NextPos = Position;
	}
	//X���W�ݒ�
	void SetPlayerPosX(float Position)
	{
		NextPos.x = Position;
	}
	//Y���W�ݒ�
	void SetPlayerPosY(float Position)
	{
		NextPos.y = Position;
	}
	//�v���C���[�̍��W�擾(���_�����S���W)
	VECTOR GetPlayerPos()
	{
		return Pos;
	}

	//�{�^���̎擾
	int GetBottan()
	{
		return ActionButton[4];
	}
	//�ߋ����U�����W�擾
	int GetPunchPosX()
	{
		return PunchPosX;
	}
	//�ߋ����U�����W�擾
	int GetPunchPosY()
	{
		return PunchPosY;
	}

	//�v���C���[�̃T�C�Y�擾
	VECTOR GetPlayerSize()
	{
		return PlayerSize;
	}
	
	DIR GetPlayerdir()
	{
		return dir;
	}

	//����
	//���̃t���[���̃v���[���[�̈ʒu���擾
	VECTOR GetNextPos()
	{
		return NextPos;
	}

	//�I�u�W�F�N�g�̏�ɂ��邩���擾
	bool GetIsGround()
	{
		return IsGround;
	}

	//�v���C���[�̐i��ł���������`�F�b�N
	void GetMoveDirection(bool* _dirArray);

	//�ʏ�̃v���C���[���W���擾(���_��������W)
	VECTOR GetNormalPlayerPos()
	{
		return Pos;
	}

	//�}�b�v�����蔻��
	void HandleCollision(int index, bool dirArray[],
		VECTOR A, VECTOR B, VECTOR Asize, VECTOR Bsize, bool checkY);

	//�����̕`��
	void DrawNumber(int Hndl[10], int Score, int X, int Y);
};

