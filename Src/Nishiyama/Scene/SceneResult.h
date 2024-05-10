#pragma once
#include "Scene.h"


#define RESULT_BG_PATH		"Data/Result/Result.png"
#define RESULT_BG2_PATH		"Data/Result/Result2.png"

class SceneResult : public SceneBase
{
private:
	//”wŒi‚ÌƒOƒ[ƒoƒ‹•Ï”
	int BackGround_handle[1] = { 0 };
	int bgSkyX[1] = { 0 };

	int BackGround_handle2[1] = { 0 };
	int bgSkyX1[1] = { 0 };

public:
	void Init();

	void Step();

	void Draw();

	void Fin();
};