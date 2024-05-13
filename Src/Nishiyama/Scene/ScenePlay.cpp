#include <math.h>

#include "DxLib.h"
#include "../../Common.h"
#include "../Input/Input.h"
#include "ScenePlay.h"
#include "SceneTitle.h"
#include "../Collision/Collision.h"





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
	//マップとの当たり判定
	MapCollision();

	//近接攻撃の当たり判定
	
	//弾の当たり判定--------------------------------------------------------------
	//プレイヤー1の弾の当たり判定(プレイヤー2がダメージを受ける)
	if (player[0].GetDamegeCoolTime() >= 30)
	{
		if (player[0].GetBulletIsUse() == true)
		{

			if (Collision::IsHitRect(player[0].GetBulletPos(), player[1].GetPlayerPos(), player[0].GetBulletSize(), player[1].GetPlayerSize()))
			{
				//プレイヤー2にダメージを与える
				player[1].Damege(player[0].GetBulletDamege());
				//ダメージクールタイムを0にする
				player[1].SetDamageCoolTime();
				//弾の使用フラグをfalseにする
				player[0].SetBulletIsUse();
			}
		}
	}
	//プレイヤー2の弾の当たり判定(プレイヤー1がダメージを受ける)
	if (player[1].GetDamegeCoolTime() >= 30)
	{
		if (player[1].GetBulletIsUse() == true)
		{
			if (Collision::IsHitRect(player[1].GetBulletPos(), player[0].GetPlayerPos(), player[1].GetBulletSize(), player[0].GetPlayerSize()))
			{
				//プレイヤー1にダメージを与える
				player[0].Damege(player[1].GetBulletDamege());
				//ダメージクールタイムを0にする
				player[0].SetDamageCoolTime();
				//弾の使用フラグをfalseにする
				player[1].SetBulletIsUse();
			}
		}
	}
	//---------------------------------------------------------------------------

	for (int Number = 1; Number < 3; Number++)
	{
		if (player[Number].GetDamegeCoolTime() <= 30)
		{
			player[Number].AddDamageCoolTime(1);
		}
	}

	if (PlayNumber == 1)
	{
		if (player[0].GetHP() <= 0)
		{
			IsPlayer1Win = false;
			IsPlayer2Win = false;
			IsCPUWin = true;
			SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_PLAY;
		}
	}
	else if (PlayNumber == 2)
	{
		if (player[0].GetHP() <= 0 || player[1].GetHP() <= 0)
		{
			SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_PLAY;
		}
		//プレイヤー2のHPがなくなったとき
		if (player[1].GetHP() <= 0)
		{
			IsPlayer1Win = true;
			IsPlayer2Win = false;
			IsCPUWin = false;
		}
		//プレイヤー1のHPがなくなったとき
		if (player[0].GetHP() <= 0)
		{
			IsPlayer2Win = true;
			IsPlayer1Win = false;
			IsCPUWin = false;
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

//奥村
// マップの当たり判定
void ScenePlay::MapCollision() {
	for (int index = 0; index < PlayNumber; index++) {
		CheckCollision(index, true);  // Y方向の当たり判定
		CheckCollision(index, false); // X方向の当たり判定
	}
}

void ScenePlay::CheckCollision(int index, bool checkY) {
	DrawFormatString(0, 300, GetColor(255, 255, 255), "%f", player[0].GetNextPos().y);
	for (int mapIndexY = 0; mapIndexY < MAP_DATA_Y; mapIndexY++) {
		for (int mapIndexX = 0; mapIndexX < MAP_DATA_X; mapIndexX++) {
			if (CMap->m_MapData[mapIndexY][mapIndexX] == 0) continue;

			bool dirArray[4] = { false, false, false, false };
			player[index].GetMoveDirection(dirArray);

			VECTOR A = { player[index].GetNormalPlayerPos().x,player[index].GetNormalPlayerPos().y ,0 };
			VECTOR Asize = { player[index].GetPlayerSize().x ,player[index].GetPlayerSize().y ,0};

			VECTOR B = { (mapIndexX * MAP_SIZE)+ MAP_SIZE , (mapIndexY * MAP_SIZE) + MAP_SIZE ,0 };
			VECTOR Bsize = { MAP_SIZE ,MAP_SIZE ,0 };

			if (checkY) {
				A.y = player[index].GetNextPos().y;
			}
			else {
				A.x = player[index].GetNextPos().x;
			}
			if (Collision::IsHitRect(A, B, Asize, Bsize)) {
				DrawFormatString(0, 400, GetColor(255, 255, 255), "%f", B.x);
				player[index].HandleCollision(index, dirArray, A, B, Asize, Bsize, checkY);
			}
		}
	}
}