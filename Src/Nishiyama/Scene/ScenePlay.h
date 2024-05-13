#pragma once
#include "Scene.h"
#include "../BackGround/BackGround.h"
#include "../Player/Player.h"
#include "../DefaultMap/DefaultMap.h"
#include "../NumberFont/NumberFont.h"
#include "../NumberFont/NumberFontData.h"

#define PLAYBGM_PATH		"Data/BGM/戦闘BGM.wav"
#define HITSE_PATH		"Data/SE/damage.mp3"

class ScenePlay : public SceneBase
{
private:
	BackGround bg;
	PLAYER *player;

	const VECTOR Player1Pos = { 32.0f, 500.0f, 0.0f };
	const VECTOR Player2Pos = { 1248.0f, 500.0f, 0.0f };

	_Map* CMap;

	int playBgm_Hndl;

	int HitSe_Hndl;
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