#pragma once
#include "../../Common.h"

constexpr int MAPCHIP_SIZE = 32;

constexpr int MAPCHIP_NUM_X = SCREEN_SIZE_X / MAPCHIP_SIZE;
constexpr int MAPCHIP_NUM_Y = SCREEN_SIZE_Y / MAPCHIP_SIZE;

enum class MAPCHIP_KIND
{
	Air,

	KindNum
};

typedef MAPCHIP_KIND MapData[MAPCHIP_NUM_Y][MAPCHIP_NUM_X];

class Map
{
private:
	MapData data;

public:
	Map();

	void Init();
	void Step();
	void Draw();
	void Fin();
};
