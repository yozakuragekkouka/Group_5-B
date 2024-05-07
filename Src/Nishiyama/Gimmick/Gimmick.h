#pragma once
#include "DxLib.h"
#include "../Map/MapData.h"

class GimmickBase
{
protected:
	GimmickID ID;

	int Map_X;
	int Map_Y;

	VECTOR default_pos;
	VECTOR pos;

public:
	GimmickBase();
	GimmickBase(int dataX, int dataY);

	virtual void Init() = 0;
	virtual void Step() = 0;
	virtual void Draw() = 0;
	virtual void Fin() = 0;
};