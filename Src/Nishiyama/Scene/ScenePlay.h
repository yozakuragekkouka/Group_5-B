#pragma once
#include "Scene.h"
#include "../BackGround/BackGround.h"
#include "../Player/Player.h"

class ScenePlay : public SceneBase
{
private:
	BackGround bg;
	PLAYER *player;

public:
	void Init();
	void Step();
	void Draw();
	void Fin();
};