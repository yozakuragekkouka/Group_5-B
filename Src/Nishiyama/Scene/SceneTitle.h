#pragma once
#include "Scene.h"

//シーン情報
class SceneTitle : public SceneBase
{
private:

public:
	void Init();

	void Step();

	void Draw();

	void Fin();
};