#pragma once
#include "../../Common.h"

constexpr int MAPCHIP_SIZE = 32;

constexpr int MAPCHIP_OVER = 2;

constexpr int MAPCHIP_NUM_X = SCREEN_SIZE_X / MAPCHIP_SIZE + MAPCHIP_OVER * 2;
constexpr int MAPCHIP_NUM_Y = SCREEN_SIZE_Y / MAPCHIP_SIZE + MAPCHIP_OVER * 2;

constexpr char ORIGINAL_MAP_PATH[5][128] =
{
	"Data/MapData/OriginalMap/OriginalMap1.bin",
	"Data/MapData/OriginalMap/OriginalMap2.bin",
	"Data/MapData/OriginalMap/OriginalMap3.bin",
	"Data/MapData/OriginalMap/OriginalMap4.bin",
	"Data/MapData/OriginalMap/OriginalMap5.bin"
};

constexpr int EDIT_MAP_NUM = 5;
constexpr char EDIT_MAP_PATH[EDIT_MAP_NUM][128] =
{
	"Data/MapData/EditMap/EditMap1.bin",
	"Data/MapData/EditMap/EditMap2.bin",
	"Data/MapData/EditMap/EditMap3.bin",
	"Data/MapData/EditMap/EditMap4.bin",
	"Data/MapData/EditMap/EditMap5.bin",
};

enum class MAPCHIP_KIND
{
	Air,
	WhiteBlock,
	WhitePillar,
	WhiteRenga,

	KindNum
};

enum class GimmickID
{
	yaiba,

	KIND_NUM
};

constexpr char MAPCHIP_PATH[(int)MAPCHIP_KIND::KindNum][128] =
{
	"",
	"Data/Image/Map/WhiteBlock.png",
	"Data/Image/Map/WhitePillar.png",
	"Data/Image/Map/WhiteRenga.png",
};

typedef MAPCHIP_KIND MapData[MAPCHIP_NUM_Y][MAPCHIP_NUM_X];

class MapOperation
{
public:
	static void LoadMap(MapData &chipData, int &gimmickNum, GimmickID *gimmickID, bool isEdit, int MapID);

	static void SaveMap(MapData &chipData, int &gimmickNum, GimmickID *gimmickID, bool isEdit, int MapID);
};