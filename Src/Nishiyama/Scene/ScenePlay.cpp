#include <math.h>

#include "DxLib.h"
#include "../../Common.h"
#include "../Input/Input.h"
#include "ScenePlay.h"
#include "SceneTitle.h"
#include "../Collision/Collision.h"

//奥村
#include"../DefaultMap/DefaultMap.h"
_Map* CMap;

//プレイシーン初期化
void ScenePlay::Init()
{
	bg.Init(BackGroundKind::NONE);

	player = new PLAYER[2];

	//奥村
	CMap = new _Map;
	CMap->Init();

	player[0].Init(1);
	player[0].SetPlayerPos(Player1Pos);
	player[0].Load();
	
	if (PlayNumber == 2)
	{
		player[1].Init(2);
		player[1].SetPlayerPos(Player2Pos);
		player[1].Load();
	}
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_LOOP_PLAY;
}

//プレイシーン通常処理
void ScenePlay::Step()
{
	bg.Step();

	player[0].Step();
	if (PlayNumber == 2)
	{
		player[1].Step();
	}

	/*for (int BulletIndex = 0; BulletIndex < player[0].GetBulletMaxNum(); BulletIndex++)
	{
	}

	for (int BulletIndex = 0; BulletIndex < player[1].GetBulletMaxNum(); BulletIndex++)
	{
	}*/

	//プレイヤー1の弾の当たり判定(プレイヤー2がダメージを受ける)
	if (player[0].GetBulletIsUse() == true)
	{
		if (Collision::IsHitRect(player[0].GetBulletPos(), player[1].GetPlayerPos(), player[0].GetBulletSize(), player[1].GetPlayerSize()))
		{
			//プレイヤー2にダメージを与える
			player[1].Damege(player[0].GetBulletDamege());
			//弾の使用フラグをfalseにする
			player[0].SetBulletIsUse();
		}
	}
	//プレイヤー2の弾の当たり判定(プレイヤー1がダメージを受ける)
	if (player[1].GetBulletIsUse() == true)
	{
		if (Collision::IsHitRect(player[1].GetBulletPos(), player[0].GetPlayerPos(), player[1].GetBulletSize(), player[0].GetPlayerSize()))
		{
			//プレイヤー1にダメージを与える
			player[0].Damege(player[1].GetBulletDamege());
			//弾の使用フラグをfalseにする
			player[1].SetBulletIsUse();
		}
	}

	if (PlayNumber == 1)
	{
		if (player[0].GetHP() <= 0)
		{
			SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_PLAY;
		}
	}
	else if (PlayNumber == 2)
	{
		if (player[0].GetHP() <= 0 || player[1].GetHP() <= 0)
		{
			SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_PLAY;
		}
	}
}

//プレイシーン描画処理
void ScenePlay::Draw()
{
	bg.Draw();

	//奥村
	CMap->Draw();

	player[0].Draw(0);
	if (PlayNumber == 2)
	{
		player[1].Draw(1);
	}

	DrawFormatString(0, 200, GetColor(255, 255, 255), "プレイヤー1の体力：%d", player[0].GetHP());
	DrawFormatString(0, 215, GetColor(255, 255, 255), "プレイヤー2の体力：%d", player[1].GetHP());

}

//プレイシーン後処理
//リトライかどうかを返す
void ScenePlay::Fin()
{
	bg.Fin();
	player[0].Delete();
	if (PlayNumber == 2)
	{
		player[1].Delete();
	}

	delete[]player;
	player = nullptr;

	//奥村
	delete CMap;
	CMap = nullptr;

	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_INIT_RESULT;
}



//弾の当たり判定
//Posで指定したプレイヤーが攻撃を食らうようにしてます
//第6引数はダメージを受ける方のプレイヤー配列番号(0か1)
//第7引数はダメージを与える方のプレイヤー配列番号(0か1)
void ScenePlay::IsHitBullet(VECTOR BulletPos, VECTOR BulletSize, VECTOR Pos, VECTOR PosSize, int Damage, int take_damageNum, int deal_damageNum)
{
	//弾とプレイヤーの当たり判定をとる
	if (Collision::IsHitRect(BulletPos, BulletSize, Pos, PosSize))
	{
		player[take_damageNum].Damege(Damage);
		player[deal_damageNum].SetBulletIsUse();
	}
}
