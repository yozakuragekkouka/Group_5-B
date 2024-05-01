#pragma once
#include "Scene.h"
#include "../BackGround/BackGround.h"

class ScenePlay : public SceneBase
{
private:
	BackGround bg;

public:
	void Init();
	void Step();
	void Draw();
	void Fin();
};