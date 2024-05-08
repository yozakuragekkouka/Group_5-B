#include "Player.h"
#include "../Scene/Scene.h"
#include "../Input/Input.h"
#include "../../Common.h"


//初期化
void PLAYER::Init(int playerNumber)
{
	memset(&hundl, -1, sizeof(Hundle));
	flameCount = 0;
	AnimeNum = 0;

	//playernumは遊ぶ人数で変える

	//プレイヤー1の初期化
	if (playerNumber == 1)
	{
		dir = IsRight;
		ActionStateID = State_Normal;

		Pos = { 32.0f, 500.0f, 0.0f };
		

		IsJump = false;
		IsDush = false;
		IsReturn = true;

		
		ActionButton[0] = KEY_INPUT_W;		//ジャンプ
		ActionButton[1] = KEY_INPUT_A;		//左移動
		ActionButton[2] = KEY_INPUT_D;		//右移動
	}
	else
	{
		dir = IsLeft;
		ActionStateID = State_Normal;


		Pos = { 1248.0f, 500.0f, 0.0f };
		

		IsJump = false;
		IsDush = false;
		IsReturn = false;

		ActionButton[0] = KEY_INPUT_U;		//ジャンプ
		ActionButton[1] = KEY_INPUT_H;		//左移動
		ActionButton[2] = KEY_INPUT_K;		//右移動
	}

	dir = IsLeft;
	IsDush = false;
	IsReturn = true;
	Pos = { 32.0f, 0.0f, 0.0f };
	YSpeed = 0.0f;
	Gravity = 0.5f;
	JunpCount = 0;

	IsJump = false;
}

//画像読み込み
void PLAYER::Load()
{
	LoadDivGraph(PLAYER1_PATH, 18, 3, 6, (float)190 / 3, (float)383 / 6, hundl.Player1Hndl);
	/*LoadDivGraph(PLAYER2_PATH, 18, 3, 6, (float)189 / 3, (float)384 / 6, hundl.Player2Hndl);*/


	LoadDivGraph(PLAYER1_PATH, 18, 3, 6, (float)190 / 3, (float)383 / 6, hundl.PlayerHndl[0]);
	LoadDivGraph(PLAYER2_PATH, 18, 3, 6, (float)189 / 3, (float)384 / 6, hundl.PlayerHndl[1]);

	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_LOOP_PLAY;
}

//通常処理
void PLAYER::Step()
{

	flameCount++;

	//移動処理
	Move();
	//移動アニメ切り替え処理
	DushAnime();
	//ジャンプアニメ切り替え処理
	if (IsJump)
	{
		JumpAnime();
	}

	//ジャンプ処理
	if (Input::IsKeyPush(ActionButton[0]))
	{
		IsJump = true;
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
	DrawRotaGraph((int)Pos.x, (int)Pos.y, 1.0f, 0.0f, hundl.PlayerHndl[dir][AnimeNum], true, IsReturn, false);
	
	//デバック
	DrawFormatString(0, 15, GetColor(255, 255, 255), "ジャンプカウント:%d", JunpCount);
	DrawFormatString(0, 55, GetColor(255, 255, 255), "X座標:%f", Pos.x);
	DrawFormatString(0, 70, GetColor(255, 255, 255), "Y座標:%f", Pos.y);
	DrawBox((int)Pos.x - 32, (int)Pos.y - 32, (int)Pos.x + 32, (int)Pos.y + 32, GetColor(255, 0, 0), false);
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
	if (Input::IsKeyKeep(ActionButton[2]))
	{
		dir = IsLeft;
		IsDush = true;
		IsReturn = true;
		Pos.x += SPEED;

	}
	else if (Input::IsKeyKeep(ActionButton[1]))
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
	if (IsDush == true && IsJump == false)
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

void PLAYER::JumpAnime()
{
	//降下中
	if (YSpeed > 0.0f)
	{
		AnimeNum = 7;
	}
	//上昇中
	else if (YSpeed < 0.0f)
	{
		AnimeNum = 6;
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
		YSpeed = -0.5f;
	}
}
