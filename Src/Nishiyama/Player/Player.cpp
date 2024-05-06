/*
#include "../Scene.h"
#include "Player.h"
#include "../Input/Input.h"
#include "../Collision/Collision.h"
#include "../Common.h"

//初期化
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

//画像読み込み
void PLAYER::Load()
{
	LoadDivGraph(PLAYER1_PATH, 18, 3, 6, (float)190 / 3, (float)383 / 6, hundl.Player1Hndl);
	LoadDivGraph(PLAYER2_PATH, 18, 3, 6, (float)189 / 3, (float)384 / 6, hundl.Player2Hndl);

	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//通常処理
void PLAYER::Step()
{

	flameCount++;

	//移動処理
	Move();
	//移動アニメ切り替え処理
	DushAnime();

	//ジャンプ処理
	if (IsKeyPush(KEY_INPUT_SPACE))
	{
		Jump();
	}
	Pos.y += YSpeed;
	YSpeed += Gravity;


	//移動制限
	LimitX_Y();
}

//描画処理
void PLAYER::Draw()
{
	//プレイヤーの描画
	DrawRotaGraph((int)Pos.x, (int)Pos.y, 1.0f, 0.0f, hundl.Player1Hndl[AnimeNum], true, IsReturn, false);

	
	//デバック
	DrawFormatString(0, 15, GetColor(255, 255, 255), "ジャンプカウント:%d", JunpCount);
	DrawFormatString(0, 55, GetColor(255, 255, 255), "X座標:%f", Pos.x);
	DrawFormatString(0, 70, GetColor(255, 255, 255), "Y座標:%f", Pos.y);
	DrawBox(Pos.x - 32, Pos.y - 32, Pos.x + 32, Pos.y + 32, GetColor(255, 0, 0), false);
}

//後処理
void PLAYER::Delete()
{
	memset(&hundl, -1, sizeof(Hundle));
}

//移動制限
void PLAYER::LimitX_Y()
{
	//X座標制限
	if (Pos.x + PLAYER_SIZE / 2 >= SCREEN_SIZE_X)
	{
		Pos.x = SCREEN_SIZE_X - PLAYER_SIZE / 2;
	}
	else if (Pos.x - PLAYER_SIZE / 2 < 0.0f)
	{
		Pos.x = PLAYER_SIZE / 2;
	}

	//Y座標制限
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

//移動処理
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

//ジャンプ処理
void PLAYER::Jump()
{
	if (JunpCount < JUMPMAX_NUM)
	{
		YSpeed = -10.0f;
		JunpCount++;
	}
}

//ダッシュアニメ
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

//Xの当たり判定
void PLAYER::PulsX(int PosX, float Width)
{
	//左からの当たり判定
	if (dir == IsLeft)
	{
		float puls = 0.0f;
		puls = (Pos.x + 32.0f) - PosX;
		Pos.x -= puls;
	}
	//右からの当たり判定
	else if (dir == IsRight)
	{
		float puls = 0.0f;
		puls = (PosX + Width) - (Pos.x - 32.0f);
		Pos.x += puls;
	}
}
//Yの当たり判定
void PLAYER::PulsY(int PosY, float Height)
{
	//上方向からの当たり判定
	if (YSpeed > 0.0f)
	{
		float puls = 0.0f;
		puls = (Pos.y + 32.0f) - PosY;
		Pos.y -= puls;
		YSpeed = 0.0f;
		JunpCount = 0;
	}
	//下方向からの当たり判定
	else if (YSpeed < 0.0f)
	{
		float puls = 0.0f;
		puls = (PosY + Height) - (Pos.y - 32.0f);
		Pos.y += puls;
		YSpeed = 0.0f;
	}
}

*/