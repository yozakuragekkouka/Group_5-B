#pragma once
#include "../../Common.h"

constexpr int MAPCHIP_SIZE = 32;

constexpr int MAPCHIP_OVER = 2;

constexpr int MAPCHIP_NUM_X = SCREEN_SIZE_X / MAPCHIP_SIZE + MAPCHIP_OVER * 2;
constexpr int MAPCHIP_NUM_Y = SCREEN_SIZE_Y / MAPCHIP_SIZE + MAPCHIP_OVER * 2;

constexpr char ORIGINAL_MAP_PATH[5][128] =
{
	"aaaaa",
	"aaaaa",
	"aaaaa",
	"aaaaa",
	"aaaaa",
};

constexpr char EDIT_MAP_PATH[5][128] =
{
	"aaaaa",
	"aaaaa",
	"aaaaa",
	"aaaaa",
	"aaaaa",
};

enum class MAPCHIP_KIND
{
	Air,

	KindNum
};

enum class GimmickID
{
	NONE,

	KIND_NUM
};

constexpr char MAPCHIP_PATH[(int)MAPCHIP_KIND::KindNum][128] =
{
	"",
};

typedef MAPCHIP_KIND MapData[MAPCHIP_NUM_Y][MAPCHIP_NUM_X];

class MapOperation
{
public:
	static void LoadMap(MapData &chipData, int &gimmickNum, GimmickID *gimmickID);

	static void SaveMap(MapData &chipData, int &gimmickNum, GimmickID *gimmickID);
};