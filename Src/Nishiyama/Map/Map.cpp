#include "../../Common.h"
#include "Map.h"

Map::Map()
{
	for (int i = 0; i < (int)MAPCHIP_KIND::KindNum; i++)
	{
		mapImage[i] = -1;
	}

	memset(&data, 0, sizeof(MapData));

	gimmick_Num = 0;
	gimmickID = nullptr;
	gimmick = nullptr;
}

Map::~Map()
{
	for (int i = 0; i < (int)MAPCHIP_KIND::KindNum; i++)
	{
		if (mapImage[i] != -1)
		{
			DeleteGraph(mapImage[i]);
		}
	}
	if (gimmick != nullptr)
	{
		if (*gimmick != nullptr)
		{
			delete[] *gimmick;
		}
		delete[] gimmick;
	}
}

void Map::Init(bool isEdit, int MapID)
{
	for (int i = 0; i < (int)MAPCHIP_KIND::KindNum; i++)
	{
		if (i == (int)MAPCHIP_KIND::Air)
			continue;

		mapImage[i] = LoadGraph(MAPCHIP_PATH[i]);
	}

	MapOperation::LoadMap(data, gimmick_Num, gimmickID, isEdit, MapID);

	if (gimmick_Num > 0)
	{
		gimmick = new GimmickBase * [gimmick_Num];

		for (int i = 0; i < gimmick_Num; i++)
		{
			switch (gimmickID[i])
			{
			case GimmickID::yaiba:
				//gimmick[i] = new a;
				gimmick[i]->Init();
				break;
			default:
				break;
			}
		}
	}
}

void Map::Step()
{
	if (gimmick_Num > 0)
	{
		if (gimmick != nullptr && *gimmick != nullptr)
		{
			for (int i = 0; i < gimmick_Num; i++)
			{
				gimmick[i]->Step();
			}
		}
	}
}

void Map::Draw()
{
	for (int j = 0; j < MAPCHIP_NUM_Y; j++)
	{
		for (int i = 0; i < MAPCHIP_NUM_X; i++)
		{
			if (data[j][i] == MAPCHIP_KIND::Air)
				continue;

			if (mapImage[(int)data[j][i]] != -1)
			{
				DrawGraph(MAPCHIP_SIZE * -MAPCHIP_OVER + MAPCHIP_SIZE * i,
					MAPCHIP_SIZE * -MAPCHIP_OVER + MAPCHIP_SIZE * j,
					mapImage[(int)data[j][i]],
					true);
			}
			else
			{
				DrawBox(MAPCHIP_SIZE * -MAPCHIP_OVER + MAPCHIP_SIZE * i,
					MAPCHIP_SIZE * -MAPCHIP_OVER + MAPCHIP_SIZE * j,
					MAPCHIP_SIZE * -MAPCHIP_OVER + MAPCHIP_SIZE * (i + 1),
					MAPCHIP_SIZE * -MAPCHIP_OVER + MAPCHIP_SIZE * (j + 1),
					GetColor(255, 0, 0),
					true);
			}
		}
	}

	if (gimmick_Num > 0)
	{
		if (gimmick != nullptr && *gimmick != nullptr)
		{
			for (int i = 0; i < gimmick_Num; i++)
			{
				gimmick[i]->Draw();
			}
			
		}
	}

}

void Map::Fin()
{
	for (int i = 0; i < (int)MAPCHIP_KIND::KindNum; i++)
	{
		if (mapImage[i] != -1)
		{
			DeleteGraph(mapImage[i]);
			mapImage[i] = -1;
		}
	}
	if (gimmick != nullptr)
	{
		if (*gimmick != nullptr)
		{
			delete[] * gimmick;
			*gimmick = nullptr;
		}
		delete[] gimmick;
		gimmick = nullptr;
	}
}
