
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

	//初期化
	void Init(/*int playerNumber*/);
	//データロード
	void Load();
	//繰り返し処理
	void Step();
	//描画
	void Draw();
	//データ削除
	void Delete();
	//XとYの移動制限
	void LimitX_Y();
	//移動処理
	void Move();
	//ジャンプ処理
	void Jump();
	//ダッシュ時のアニメ切り替え処理
	void DushAnime();
	//ジャンプ時のアニメ切り替え処理
	void JumpAnime();
	//当たり判定(X方向)
	void PulsX(int PosX, float Width);
	//当たり判定(Y方向)
	void PulsY(int PosY, float Height);
};

