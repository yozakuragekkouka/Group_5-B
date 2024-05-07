#pragma once
#include "MapData.h"
#include "../Gimmick/Gimmick.h"

class Map
{
private:
	int mapImage[(int)MAPCHIP_KIND::KindNum];
	MapData data;
	
	const int gimmick_Num;
	GimmickID* gimmickID;
	GimmickBase** gimmick;

public:
	Map(int AllGimmickNum);
	~Map();

	void Init();
	void Step();
	void Draw();
	void Fin();
};
