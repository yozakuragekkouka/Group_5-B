#pragma once
#include "Scene.h"

#define TITLE_PATH		"Data/Title/Title1.png"
#define TITLE2_PATH		"Data/Title/Title2.png"
#define BUTTON_PATH		"Data/Title/�v���C�{�^��.png"

//�V�[�����
class SceneTitle : public SceneBase
{
private:
	
	//�w�i�̃O���[�o���ϐ�
	int BackGround_handle[2] = { 0 };
	int bgSkyX[2] = { 0 };

	int BackGround_handle2[2] = { 0 };
	int bgSkyX1[2] = { 0 };

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