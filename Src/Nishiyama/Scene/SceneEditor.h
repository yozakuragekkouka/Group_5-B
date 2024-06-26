#pragma once
#include "Scene.h"
#include "../MapEditor/MapEditor.h"

//シーン情報
class SceneEditor : public SceneBase
{
private:
	MapEditor editor;

public:
	void Init();

	void Step();

	void Draw();

	void Fin();
};