#pragma once
#include "Scene.h"

#define TITLE_PATH		"Data/Title/Title1.png"
#define TITLE2_PATH		"Data/Title/Title2.png"
#define TITLE_NAME_PATH	"Data/Title/TitleName.png"
#define BUTTON_PATH		"Data/Title/PLAY-2024-5-10.png"

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

	int button_x, button_y;

	SCENEID nextScene;

public:
	void Init();

	void Step();

	void Draw();

	void Fin();
};

extern int PlayNumber;