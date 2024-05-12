#pragma once
#include "Scene.h"
#include "../BackGround/BackGround.h"
#include "../Player/Player.h"

class ScenePlay : public SceneBase
{
private:
	BackGround bg;
	PLAYER *player;

	const VECTOR Player1Pos = { 32.0f, 500.0f, 0.0f };
	const VECTOR Player2Pos = { 1248.0f, 500.0f, 0.0f };



public:
	void Init();
	void Step();
	void Draw();
	void Fin();

	//奥村
	//マップ当たり判定の総合
	void MapCollision();

	//マップとプレイヤーの当たり判定の情報を
	// GetIsGroundとGetMoveDirectionに渡す
	void CheckCollision(int index, bool checkY);

	//宮近
	//弾の当たり判定
	//引数1が攻撃を食らうようにしてます
	void IsHitBullet(VECTOR BulletPos, VECTOR BulletSize, VECTOR Pos, VECTOR PosSize, int Damage, int take_damageNum, int deal_damageNum);
};