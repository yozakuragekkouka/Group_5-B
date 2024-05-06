#pragma once

constexpr int MAPCHIP_SIZE = 32;

constexpr int MAPCHIP_OVER = 2;

constexpr int MAPCHIP_NUM_X = SCREEN_SIZE_X / MAPCHIP_SIZE + MAPCHIP_OVER * 2;
constexpr int MAPCHIP_NUM_Y = SCREEN_SIZE_Y / MAPCHIP_SIZE + MAPCHIP_OVER * 2;

enum class MAPCHIP_KIND
{
	Air,

	KindNum
};

constexpr char MAPCHIP_PATH[(int)MAPCHIP_KIND::KindNum][128] =
{
	"",
};

typedef MAPCHIP_KIND MapData[MAPCHIP_NUM_Y][MAPCHIP_NUM_X];