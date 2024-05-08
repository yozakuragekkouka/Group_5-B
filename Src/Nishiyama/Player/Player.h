
#pragma once
#include <DxLib.h>


#define PLAYER1_PATH		"Data/Image/Player/Player1.png"
#define PLAYER2_PATH		"Data/Image/Player/Player2.png"

#define PLAYER_ANIME_NUM	(18)


#define PLAYER_SIZE			(64)

#define JUMPMAX_NUM			(3)
#define SPEED				(4.0f)

struct Hundle
{
	int Player1Hndl[PLAYER_ANIME_NUM];
	int Player2Hndl[PLAYER_ANIME_NUM];
	int PlayerHndl[2][PLAYER_ANIME_NUM];
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


	//�W�����v�Ɏg���ϐ�
	float YSpeed;
	float Gravity;
	int JunpCount;

	//����t���O
	bool IsDush;
	bool IsReturn;
	bool IsJump;

	int flameCount;

	//�A�N�V�����{�^��
	int ActionButton[3];

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

	//�A�j���[�V�����؂�ւ�����
	void PlayerAnimetion();
};

