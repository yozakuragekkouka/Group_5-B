#include "MapEditor.h"
#include "../Input/Input.h"

MapEditor::MapEditor()
{
	memset(&screenPos, 0, sizeof(VECTOR));

	currentEditMapID = 0;
	currentSelectTool = EditTool::Move;
	toolSelectFlag = false;

	currentToolID = 0;

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
	currentEditMapID = 0;
	currentSelectTool = EditTool::Move;
	toolSelectFlag = false;

	currentToolID = 0;

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
	//マップ拡縮
	if (Input::GetMouseWheelRota() > 0)
	{
		int BufInt = (int)(DrawRate * 100.0f);

		if (BufInt <= 10)
		{
			BufInt = 15;
		}
		else if(BufInt < 200)
		{
			BufInt += 5;
		}

		if (BufInt >= 200)
		{
			BufInt = 200;
		}

		DrawRate = (float)BufInt / 100.0f;
	}
	else if (Input::GetMouseWheelRota() < 0)
	{
		int BufInt = (int)(DrawRate * 100.0f);

		BufInt -= 5;

		if (BufInt <= 10)
		{
			BufInt = 10;
		}

		DrawRate = (float)BufInt / 100.0f;
	}

	//ツール変更
	for (int i = 0; i < (int)EditTool::KindNum; i++)
	{
		VECTOR mouse = Input::GetMousePos();
		if (mouse.x > EDIT_TOOL_SELECT_X_OFFSET + (EDIT_TOOL_SELECT_X_OFFSET + EDIT_TOOL_SELECT_SIZE_X) * i &&
			mouse.y > 0 &&
			mouse.y < EDIT_TOOL_SELECT_X_OFFSET + (EDIT_TOOL_SELECT_X_OFFSET + EDIT_TOOL_SELECT_SIZE_X) * i + EDIT_TOOL_SELECT_SIZE_X &&
			mouse.y < EDIT_TOOL_SELECT_Y)
		{
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
			{
				//押されている
				if (toolSelectFlag == false)
				{
					//押されつづけていない
					MoveFlag = false;
					memset(&MouseLogPos, 0, sizeof(VECTOR));

					currentSelectTool = (EditTool)i;
				}
			}
			else
			{
				//押されていない
				toolSelectFlag = false;
			}
		}
	}

	switch (currentSelectTool)
	{
	case EditTool::Move:
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
		break;
	case EditTool::Draw:
		break;
	default:
		break;
	}
	
}

void MapEditor::Draw()
{
	//背景
	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, GetColor(15, 15, 15), true);

	int chip_size = (int)((float)MAPCHIP_SIZE * DrawRate);	//マップチップ拡縮
	//編集領域背景
	DrawBox((int)(chip_size * -MAPCHIP_OVER - screenPos.x),
		(int)(chip_size * -MAPCHIP_OVER - screenPos.y),
		(int)(chip_size * -MAPCHIP_OVER + chip_size * MAPCHIP_NUM_X - screenPos.x),
		(int)(chip_size * -MAPCHIP_OVER + chip_size * MAPCHIP_NUM_Y - screenPos.y)
		, GetColor(50, 50, 50), true);
	//画面外領域
	DrawBox((int)(chip_size * -MAPCHIP_OVER - screenPos.x),
		(int)(chip_size * -MAPCHIP_OVER - screenPos.y),
		(int)(chip_size * -MAPCHIP_OVER + chip_size * 2 - screenPos.x),
		(int)(chip_size * -MAPCHIP_OVER + chip_size * MAPCHIP_NUM_Y - screenPos.y)
		, GetColor(40, 40, 40), true);
	DrawBox((int)(chip_size * -MAPCHIP_OVER + chip_size * (MAPCHIP_NUM_X - 2) - screenPos.x),
		(int)(chip_size * -MAPCHIP_OVER - screenPos.y),
		(int)(chip_size * -MAPCHIP_OVER + chip_size * MAPCHIP_NUM_X - screenPos.x),
		(int)(chip_size * -MAPCHIP_OVER + chip_size * MAPCHIP_NUM_Y - screenPos.y)
		, GetColor(40, 40, 40), true);
	DrawBox((int)(chip_size * -MAPCHIP_OVER - screenPos.x),
		(int)(chip_size * -MAPCHIP_OVER - screenPos.y),
		(int)(chip_size * -MAPCHIP_OVER + chip_size * MAPCHIP_NUM_X - screenPos.x),
		(int)(chip_size * -MAPCHIP_OVER + chip_size * 2 - screenPos.y)
		, GetColor(40, 40, 40), true);
	DrawBox((int)(chip_size * -MAPCHIP_OVER - screenPos.x),
		(int)(chip_size * -MAPCHIP_OVER + chip_size * (MAPCHIP_NUM_Y - 2) - screenPos.y),
		(int)(chip_size * -MAPCHIP_OVER + chip_size * MAPCHIP_NUM_X - screenPos.x),
		(int)(chip_size * -MAPCHIP_OVER + chip_size * MAPCHIP_NUM_Y - screenPos.y)
		, GetColor(40, 40, 40), true);

	for (int j = 0; j < MAPCHIP_NUM_Y; j++)
	{
		for (int i = 0; i < MAPCHIP_NUM_X; i++)
		{
			if (data[j][i] == MAPCHIP_KIND::Air)
				continue;

			if (mapImage[(int)data[j][i]] != -1)
			{
				DrawExtendGraph((int)(chip_size * -MAPCHIP_OVER + chip_size * i - screenPos.x),
					(int)(chip_size * -MAPCHIP_OVER + chip_size * j - screenPos.y),
					(int)(chip_size * -MAPCHIP_OVER + chip_size * (i + 1) - screenPos.x),
					(int)(chip_size * -MAPCHIP_OVER + chip_size * (j + 1) - screenPos.y),
					mapImage[(int)data[j][i]],
					true);
			}
			else
			{
				DrawBox((int)(chip_size * -MAPCHIP_OVER + chip_size * i - screenPos.x),
					(int)(chip_size * -MAPCHIP_OVER + chip_size * j - screenPos.y),
					(int)(chip_size * -MAPCHIP_OVER + chip_size * (i + 1) - screenPos.x),
					(int)(chip_size * -MAPCHIP_OVER + chip_size * (j + 1) - screenPos.y),
					GetColor(255, 0, 0),
					true);
			}
		}
	}

	//UI マップセレクト
	DrawBox(0, EDIT_TOOL_Y, MAP_SELECT_X, SCREEN_SIZE_Y, GetColor(110, 110, 110), true);
	//UI ツール
	DrawBox(0, 0, SCREEN_SIZE_X, EDIT_TOOL_Y, GetColor(30, 30, 30), true);
	DrawBox(0, EDIT_TOOL_SELECT_Y, SCREEN_SIZE_X, EDIT_TOOL_Y, GetColor(130, 130, 130), true);

	for (int i = 0; i < (int)EditTool::KindNum; i++)
	{
		unsigned int BoxColor = GetColor(80, 80, 80);
		if (i == (int)currentSelectTool)
		{
			BoxColor = GetColor(125, 125, 125);
		}
		DrawBox(EDIT_TOOL_SELECT_X_OFFSET + (EDIT_TOOL_SELECT_X_OFFSET + EDIT_TOOL_SELECT_SIZE_X) * i,
			0,
			EDIT_TOOL_SELECT_X_OFFSET + (EDIT_TOOL_SELECT_X_OFFSET + EDIT_TOOL_SELECT_SIZE_X) * i + EDIT_TOOL_SELECT_SIZE_X,
			EDIT_TOOL_SELECT_Y,
			BoxColor, true);

		DrawFormatString(EDIT_TOOL_SELECT_X_OFFSET + (EDIT_TOOL_SELECT_X_OFFSET + EDIT_TOOL_SELECT_SIZE_X) * i + 10,
			10,
			GetColor(255, 255, 255),
			EDIT_TOOL_NAME[i]);
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
