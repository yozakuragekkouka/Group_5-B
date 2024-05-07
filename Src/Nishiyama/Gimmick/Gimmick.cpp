#include "Gimmick.h"

GimmickBase::GimmickBase()
{
	memset(&ID, 0, sizeof(GimmickID));

	Map_X = 0;
	Map_Y = 0;

	memset(&default_pos, 0, sizeof(VECTOR));
	memset(&pos, 0, sizeof(VECTOR));
}

GimmickBase::GimmickBase(int dataX, int dataY)
{
	memset(&ID, 0, sizeof(GimmickID));

	Map_X = 0;
	Map_Y = 0;

	default_pos = VGet(-(MAPCHIP_SIZE * MAPCHIP_OVER) + MAPCHIP_SIZE * Map_X + MAPCHIP_SIZE / 2,
		-(MAPCHIP_SIZE * MAPCHIP_OVER) + MAPCHIP_SIZE * Map_X + MAPCHIP_SIZE / 2,
		0.0f);
	pos = default_pos;
}
