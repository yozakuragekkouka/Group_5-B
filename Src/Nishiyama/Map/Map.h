#pragma once
#include "MapData.h"
#include "../Gimmick/Gimmick.h"

class Map
{
private:
	int mapImage[(int)MAPCHIP_KIND::KindNum];
	MapData data;
	
	int gimmick_Num;
	GimmickID* gimmickID;
	GimmickBase** gimmick;

public:
	Map();
	~Map();

	void Init(bool isEdit, int MapID);
	void Step();
	void Draw();
	void Fin();

	MAPCHIP_KIND GetData(int x, int y) {return data[y][x];}
};
