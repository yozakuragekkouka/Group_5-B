#include "DxLib.h"
#include "Scene.h"
#include "SceneTitle.h"
#include "ScenePlay.h"
#include "SceneResult.h"

SCENEID SceneManager::SceneManager::g_CurrenySceneID;	//現在のシーンID

SceneManager::SceneManager()
{
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_INIT_TITLE;

	RetryFlag = false;

	scene = nullptr;
}

SceneManager::~SceneManager()
{
	InitGraph();
	InitSoundMem();
}

void SceneManager::SceneInit()
{
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_INIT_TITLE;

	RetryFlag = false;

	scene = nullptr;
}

bool SceneManager::SceneLoop()
{
	switch (SceneManager::g_CurrenySceneID)
	{
	case SCENEID::SCENE_ID_END:
	{
		return true;
	}

	case SCENEID::SCENE_ID_INIT_TITLE:
	{
		scene = new SceneTitle;
		scene->Init();
	}
	break;
	case SCENEID::SCENE_ID_LOOP_TITLE:
	{
		if (scene)
		{
			scene->Step();
			scene->Draw();
		}
	}
	break;
	case SCENEID::SCENE_ID_FIN_TITLE:
	{
		if (scene)
		{
			scene->Fin();
			delete scene;
			scene = nullptr;
		}
	}
	break;
	//SCENE_TITLE終わり

	case SCENEID::SCENE_ID_INIT_PLAY:
	{
		scene = new ScenePlay;
		scene->Init();
	}
	break;
	case SCENEID::SCENE_ID_LOOP_PLAY:
	{
		if (scene)
		{
			scene->Step();
			scene->Draw();
		}
	}
	break;
	case SCENEID::SCENE_ID_FIN_PLAY:
	{
		if (scene)
		{
			scene->Fin();
			delete scene;
			scene = nullptr;
		}
	}
	break;
	//SCENE_PLAY終わり

	case SCENEID::SCENE_ID_INIT_RESULT:
	{
		scene = new SceneResult;
		scene->Init();
	}
	break;
	case SCENEID::SCENE_ID_LOOP_RESULT:
	{
		if (scene)
		{
			scene->Step();
			scene->Draw();
		}
	}
	break;
	case SCENEID::SCENE_ID_FIN_RESULT:
	{
		if (scene)
		{
			scene->Fin();
			delete scene;
			scene = nullptr;
		}
	}
	break;
	//SCENE_RESULT終わり

	}//シーン振り分け
	return false;
}

void SceneManager::SceneFin()
{
	InitGraph();
	InitSoundMem();

	if (scene != nullptr)
		delete scene;
}