#pragma once
#include "Scene.h"


#define RESULT_BG_PATH		"Data/Result/Result.png"
#define RESULT_BG2_PATH		"Data/Result/Result2.png"
#define PLAYER1WIN_PATH		"Data/Result/1Pwin.png"
#define PLAYER2WIN_PATH		"Data/Result/2Pwin.png"
#define CPUWIN_PATH			"Data/Result/CPUwin.png"

class SceneResult : public SceneBase
{
private:
	//îwåiÇÃÉOÉçÅ[ÉoÉãïœêî
	int BackGround_handle[1] = { 0 };
	int bgSkyX[1] = { 0 };

	int BackGround_handle2[1] = { 0 };
	int bgSkyX1[1] = { 0 };

	int Win1P_Hndl;
	int Win2P_Hndl;
	int WinCPU_Hndl;

	bool Win1P;
	bool Win2P;

public:
	void Init();

	void Step();

	void Draw();

	void Fin();
};

extern bool Win1P;
