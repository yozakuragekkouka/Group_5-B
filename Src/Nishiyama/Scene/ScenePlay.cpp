#include <math.h>

#include "DxLib.h"
#include "../../Common.h"
#include "../Input/Input.h"
#include "ScenePlay.h"
#include "SceneTitle.h"
#include "../Collision/Collision.h"
#include"../Effect/Effect.h"




//プレイシーン初期化
void ScenePlay::Init()
{
	bg1.Init(BackGroundKind::SKY);
	bg2.Init(BackGroundKind::CLOUD);
	bg3.Init(BackGroundKind::BUILDING);

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

	//エフェクトの初期化
	InitEffect();
	//エフェクトの読み込み
	LoadEffect(EFFECT_TYPE_JUMP, 10);
	LoadEffect(EFFECT_TYPE_HIT, 2);

	playBgm_Hndl = LoadSoundMem(PLAYBGM_PATH);
	HitSe_Hndl = LoadSoundMem(HITSE_PATH);
	//曲の効果音
	PlaySoundMem(playBgm_Hndl, DX_PLAYTYPE_LOOP, true);


	MapDrawFlag = false;
	isEdit = 0;
	currentMapID = 0;

	for (int Ori_or_Edi = 0; Ori_or_Edi < 2; Ori_or_Edi++)
	{
		for (int mapID = 0; mapID < 5; mapID++)
		{
			map[Ori_or_Edi][mapID].Init((bool)Ori_or_Edi, mapID);
		}
	}

	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_LOOP_PLAY;
}

//プレイシーン通常処理
void ScenePlay::Step()
{
	bg1.Step();
	bg2.Step();
	bg3.Step();

	player[0].Step();
	if (PlayNumber == 2)
	{
		player[1].Step();
	}
	//マップとの当たり判定
	MapCollision();


	StepEffect();

	for (int Ori_or_Edi = 0; Ori_or_Edi < 2; Ori_or_Edi++)
	{
		for (int mapID = 0; mapID < 5; mapID++)
		{
			map[Ori_or_Edi][mapID].Step();
		}
	}

	if (Input::IsKeyPush(KEY_INPUT_I))
	{
		MapDrawFlag = !MapDrawFlag;
	}
	if (MapDrawFlag)
	{
		if (Input::IsKeyPush(KEY_INPUT_O))
		{
			isEdit++;
			if (isEdit > 1)
				isEdit = 0;
		}
		if (Input::IsKeyPush(KEY_INPUT_P))
		{
			currentMapID++;
			if (currentMapID > 4)
				currentMapID = 0;
		}
	}

	if (PlayNumber == 2)
	{
		//近接攻撃の当たり判定
		if (Input::IsKeyPush(player[0].GetBottan()))
		{
			//左
			if (player[0].GetPlayerdir() == 0)
			{
				//プレイヤー1の当たり判定(プレイヤー2がダメージを受ける)
				if (player[0].GetDamegeCoolTime() >= 30)
				{
					if (Collision::IsHitRectNormal(player[0].GetPunchPosX() - 64, player[0].GetPunchPosY() - 32, 32, 64,
						player[1].GetPunchPosX() - 32, player[1].GetPunchPosY() - 32, 64, 64))
					{
						PlayEffect(EFFECT_TYPE_HIT, 
							player[1].GetNormalPlayerPos().x, 
							player[1].GetNormalPlayerPos().y);
						PlaySoundMem(HitSe_Hndl, DX_PLAYTYPE_BACK, true);

						player[1].Damege(10);
					}
				}
			}
			//右
			if (player[0].GetPlayerdir() == 1)
			{
				if (player[0].GetDamegeCoolTime() >= 30)
				{
					if (Collision::IsHitRectNormal(player[0].GetPunchPosX() + 32, player[0].GetPunchPosY() - 32, 32, 64,
						player[1].GetPunchPosX() - 32, player[1].GetPunchPosY() - 32, 64, 64))
					{
						PlayEffect(EFFECT_TYPE_HIT, 
							player[1].GetNormalPlayerPos().x, 
							player[1].GetNormalPlayerPos().y);
						PlaySoundMem(HitSe_Hndl, DX_PLAYTYPE_BACK, true);

						player[1].Damege(10);
					}
				}
			}

		}

		//近接攻撃の当たり判定
		if (Input::IsKeyPush(player[1].GetBottan()))
		{
			//プレイヤー2の当たり判定(プレイヤー1がダメージを受ける)
			if (player[1].GetPlayerdir() == 0)
			{
				if (player[1].GetDamegeCoolTime() >= 30)
				{
					if (Collision::IsHitRectNormal(player[1].GetPunchPosX() - 64, player[1].GetPunchPosY() - 32, 32, 64,
						player[0].GetPunchPosX() - 32, player[0].GetPunchPosY() - 32, 64, 64))
					{
						PlayEffect(EFFECT_TYPE_HIT, 
							player[0].GetNormalPlayerPos().x, 
							player[0].GetNormalPlayerPos().y);
						PlaySoundMem(HitSe_Hndl, DX_PLAYTYPE_BACK, true);

						player[0].Damege(10);
					}
				}
			}
			//右
			if (player[1].GetPlayerdir() == 1)
			{
				if (player[1].GetDamegeCoolTime() >= 30)
				{
					if (Collision::IsHitRectNormal(player[1].GetPunchPosX() + 32, player[1].GetPunchPosY() - 32, 32, 64,
						player[0].GetPunchPosX() - 32, player[0].GetPunchPosY() - 32, 64, 64))
					{
						PlayEffect(EFFECT_TYPE_HIT, 
							player[0].GetNormalPlayerPos().x,
							player[0].GetNormalPlayerPos().y);
						PlaySoundMem(HitSe_Hndl, DX_PLAYTYPE_BACK, true);

						player[0].Damege(10);
					}
				}
			}
		}
	}
	
	if (PlayNumber == 2)
	{
		//弾の当たり判定--------------------------------------------------------------
	//プレイヤー1の弾の当たり判定(プレイヤー2がダメージを受ける)
		if (player[0].GetDamegeCoolTime() >= 30)
		{
			for (int i = 0; i < BULLET_MAX_NUM; i++)
			{
				if (player[0].GetBulletIsUse(i) == true)
				{
					if (Collision::IsHitRect(player[0].GetBulletPos(i), player[1].GetNormalPlayerPos(), player[0].GetBulletSize(), player[1].GetPlayerSize()))
					{
						PlayEffect(EFFECT_TYPE_HIT,
							player[1].GetNormalPlayerPos().x,
							player[1].GetNormalPlayerPos().y);
						//プレイヤー2にダメージを与える
						player[1].Damege(player[0].GetBulletDamege());
						//ダメージクールタイムを0にする
						player[1].SetDamageCoolTime();
						//弾の使用フラグをfalseにする
						player[0].SetBulletIsUse(i);
					}
				}
			}
		}

		//プレイヤー2の弾の当たり判定(プレイヤー1がダメージを受ける)
		if (player[1].GetDamegeCoolTime() >= 30)
		{
			for (int i = 0; i < BULLET_MAX_NUM; i++)
			{
				if (player[1].GetBulletIsUse(i) == true)
				{
					if (Collision::IsHitRect(player[1].GetBulletPos(i), player[0].GetNormalPlayerPos(), player[1].GetBulletSize(), player[0].GetPlayerSize()))
					{
						PlayEffect(EFFECT_TYPE_HIT,
							player[0].GetNormalPlayerPos().x,
							player[0].GetNormalPlayerPos().y);
						//プレイヤー1にダメージを与える
						player[0].Damege(player[1].GetBulletDamege());
						//ダメージクールタイムを0にする
						player[0].SetDamageCoolTime();
						//弾の使用フラグをfalseにする
						player[1].SetBulletIsUse(i);
					}
				}
			}
		}

		//ダメージクールタイムを加算
		for (int Number = 0; Number < 2; Number++)
		{
			if (player[Number].GetDamegeCoolTime() <= 30)
			{
				player[Number].AddDamageCoolTime(1);
			}
		}
		//---------------------------------------------------------------------------

	}
	
	//終了処理-------------------------------------------------------------------
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
	//-----------------------------------------------------------------------
}

//プレイシーン描画処理
void ScenePlay::Draw()
{
	bg1.Draw();
	bg2.Draw();
	bg3.Draw();

	//奥村
	if (MapDrawFlag == false)
	{
		CMap->Draw();
	}
	else
	{
		map[isEdit][currentMapID].Draw();
	}

	DrawEffect();
	player[0].Draw(0);
	if (PlayNumber == 2)
	{
		player[1].Draw(1);
	}

	//DrawFormatString(0, 0, GetColor(255, 255, 255), "プレイヤー1の体力：%d", player[0].GetHP());
	if (PlayNumber == 2)
	{
		//DrawFormatString(0, 15, GetColor(255, 255, 255), "プレイヤー2の体力：%d", player[1].GetHP());
	}

}

//プレイシーン後処理
//リトライかどうかを返す
void ScenePlay::Fin()
{
	bg1.Fin();
	bg2.Fin();
	bg3.Fin();

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

	FinEffect();

	DeleteSoundMem(playBgm_Hndl);
	DeleteSoundMem(HitSe_Hndl);

	for (int Ori_or_Edi = 0; Ori_or_Edi < 2; Ori_or_Edi++)
	{
		for (int mapID = 0; mapID < 5; mapID++)
		{
			map[Ori_or_Edi][mapID].Fin();
		}
	}

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
	//DrawFormatString(0, 300, GetColor(255, 255, 255), "%f", player[0].GetNextPos().y);
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
				//DrawFormatString(0, 400, GetColor(255, 255, 255), "%f", B.x);
				player[index].HandleCollision(index, dirArray, A, B, Asize, Bsize, checkY);
			}
		}
	}
}