#include <math.h>

#include "DxLib.h"
#include "../../Common.h"
#include "../Input/Input.h"
#include "ScenePlay.h"
#include "SceneTitle.h"

//プレイシーン初期化
void ScenePlay::Init()
{
	bg.Init(BackGroundKind::NONE);

	player = new PLAYER[2];


	player[0].Init(1);
	player[0].Load();

	if (PlayNumber == 2)
	{
		player[1].Init(2);
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
	if (Input::IsKeyPush(KEY_INPUT_RETURN))
	{
		SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_PLAY;
	}
}

//プレイシーン描画処理
void ScenePlay::Draw()
{
	bg.Draw();
	player[0].Draw(0);
	if (PlayNumber == 2)
	{
		player[1].Draw(1);
	}
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

	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_INIT_RESULT;
}
