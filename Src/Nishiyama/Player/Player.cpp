#include "Player.h"
#include "../Scene/Scene.h"
#include "../Input/Input.h"
#include "../Collision/Collision.h"
#include "../../Common.h"



//初期化
void PLAYER::Init(int playerNumber)
{
	memset(&hundl, -1, sizeof(Hundle));

	flameCount = 0;
	AnimeNum = 0;
	PlayerSize = { 64.0f, 64.0f, 0.0f };
	

	//近接攻撃の攻撃力
	closeAttackDm = 10;

	//アイテムフラグ
	IsGet = false;

	//プレイヤー1の初期化
	dir = IsRight;
	ActionStateID = State_Normal;


	IsJump = false;
	IsDush = false;
	IsReturn = true;
	IsGround = false;

	//弾情報関連
	for (int i = 0; i < BULLET_MAX_NUM; i++)
	{
		bulletInfo[i].BulletReturn = true;
		bulletInfo[i].IsUse = false;
		bulletInfo[i].BulletPos = { 0.0f, 0.0f, 0.0f };
		bulletInfo[i].Speed = 0.0f;
	}
	BulletDamege = 5;
	BulletSize = { 160.0f, 80.0f, 0.0f };

	YSpeed = 0.0f;
	Gravity = 0.5f;
	JunpCount = 0;

	//プレイヤー１の移動キー
	ActionButton[0] = KEY_INPUT_W;		//ジャンプ
	ActionButton[1] = KEY_INPUT_A;		//左移動
	ActionButton[2] = KEY_INPUT_D;		//右移動
	ActionButton[3] = KEY_INPUT_SPACE;	//発射ボタン
	ActionButton[4] = KEY_INPUT_E;		//近距離攻撃
	ActionButton[5] = KEY_INPUT_F;		//アイテム攻撃

	if(playerNumber == 2)
	{

		Life = 100;

		dir = IsLeft;
		IsReturn = false;

		//プレイヤー2の移動キー
		ActionButton[0] = KEY_INPUT_UP;			//ジャンプ
		ActionButton[1] = KEY_INPUT_LEFT;		//左移動
		ActionButton[2] = KEY_INPUT_RIGHT;		//右移動
		ActionButton[3] = KEY_INPUT_RSHIFT;		//発射ボタン
		ActionButton[4] = KEY_INPUT_RCONTROL;	//近距離攻撃
		ActionButton[5] = KEY_INPUT_M;			//アイテム攻撃
	}

	OldPos = { 0.0f, 0.0f, 0.0f };
	Life = 100;
}

//画像読み込み
void PLAYER::Load()
{
	LoadDivGraph(PLAYER1_PATH, 18, 3, 6, (float)187 / 3, (float)382 / 6, hundl.PlayerHndl[0]);
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

	//アイテム処理
	/*if (Input::IsKeyPush(ActionButton[5]))
	{
		if (!IsGet)
		{
			GetItem();
		}
		else
		{
			ThrowItem();
		}
	}*/

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

	if (IsGet == true)
	{
		DrawString(0, 100, "Player1アイテムを持っている", GetColor(255, 255, 255));
		if (Input::IsKeyPush(ActionButton[5]))
		{
			DrawString(0, 115, "Player1アイテムを投げた", GetColor(255, 255, 255));
		}
	}
	else
	{
		DrawString(0, 100, "Player1アイテムを持っていない", GetColor(255, 255, 255));
	}

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
	if (Pos.x + PlayerSize.x / 2 >= SCREEN_SIZE_X)
	{
		Pos.x = SCREEN_SIZE_X - PlayerSize.x / 2;
	}
	else if (Pos.x - PlayerSize.x / 2 < 0.0f)
	{
		Pos.x = PlayerSize.x / 2;
	}

	//Y座標制限
	//
	if (Pos.y + PlayerSize.y / 2 >= SCREEN_SIZE_Y)
	{
		YSpeed = 0.0f;
		Pos.y = SCREEN_SIZE_Y - PlayerSize.y / 2;
		JunpCount = 0;
		IsJump = false;

		if (IsDush == false)
		{
			ActionStateID = State_Normal;
		}

	}
	else if (Pos.y - PlayerSize.y / 2 < 0.0f)
	{
		Pos.y = PlayerSize.y / 2;
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
void PLAYER::GetItem(VECTOR ItemPos, VECTOR ItemSize)
{
	//当たり判定をとる
	if (Collision::IsHitRect(Pos, ItemPos, PlayerSize, ItemSize))
	{
		//当たったらアイテムをプレイヤーの腕付近に配置する
		ItemPos = Pos;
		//取得フラグをオンにする
		IsGet = true;
	}
}

//アイテムを投げる処理
void PLAYER::ThrowItem(VECTOR ItemPos)
{
	//もしフラグがオンなら投げる
	if (IsGet == true)
	{
		IsGet = false;
	}
}