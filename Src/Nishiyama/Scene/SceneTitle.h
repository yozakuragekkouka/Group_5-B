#pragma once
#include "Scene.h"

#define TITLE_PATH		"Data/Title/�^�C�g��.png"
#define BUTTON_PATH		"Data/Title/�v���C�{�^��.png"

//�V�[�����
class SceneTitle : public SceneBase
{
private:
	int Title_Hndl;

	int Playbutton_Hndl;

	int button_x, button_y;

	SCENEID nextScene;

public:
	void Init();

	void Step();

	void Draw();

	void Fin();
};

extern int PlayNumber;