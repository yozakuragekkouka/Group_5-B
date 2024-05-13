#pragma once
#include "Scene.h"
#include "../Player/Player.h"


#define RESULT_BG_PATH		"Data/Result/Result.png"
#define RESULT_BG2_PATH		"Data/Result/Result2.png"
#define PLAYER1WIN_PATH		"Data/Result/1Pwin.png"
#define PLAYER2WIN_PATH		"Data/Result/2Pwin.png"
#define CPUWIN_PATH			"Data/Result/CPUwin.png"

#define BGM_PATH		"Data/BGM/Result.mp3"
class SceneResult : public SceneBase
{
private:

	PLAYER Player;
	//îwåiÇÃÉOÉçÅ[ÉoÉãïœêî
	int BackGround_handle[1] = { 0 };
	int bgSkyX[1] = { 0 };

	int BackGround_handle2[1] = { 0 };
	int bgSkyX1[1] = { 0 };

	int Win1P_Hndl;
	int Win1P_x, Win1P_y;
	int Win2P_Hndl;
	int Win2P_x, Win2P_y;
	int WinCPU_Hndl;
	int WinCPU_x, WinCPU_y;

	int BGM_Hndl;
public:
	void Init();

	void Step();

	void Draw();

	void Fin();
};