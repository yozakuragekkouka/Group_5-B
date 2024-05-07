
#pragma once
#include <DxLib.h>


#define PLAYER1_PATH		"Data/Image/Player/Player1.png"
//#define PLAYER2_PATH		"Data/Image/Player/Player2.png"

#define PLAYER_ANIME_NUM	(18)


#define PLAYER_SIZE			(64)

#define JUMPMAX_NUM			(3)
#define SPEED				(4.0f)

struct Hundle
{
	int Player1Hndl[PLAYER_ANIME_NUM];
	int Player2Hndl[PLAYER_ANIME_NUM];
};

enum DIR
{
	IsLeft,
	IsRight,
};

class PLAYER
{
private:
	Hundle hundl;

	DIR dir;
	bool IsDush;
	int AnimeNum;

	VECTOR Pos;
	VECTOR OldPos;
	float YSpeed;
	float Gravity;
	int JunpCount;

	bool IsReturn;
	bool IsJump;

	int flameCount;


public:

	//������
	void Init(/*int playerNumber*/);
	//�f�[�^���[�h
	void Load();
	//�J��Ԃ�����
	void Step();
	//�`��
	void Draw();
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
};

