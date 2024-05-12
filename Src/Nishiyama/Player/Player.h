
#pragma once
#include <DxLib.h>


#define PLAYER1_PATH		"Data/Image/Player/Player1.png"
#define PLAYER2_PATH		"Data/Image/Player/Player2.png"

#define PLAYER_MAX_LIFE		(100)

#define BULLETHNDL_PATH		"Data/Image/Player/FireBall.png"

#define PLAYER_ANIME_NUM	(18)

#define JUMPMAX_NUM			(2)
#define SPEED				(4.0f)

#define BULLET_MAX_NUM		(3)
#define BULLET_ANIME_NUM	(24)
#define SHOT_INTERVAL		(100)

struct Hundle
{
	int PlayerHndl[2][PLAYER_ANIME_NUM];
	int HP_Flame_Hbndl[2];
	int HP_Hndl[2];
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
	State_Atack,
};

//弾の向き
enum BULLETDIR
{
	BULLET_LEFT,
	BULLET_RIGHT,
};

class PLAYER
{
protected:
	//描画に使う変数
	Hundle hundl;
	int AnimeNum;
	VECTOR PlayerSize;
	
	//プレイヤーのライフ
	int Life;
	int DamageCoolTime;

	//近接攻撃の攻撃力
	int closeAttackDm;

	//方向を決める変数
	DIR dir;
	VECTOR Pos;
	VECTOR Pos1;	//左端を原点にするためだけの変数
	VECTOR OldPos;

	ACTIONSTATE ActionStateID;
	ACTIONSTATE OldActionState;

	//ジャンプに使う変数
	float YSpeed;
	float Gravity;
	int JunpCount;

	//弾に使う変数
	struct BulletInfo
	{
		VECTOR BulletPos;
		VECTOR BulletPos1;	//左端を原点にするためだけの変数
		bool IsUse;
		int Isdir;
		int BulletHndl[BULLET_ANIME_NUM];
		bool BulletReturn;
		int BulletAnimeIndex;
		float Speed;
		
		
	};
	int BulletDamege;
	VECTOR BulletSize;		//弾画像のサイズ
	BulletInfo bulletInfo[BULLET_MAX_NUM];


	//投げるアイテム
	bool IsGet;


	//判定フラグ
	bool IsDush;
	bool IsReturn;
	bool IsJump;
	bool IsGround;

	int flameCount;
	int LoopCount;

	//アクションボタン
	int ActionButton[6];

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

	//弾の発射間隔調整
	void BulletCount();

	//弾の発射処理
	void BulletShot();

	//弾の移動
	void MoveBullet();

	//アイテムを拾う処理
	void GetItem(VECTOR ItemPos, VECTOR ItemSize);

	//アイテムを投げる処理
	void ThrowItem(VECTOR ItemPos);

	//アニメーション切り替え処理
	void PlayerAnimetion();

	//弾の最大数取得
	int GetBulletMaxNum()
	{
		return BULLET_MAX_NUM;
	}

	//プレイヤーの座標設定
	void SetPlayerPos(VECTOR Position)
	{
		Pos = Position;
	}

	//プレイヤーの座標取得
	VECTOR GetPlayerPos()
	{
		return Pos1;
	}

	VECTOR GetPlayerSize()
	{
		return PlayerSize;
	}

	//弾の座標取得
	VECTOR GetBulletPos()
	{
		for (int i = 0; i < BULLET_MAX_NUM; i++)
		{
			return bulletInfo[i].BulletPos1;
		}
	}

	//弾の使用フラグ取得
	bool GetBulletIsUse()
	{
		for (int i = 0; i < BULLET_MAX_NUM; i++)
		{
			return bulletInfo[i].IsUse;
		}
	}

	//弾の使用フラグ設定
	void SetBulletIsUse()
	{
		for (int i = 0; i < BULLET_MAX_NUM; i++)
		{
			bulletInfo[i].IsUse = false;
		}	
	}

	//弾の横サイズ取得
	VECTOR GetBulletSize()
	{
		return BulletSize;
	}

	//弾のダメージ取得
	int GetBulletDamege()
	{
		return BulletDamege;
	}

	//プレイヤーのHP取得
	int GetHP()
	{
		return Life;
	}

	int SetLife(int Hp)
	{
		return Life = Hp;
	}

	//プレイヤーのHP設定
	void Damege(int damege)
	{
		Life -= damege;
	}

	//ダメージクールタイム取得
	int GetDamegeCoolTime()
	{
		return DamageCoolTime;
	}

	//ダメージクールタイム設定
	void SetDamageCoolTime()
	{
		DamageCoolTime = 0;
	}

	//ダメージクールタイム増加
	void AddDamageCoolTime(int AddTime)
	{
		DamageCoolTime += AddTime;
	}
};

