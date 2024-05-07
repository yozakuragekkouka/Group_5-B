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
	player.Init(PlayNumber);
	player.Load();
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_LOOP_PLAY;
}

//プレイシーン通常処理
void ScenePlay::Step()
{
	bg.Step();
	player.Step();
	if (Input::IsKeyPush(KEY_INPUT_RETURN))
	{
		SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_PLAY;
	}
}

//プレイシーン描画処理
void ScenePlay::Draw()
{
	bg.Draw();
	player.Draw();
}

//プレイシーン後処理
//リトライかどうかを返す
void ScenePlay::Fin()
{
	bg.Fin();
	player.Delete();
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_INIT_RESULT;
}
