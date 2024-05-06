/*
#pragma once
#include <DxLib.h>


#define PLAYER1_PATH		"Data/Img/Player1.png"
#define PLAYER2_PATH		"Data/Img/Player2.png"

#define PLAYER_ANIME_NUM	(18)


#define PLAYER_SIZE			(64)

#define JUMPMAX_NUM			(3)
#define SPEED				(4.0f)

struct Hundle
{
	int Player1Hndl[PLAYER_ANIME_NUM];
	int Player2Hndl[PLAYER_ANIME_NUM];
};

struct Player1
{

};

struct Player2
{

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
	Player1 player1;
	Player2 player2;

	DIR dir;
	bool IsDush;
	int AnimeNum;

	VECTOR Pos;
	VECTOR OldPos;
	float YSpeed;
	float Gravity;
	int JunpCount;

	bool IsReturn;

	int flameCount;


public:

	void Init();

	void Load();

	void Step();

	void Draw();

	void Delete();

	void LimitX_Y();

	void Move();

	void Jump();

	void DushAnime();

	void PulsX(int PosX, float Width);

	void PulsY(int PosY, float Height);
};

*/
