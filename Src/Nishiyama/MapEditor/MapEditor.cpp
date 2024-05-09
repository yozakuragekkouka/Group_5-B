#include "MapEditor.h"
#include "../Input/Input.h"

MapEditor::MapEditor()
{
	memset(&screenPos, 0, sizeof(VECTOR));

	for (int i = 0; i < (int)MAPCHIP_KIND::KindNum; i++)
	{
		mapImage[i] = -1;
	}

	memset(&data, 0, sizeof(MapData));

	MoveFlag = false;
	memset(&MouseLogPos, 0, sizeof(VECTOR));
	memset(&isSet, 0, sizeof(isSet));

	memset(&DrawRate, 0, sizeof(float));

	gimmick = nullptr;
}

MapEditor::~MapEditor()
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
			delete[] * gimmick;
		}
		delete[] gimmick;
	}
}

void MapEditor::Init()
{
	for (int i = 0; i < (int)MAPCHIP_KIND::KindNum; i++)
	{
		if (i == (int)MAPCHIP_KIND::Air)
			continue;

		mapImage[i] = LoadGraph(MAPCHIP_PATH[i]);
	}

	MoveFlag = false;
	memset(&MouseLogPos, 0, sizeof(VECTOR));
	for (int j = 0; j < MAPCHIP_NUM_Y; j++)
	{
		for (int i = 0; i < MAPCHIP_NUM_X; i++)
		{
			isSet[j][i] = false;
		}
	}

	DrawRate = 1.0f;

	if (!gimmickID.empty())
	{
		gimmickID.erase(gimmickID.begin(), gimmickID.end());
	}
}

void MapEditor::Step()
{
	//�}�b�v�g�k
	if (GetMouseWheelRotVol() > 0)
	{
		int BufInt = (int)(DrawRate * 100.0f);

		if (BufInt <= 10)
		{
			BufInt = 25;
		}
		else if(BufInt < 200)
		{
			BufInt += 25;
		}

		if (BufInt >= 200)
		{
			BufInt = 200;
		}

		DrawRate = (float)BufInt / 100.0f;
	}
	else if (GetMouseWheelRotVol() < 0)
	{
		int BufInt = (int)(DrawRate * 100.0f);

		BufInt -= 25;

		if (BufInt <= 10)
		{
			BufInt = 10;
		}

		DrawRate = (float)BufInt / 100.0f;
	}

	if (!MoveFlag)
	{
		if (Input::Mouse_Click())
		{
			MoveFlag = true;
			MouseLogPos = Input::GetMousePos();
		}
	}
	else
	{
		if (Input::Mouse_Release())
		{
			MoveFlag = false;
			memset(&MouseLogPos, 0, sizeof(VECTOR));
		}
		else
		{
			screenPos.x -= Input::GetMousePos().x - MouseLogPos.x;
			screenPos.y -= Input::GetMousePos().y - MouseLogPos.y;

			MouseLogPos = Input::GetMousePos();
		}
	}
}

void MapEditor::Draw()
{
	for (int j = 0; j < MAPCHIP_NUM_Y; j++)
	{
		for (int i = 0; i < MAPCHIP_NUM_X; i++)
		{
			/*if (data[j][i] == MAPCHIP_KIND::Air)
				continue;*/

			if (mapImage[(int)data[j][i]] != -1)
			{
				DrawGraph((int)(MAPCHIP_SIZE * -MAPCHIP_OVER + MAPCHIP_SIZE * i - screenPos.x),
					(int)(MAPCHIP_SIZE * -MAPCHIP_OVER + MAPCHIP_SIZE * j - screenPos.y),
					mapImage[(int)data[j][i]],
					true);
			}
			else
			{
				DrawBox((int)(MAPCHIP_SIZE * -MAPCHIP_OVER + MAPCHIP_SIZE * i - screenPos.x),
					(int)(MAPCHIP_SIZE * -MAPCHIP_OVER + MAPCHIP_SIZE * j - screenPos.y),
					(int)(MAPCHIP_SIZE * -MAPCHIP_OVER + MAPCHIP_SIZE * (i + 1) - screenPos.x),
					(int)(MAPCHIP_SIZE * -MAPCHIP_OVER + MAPCHIP_SIZE * (j + 1) - screenPos.y),
					GetColor(255, 0, 0),
					true);
			}
		}
	}

}

void MapEditor::Fin()
{
	for (int i = 0; i < (int)MAPCHIP_KIND::KindNum; i++)
	{
		if (mapImage[i] != -1)
		{
			DeleteGraph(mapImage[i]);
			mapImage[i] = -1;
		}
	}

	if (!gimmickID.empty())
	{
		gimmickID.erase(gimmickID.begin(), gimmickID.end());
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
