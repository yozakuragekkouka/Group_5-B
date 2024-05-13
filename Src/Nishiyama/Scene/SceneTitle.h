#pragma once
#include "Scene.h"

#define TITLE_PATH		"Data/Title/Title1.png"
#define TITLE2_PATH		"Data/Title/Title2.png"
#define TITLE_NAME_PATH	"Data/Title/TitleName.png"
#define BUTTON_PATH		"Data/Title/PLAY-2024-5-10.png"

#define PLAY_PATH		"Data/Title/1人でPLay.png"
#define PLAY2_PATH		"Data/Title/2人でPLay.png"
#define ARROW_PATH		"Data/Title/arrow.png"

#define BGM_PATH		"Data/BGM/タイトル.mp3"
#define SE_S_PATH		"Data/SE/カーソル移動5.mp3"
#define SE_D_PATH		"Data/SE/決定ボタンを押す43.mp3"

//シーン情報
class SceneTitle : public SceneBase
{
private:
	
	//背景のグローバル変数
	int BackGround_handle[1] = { 0 };
	int bgSkyX[1] = { 0 };

	int BackGround_handle2[1] = { 0 };
	int bgSkyX1[1] = { 0 };

	int Playbutton_Hndl;

	int TitleName_Hndl;

	int Play_Hndl;
	int button_x, button_y;
	int Play2_Hndl;
	int button2_x, button2_y;

	int arrow_Hndl;
	int arrow_x, arrow_y;

	int bgm_Hndl;
	int Se_Hndl;
	int Se2_Hndl;

	SCENEID nextScene;

public:
	void Init();

	void Step();

	void Draw();

	void Fin();
};

extern int PlayNumber;