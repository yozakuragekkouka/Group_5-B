
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

//方向
enum DIR
{
	IsLeft,
	IsRight,
};

//プレイヤーの状態
enum ACTIONSTATE
{
	State_Normal,
	State_Dush,
	Stete_Jump,
};

class PLAYER
{
protected:
	//描画に使う変数
	Hundle hundl;
	int AnimeNum;

	//方向を決める変数
	DIR dir;
	VECTOR Pos;
	VECTOR OldPos;

	ACTIONSTATE ActionStateID;


	//ジャンプに使う変数
	float YSpeed;
	float Gravity;
	int JunpCount;

	//判定フラグ
	bool IsDush;
	bool IsReturn;
	bool IsJump;

	int flameCount;

	//アクションボタン
	int ActionButton[3];

public:

	//初期化
	void Init(int playerNumber);
	//データロード
	void Load();
	//繰り返し処理
	void Step();
	//描画
	void Draw(int playerNumber);
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

	//アニメーション切り替え処理
	void PlayerAnimetion();
};

