#pragma once
#include "Scene.h"
#include "../BackGround/BackGround.h"
#include "../Player/Player.h"
#include "../DefaultMap/DefaultMap.h"
class ScenePlay : public SceneBase
{
private:
	BackGround bg;
	PLAYER *player;

	const VECTOR Player1Pos = { 32.0f, 500.0f, 0.0f };
	const VECTOR Player2Pos = { 1248.0f, 500.0f, 0.0f };

	_Map* CMap;

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
};