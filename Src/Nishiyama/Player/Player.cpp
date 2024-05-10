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
	dir = IsLeft;
	ActionStateID = State_Normal;


	IsJump = false;
	IsDush = false;
	IsReturn = true;
	IsGround = false;

	for (int i = 0; i < BULLET_MAX_NUM; i++)
	{
		bulletInfo[i].BulletReturn = true;
		bulletInfo[i].IsUse = false;
		bulletInfo[i].BulletPos = { 0.0f, 0.0f, 0.0f };
		bulletInfo[i].Speed = 0.0f;
	}

	YSpeed = 0.0f;
	Gravity = 0.5f;
	JunpCount = 0;

	//プレイヤー１の移動キー
	ActionButton[0] = KEY_INPUT_W;		//ジャンプ
	ActionButton[1] = KEY_INPUT_A;		//左移動
	ActionButton[2] = KEY_INPUT_D;		//右移動
	ActionButton[3] = KEY_INPUT_SPACE;	//発射ボタン
		
	if(playerNumber == 2)
	{
		dir = IsLeft;
		IsReturn = false;

		//プレイヤー2の移動キー
		ActionButton[0] = KEY_INPUT_UP;		//ジャンプ
		ActionButton[1] = KEY_INPUT_LEFT;	//左移動
		ActionButton[2] = KEY_INPUT_RIGHT;	//右移動
		ActionButton[3] = KEY_INPUT_RSHIFT;	//発射ボタン
	}

	OldPos = { 0.0f, 0.0f, 0.0f };
}

//画像読み込み
void PLAYER::Load()
{
	LoadDivGraph(PLAYER1_PATH, 18, 3, 6, (float)190 / 3, (float)383 / 6, hundl.PlayerHndl[0]);
	LoadDivGraph(PLAYER2_PATH, 18, 3, 6, (float)189 / 3, (float)384 / 6, hundl.PlayerHndl[1]);

	for (int i = 0; i < BULLET_MAX_NUM; i++)
	{
		LoadDivGraph(BULLETHNDL_PATH, 24, 6, 4, 160, 80, bulletInfo[i].BulletHndl);
	}

	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_LOOP_PLAY;
}

//通常処理
void PLAYER::Step()
{
	flameCount++;
	OldPos = Pos;

	IsGround = false;

	//移動処理
	Move();

	//ジャンプ処理
	if (Input::IsKeyPush(ActionButton[0]))
	{
		//状態をジャンプにする
		IsJump = true;
		ActionStateID = Stete_Jump;
		Jump();
	}
	Pos.y += YSpeed;
	YSpeed += Gravity;



	//弾の発射間隔調整
	BulletCount();

	//弾の発射処理
	if (Input::IsKeyPush(ActionButton[3]))
	{
		BulletShot();
	}
	//弾の移動
	MoveBullet();

	//移動制限
	LimitX_Y();

	//プレイヤーアニメ切り替え
	PlayerAnimetion();

	OldActionState = ActionStateID;
}

//描画処理
void PLAYER::Draw(int playerNumber)
{

	//プレイヤーの描画
	DrawRotaGraph((int)Pos.x, (int)Pos.y, 1.0f, 0.0f, hundl.PlayerHndl[playerNumber][AnimeNum], true, IsReturn, false);
	
	//弾の描画
	for (int i = 0; i < BULLET_MAX_NUM; i++)
	{
		//弾が使用中なら描画する
		if (bulletInfo[i].IsUse)
		{
			DrawRotaGraph(bulletInfo[i].BulletPos.x, bulletInfo[i].BulletPos.y,
				1.0, 0.0, bulletInfo[i].BulletHndl[bulletInfo[i].BulletAnimeIndex], true,bulletInfo[i].BulletReturn, false);

			if (flameCount % 4 == 0)
			{
				bulletInfo[i].BulletAnimeIndex++;
				if (bulletInfo[i].BulletAnimeIndex == 6)
				{
					bulletInfo[i].BulletAnimeIndex = 0;
				}
			}
		}
	}
	
	//デバック
	DrawFormatString(0, 15, GetColor(255, 255, 255), "ジャンプカウント:%d", JunpCount);
	DrawFormatString(0, 55, GetColor(255, 255, 255), "X座標:%f", Pos.x);
	DrawFormatString(0, 70, GetColor(255, 255, 255), "Y座標:%f", Pos.y);
	DrawBox((int)Pos.x - 32, (int)Pos.y - 32, (int)Pos.x + 32, (int)Pos.y + 32, GetColor(255, 0, 0), false);
}

//後処理
void PLAYER::Delete()
{
	
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
	//
	if (Pos.y + PLAYER_SIZE / 2 >= SCREEN_SIZE_Y)
	{
		YSpeed = 0.0f;
		Pos.y = SCREEN_SIZE_Y - PLAYER_SIZE / 2;
		JunpCount = 0;
		IsJump = false;

		if (IsDush == false)
		{
			ActionStateID = State_Normal;
		}

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
		if (IsJump == false)
		{
			ActionStateID = State_Dush;
		}
		IsDush = true;
		dir = IsRight;
		IsReturn = true;
		Pos.x += SPEED;
	}
	else if (Input::IsKeyKeep(ActionButton[1]))
	{	
		if (IsJump == false)
		{
			ActionStateID = State_Dush;
		}		
		IsDush = true;
		dir = IsLeft;
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
		YSpeed = -15.0f;
		JunpCount++;
	}
}

//ダッシュアニメ
void PLAYER::DushAnime()
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
		IsJump = false;

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


//アニメーション切り替え処理
void PLAYER::PlayerAnimetion()
{
	switch (ActionStateID)
	{
	case State_Normal:
		if (ActionStateID != OldActionState)
		{
			AnimeNum = 15;
		}

		//待機モーション
		if (flameCount % 8 == 0)
		{
			AnimeNum++;
			if (AnimeNum > 17)
			{
				AnimeNum = 14;
			}
		}
		
		break;
	case State_Dush:
		if (ActionStateID != OldActionState)
		{
			AnimeNum = 0;
		}
		if (IsJump == false)
		{
			//ダッシュ
			DushAnime();
		}

		break;
	case Stete_Jump:
		//ジャンプ
		if (IsJump == true)
		{
			JumpAnime();
		}

		break;

	case State_Atack:
		//攻撃中


	default:
		break;
	}
}

//弾の発射間隔調整
void PLAYER::BulletCount()
{
	LoopCount++;
	if (LoopCount > SHOT_INTERVAL)
	{
		LoopCount = SHOT_INTERVAL;
	}
}

//弾の発射処理
void PLAYER::BulletShot()
{
	for (int i = 0; i < BULLET_MAX_NUM; i++)
	{
		if (!bulletInfo[i].IsUse)
		{
			bulletInfo[i].BulletAnimeIndex = 0;
			bulletInfo[i].IsUse = true;

			switch (dir)
			{
			case IsLeft:
				bulletInfo[i].BulletPos.x = Pos.x + 5.0f;
				bulletInfo[i].BulletPos.y = Pos.y;
				bulletInfo[i].BulletPos.z = 0.0f;

				bulletInfo[i].Speed = -5.0f;
				bulletInfo[i].Isdir = IsLeft;
				bulletInfo[i].BulletReturn = true;

				break;

			case IsRight:
				bulletInfo[i].BulletPos.x = Pos.x - 5.0f;
				bulletInfo[i].BulletPos.y = Pos.y;
				bulletInfo[i].BulletPos.z = 0.0f;

				bulletInfo[i].Speed = 5.0f;
				bulletInfo[i].Isdir = IsRight;
				bulletInfo[i].BulletReturn = false;
				break;

			default:
				break;
			}

			//玉発射間隔を初期化
			LoopCount = 0;
			break;
		}
	}
}

//弾の移動
void PLAYER::MoveBullet()
{
	for (int i = 0; i < BULLET_MAX_NUM; i++)
	{
		if(bulletInfo[i].IsUse == true)
		{
			bulletInfo[i].BulletPos.x += bulletInfo[i].Speed;

			//画面外に出たらフラグを折る
			if (bulletInfo[i].BulletPos.x < 0 || bulletInfo[i].BulletPos.x > SCREEN_SIZE_X)
			{
				bulletInfo[i].IsUse = false;
			}
		}
		
	}
}


//アイテムを拾う処理
void PLAYER::GetItem(VECTOR PlayerPos, VECTOR ItemPos)
{
	//当たり判定をとる

	//当たったらアイテムをプレイヤーの腕付近に配置する

	//取得フラグをオンにする
	IsGet = true;
}

//アイテムを投げる処理
void PLAYER::ThrowItem(VECTOR PlayerPos, VECTOR ItemPos)
{
	//もしフラグがオンなら投げる
	if (IsGet == true)
	{

	}
}