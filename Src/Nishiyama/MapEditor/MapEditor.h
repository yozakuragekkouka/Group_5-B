#pragma once
#include <vector>
#include "DxLib.h"
#include "../Map/MapData.h"
#include "../Gimmick/Gimmick.h"

class MapEditor
{
private:
	VECTOR screenPos;

	int mapImage[(int)MAPCHIP_KIND::KindNum];
	MapData data;

	bool MoveFlag;
	VECTOR MouseLogPos;
	bool isSet[MAPCHIP_NUM_Y][MAPCHIP_NUM_X];

	float DrawRate;

	std::vector<GimmickID> gimmickID;
	GimmickBase** gimmick;

public:
	MapEditor();
	~MapEditor();

	void Init();
	void Step();
	void Draw();
	void Fin();
};