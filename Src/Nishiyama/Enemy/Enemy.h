#include "../Scene//Scene.h"
#include<math.h>
#include "../../Common.h"

const int CHARACTER_MAX_NUM = 3;

class Enemy {

protected:

	const float DISTANCE = 300;

	//プレイヤー変数
	int EnemyHan[11] = { 0 };				//プレイヤー画像
	const int Enemy_Animation = 11;			//プレイヤーのアニメーション数
	const int EnemySize = 64;					//プレイヤー画像サイズ

	float BaseEnemySpeed = 0.5f;				//プレイヤー基本移動速度
	float MaxEnemySpeed = 5.0f;				//プレイヤー最大移動速度
	//	float accelerationFactor = 0.0001f;			//加速度

	int animState = 0;						//右向きか左向きか
	int animFlag = 0;						//アニメーションの種類
	int animIndex = 0;						//アニメーションの添え字
	int changeAnimFlame = 0;				//アニメーション切り替え時間

	int animFlameCount = 0;				//切り替え時間カウント
	bool EnemyOnSwitch = false;			//プレイヤーとスイッチが重なっているか
	bool EnemyGoalFlag = false;			//プレイヤーがゴールにいるか

	//float BasePlayerSpeed = 0.2f;				//プレイヤー基本移動速度
	//float MaxPlayerSpeed = 4.0f;				//プレイヤー最大移動速度

	VECTOR m_pos;//プレイヤーの座標
	VECTOR m_next_pos;//次のフレームの座標
	float speed;

	VECTOR m_move_vec;

	bool enemyStopFlag = false;

	bool MouseOrPlayer = false;//マウスに反応時false、プレイヤーに反応時true;

	float grav;//重力の大きさ

	bool isJump;
	float jumpPower;
	///////////////////////////////////////////////////////////////////////

	//仮他のプレイヤーの座標
	VECTOR dvd[CHARACTER_MAX_NUM];

	//仮他のプレイヤーの次のフレームの座標
	VECTOR next_dvd[CHARACTER_MAX_NUM];

	//仮他のプレイヤー半径
	float radius;

	//現在対応している敵
	int currentRivalIndex;

	//これから対応する敵
	int nearestRivalIndex;

	//プレイヤーの参加人数
	int PlayerToParticipate;

	VECTOR Rival[CHARACTER_MAX_NUM];//プレイヤーとCPの座標を入れる変数
	///////////////////////////////////////////////////////////////////////


	// ノード定義
	struct Node {
		int x, y;
		int cost; // 移動コスト
		int heuristic; // ヒューリスティック（推定コスト）
		Node* parent; // 親ノード

		// コストの合計を計算する関数
		int GetScore() const {
			return cost + heuristic;
		}

		// ノードの比較関数
		bool operator<(const Node& other) const {
			return GetScore() > other.GetScore();
		}
	};


	// ヒューリスティック関数（マンハッタン距離）
	int Heuristic(int x1, int y1, int x2, int y2) {
		return abs(x1 - x2) + abs(y1 - y2);
	}

public:
	int Walk_Sound[13] = { 0 };

	Enemy();
	~Enemy();

	//初期化
	void Init(int num);

	//通常処理
	void Step();

	//描画処理
	void Draw();

	//終了処理
	void Fin();

	//プレイヤー

	//プレイヤーのｘ座標を得る
	float GetEnemyPosX() { return m_pos.x; }

	//プレイヤーのｙ座標を得る
	float GetEnemyPosY() { return m_pos.y; }

	//プレイヤーのＸサイズを得る
	int GetEnemySizeX() { return EnemySize; }

	//プレイヤーのＹサイズを得る
	int GetEnemySizeY() { return EnemySize; }

	//プレイヤーの進んでいる方向をチェック
	void GetMoveDirection(bool* _dirArray);

	//プレイヤーのｘ座標を得る
	float GetNextEnemyPosX() { return m_next_pos.x; }

	//プレイヤーのｙ座標を得る
	float GetNextEnemyPosY() { return m_next_pos.y; }

	//プレイヤーのx座標をセット
	void SetEnemyNextPosX(float new_pos_x) { m_next_pos.x = new_pos_x; }

	//プレイヤーのｙ座標をセット
	void SetEnemyNextPosY(float new_pos_y) { m_next_pos.y = new_pos_y; }

	//線形補完関数
	float lerp(float start, float end, float t);

	void SetEnemyOnSwitchTrue();

	void SetEnemyOnSwitchFalse();

	bool GetEnemyOnSwitch() { return EnemyOnSwitch; };

	///////////////////////////////////////////////////////////////////////

	double CalculateDistance(int x1, int y1, int x2, int y2)
	{
		return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
	}

	//一番近い敵を探す
	void ConnectToNearestRival();
	//一番近い敵に近づく
	void NearsRival();
	//仮他のプレイヤーの移動
	void Update();
	//プレイヤーとCPの座標を共通の配列に統一する
	void Participate(VECTOR Player[CHARACTER_MAX_NUM]);
	//ジャンプする
	void Jump();
	//ジャンプできるか
	bool GetJump() { return isJump; };
	//ジャンプできるようにする
	void SetJump() { isJump = false; };
	bool IsBlockBetween(float x1, float y1, float x2, float y2);
	///////////////////////////////////////////////////////////////////////
};