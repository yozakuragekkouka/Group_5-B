#include "MapEditor.h"
#include "../Input/Input.h"

MapEditor::MapEditor()
{
	memset(&screenPos, 0, sizeof(VECTOR));

	MoveFlag = false;

	currentEditMapID = 0;
	mapSelectFlag = false;

	currentSelectTool = EditTool::Block;
	toolSelectFlag = false;

	currentToolID = 0;
	toolElementSelectFlag = false;

	eraserImage = -1;
	for (int i = 0; i < (int)MAPCHIP_KIND::KindNum; i++)
	{
		mapImage[i] = -1;
	}

	memset(&data, 0, sizeof(MapData));

	MoveNowFlag = false;
	memset(&MouseLogPos, 0, sizeof(VECTOR));
	memset(&isSet, 0, sizeof(isSet));

	memset(&DrawRate, 0, sizeof(float));

	gimmick = nullptr;
}

MapEditor::~MapEditor()
{
	if (eraserImage != -1)
	{
		DeleteGraph(eraserImage);
	}
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
	screenPos.x = -200.0f;
	screenPos.y = -150.0f;

	MoveFlag = false;

	currentEditMapID = 0;
	mapSelectFlag = false;

	currentSelectTool = EditTool::Block;
	toolSelectFlag = false;

	currentToolID = 0;
	toolElementSelectFlag = false;

	eraserImage = LoadGraph(ERASER_PATH);

	for (int i = 0; i < (int)MAPCHIP_KIND::KindNum; i++)
	{
		if (i == (int)MAPCHIP_KIND::Air)
			continue;

		mapImage[i] = LoadGraph(MAPCHIP_PATH[i]);
	}

	MoveNowFlag = false;
	memset(&MouseLogPos, 0, sizeof(VECTOR));
	for (int j = 0; j < MAPCHIP_NUM_Y; j++)
	{
		for (int i = 0; i < MAPCHIP_NUM_X; i++)
		{
			isSet[j][i] = false;
		}
	}

	DrawRate = 0.75f;

	if (!gimmickID.empty())
	{
		gimmickID.erase(gimmickID.begin(), gimmickID.end());
	}

	int dummyInt = 0;
	GimmickID* dummyIDptr = nullptr;
	MapOperation::LoadMap(data, dummyInt, dummyIDptr, true, currentEditMapID);
	if (dummyInt > 0)
	{
		for (int i = 0; i < dummyInt; i++)
		{
			gimmickID.push_back(dummyIDptr[i]);
		}
		delete[] dummyIDptr;
	}
}

void MapEditor::Step()
{
	int MouseState = GetMouseInput();
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

	//マップ移動
	if (!MoveNowFlag)
	{
		if ((MouseState & MOUSE_INPUT_RIGHT) != 0)
		{
			//押されている
			if (MoveFlag == false)
			{
				//押されつづけていない
				MoveFlag = true;
				
				MoveNowFlag = true;
				MouseLogPos = Input::GetMousePos();
			}
		}
		else
		{
			//押されていない
			MoveFlag = false;
		}
	}
	else
	{
		if ((MouseState & MOUSE_INPUT_RIGHT) != 0)
		{
			//押されている
			screenPos.x -= Input::GetMousePos().x - MouseLogPos.x;
			screenPos.y -= Input::GetMousePos().y - MouseLogPos.y;

			MouseLogPos = Input::GetMousePos();
		}
		else
		{
			//押されていない
			if (MoveFlag == true)
			{
				//押されつづけていた
				MoveFlag = false;

				MoveNowFlag = false;
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

	//ツール変更
	for (int i = 0; i < (int)EditTool::KindNum; i++)
	{
		VECTOR mouse = Input::GetMousePos();
		if (mouse.x > EDIT_TOOL_SELECT_X_OFFSET + (EDIT_TOOL_SELECT_X_OFFSET + EDIT_TOOL_SELECT_SIZE_X) * i &&
			mouse.y > 0 &&
			mouse.x < EDIT_TOOL_SELECT_X_OFFSET + (EDIT_TOOL_SELECT_X_OFFSET + EDIT_TOOL_SELECT_SIZE_X) * i + EDIT_TOOL_SELECT_SIZE_X &&
			mouse.y < EDIT_TOOL_SELECT_Y)
		{
			if ((MouseState & MOUSE_INPUT_LEFT) != 0)
			{
				//押されている
				if (toolSelectFlag == false)
				{
					//押されつづけていない
					toolSelectFlag = true;

					currentToolID = 0;
					currentSelectTool = (EditTool)i;
				}
			}
			else
			{
				//押されていない
				toolSelectFlag = false;
			}
		}
		else
		{
			toolSelectFlag = false;
		}
	}

	//マップ変更
	for (int i = 0; i < EDIT_MAP_NUM; i++)
	{
		VECTOR mouse = Input::GetMousePos();
		if (mouse.x > 0 &&
			mouse.y > EDIT_TOOL_Y + MAP_SELECT_Y_OFFSET + (MAP_SELECT_Y_OFFSET + MAP_SELECT_SIZE_Y) * i &&
			mouse.x < MAP_SELECT_X &&
			mouse.y < EDIT_TOOL_Y + MAP_SELECT_Y_OFFSET + (MAP_SELECT_Y_OFFSET + MAP_SELECT_SIZE_Y) * i + MAP_SELECT_SIZE_Y)
		{
			if ((MouseState & MOUSE_INPUT_LEFT) != 0)
			{
				//押されている
				if (mapSelectFlag == false)
				{
					//押されつづけていない
					mapSelectFlag = true;

					int dummyInt = 0;
					GimmickID* dummyIDptr = nullptr;
					if (!gimmickID.empty())
					{
						dummyInt = (int)(gimmickID.size() / sizeof(int));
						dummyIDptr = new GimmickID[dummyInt];
						int count = 0;
						for (auto element : gimmickID)
						{
							dummyIDptr[count] = element;
							count++;
						}
					}

					MapOperation::SaveMap(data, dummyInt, dummyIDptr, true, currentEditMapID);
					if (!gimmickID.empty())
					{
						dummyInt = 0;
						delete[] dummyIDptr;
						gimmickID.erase(gimmickID.begin(), gimmickID.end());
					}

					currentEditMapID = i;
					MapOperation::LoadMap(data, dummyInt, dummyIDptr, true, currentEditMapID);
					if (dummyInt > 0)
					{
						for (int i = 0; i < dummyInt; i++)
						{
							gimmickID.push_back(dummyIDptr[i]);
						}
						delete[] dummyIDptr;
					}
				}
			}
			else
			{
				//押されていない
				mapSelectFlag = false;
			}
		}
		else
		{
			mapSelectFlag = false;
		}
	}

	float chip_size = ((float)MAPCHIP_SIZE * DrawRate);	//マップチップ一枚当たりの領域
	switch (currentSelectTool)
	{
	case EditTool::Block:
		VECTOR mouse = Input::GetMousePos();
		for (int i = 0; i < (int)MAPCHIP_KIND::KindNum; i++)
		{
			if (mouse.x > EDIT_TOOL_ELEMENT_X_OFFSET + (EDIT_TOOL_ELEMENT_X_OFFSET + MAPCHIP_SIZE) * i &&
				mouse.y > EDIT_TOOL_ELEMENT_Y &&
				mouse.x < EDIT_TOOL_ELEMENT_X_OFFSET + (EDIT_TOOL_ELEMENT_X_OFFSET + MAPCHIP_SIZE) * i + MAPCHIP_SIZE &&
				mouse.y < EDIT_TOOL_ELEMENT_Y + MAPCHIP_SIZE)
			{
				if ((MouseState & MOUSE_INPUT_LEFT) != 0)
				{
					//押されている
					if (toolElementSelectFlag == false)
					{
						//押されつづけていない
						toolElementSelectFlag = true;

						currentToolID = i;
					}
				}
				else
				{
					//押されていない
					toolElementSelectFlag = false;
				}
			}
			else
			{
				toolElementSelectFlag = false;
			}
		}

		//ブロック設置
		if ((MouseState & MOUSE_INPUT_LEFT) == 0)
		{
			memset(&isSet, 0, sizeof(isSet));
		}
		else
		{
			if (mouse.x > (float)MAP_SELECT_X &&
				mouse.y > (float)EDIT_TOOL_Y &&
				mouse.x < (float)SCREEN_SIZE_X &&
				mouse.y < (float)SCREEN_SIZE_Y)
			{
				for (int j = 0; j < MAPCHIP_NUM_Y; j++)
				{
					for (int i = 0; i < MAPCHIP_NUM_X; i++)
					{

						if (mouse.x > (chip_size * -MAPCHIP_OVER + chip_size * i - screenPos.x) &&
							mouse.y > (chip_size * -MAPCHIP_OVER + chip_size * j - screenPos.y) &&
							mouse.x < (chip_size * -MAPCHIP_OVER + chip_size * (i + 1) - screenPos.x) &&
							mouse.y < (chip_size * -MAPCHIP_OVER + chip_size * (j + 1) - screenPos.y))
						{
							if ((MouseState & MOUSE_INPUT_LEFT) != 0)
							{
								//押されている
								if (isSet[j][i] == false)
								{
									data[j][i] = (MAPCHIP_KIND)currentToolID;
									isSet[j][i] = true;
								}
							}
						}
					}
				}
			}
		}
		break;
	case EditTool::Gimmick:
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
	
	//ツールセレクト文字
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
	
	//マップセレクト文字
	for (int i = 0; i < EDIT_MAP_NUM; i++)
	{
		unsigned int BoxColor = GetColor(80, 80, 80);
		if (i == currentEditMapID)
		{
			BoxColor = GetColor(150, 150, 150);
		}
		DrawBox(0,
			EDIT_TOOL_Y + MAP_SELECT_Y_OFFSET + (MAP_SELECT_Y_OFFSET + MAP_SELECT_SIZE_Y) * i,
			MAP_SELECT_X,
			EDIT_TOOL_Y + MAP_SELECT_Y_OFFSET + (MAP_SELECT_Y_OFFSET + MAP_SELECT_SIZE_Y) * i + MAP_SELECT_SIZE_Y,
			BoxColor, true);

		DrawFormatString(0,
			EDIT_TOOL_Y + MAP_SELECT_Y_OFFSET + (MAP_SELECT_Y_OFFSET + MAP_SELECT_SIZE_Y) * i + 20,
			GetColor(255, 255, 255),
			"EDIT MAP %d", i + 1);
	}

	//ツール.内容
	switch (currentSelectTool)
	{
	case EditTool::Block:
		//ツールアイコン表示
		for (int i = 0; i < (int)MAPCHIP_KIND::KindNum; i++)
		{
			if (i == (int)MAPCHIP_KIND::Air)
			{
				if (eraserImage != -1)
				{
					DrawExtendGraph(EDIT_TOOL_ELEMENT_X_OFFSET + (EDIT_TOOL_ELEMENT_X_OFFSET + MAPCHIP_SIZE) * i,
						EDIT_TOOL_ELEMENT_Y,
						EDIT_TOOL_ELEMENT_X_OFFSET + (EDIT_TOOL_ELEMENT_X_OFFSET + MAPCHIP_SIZE) * i + MAPCHIP_SIZE,
						EDIT_TOOL_ELEMENT_Y + MAPCHIP_SIZE,
						eraserImage, true);
				}
				else
				{
					DrawBox(EDIT_TOOL_ELEMENT_X_OFFSET + (EDIT_TOOL_ELEMENT_X_OFFSET + MAPCHIP_SIZE) * i,
						EDIT_TOOL_ELEMENT_Y,
						EDIT_TOOL_ELEMENT_X_OFFSET + (EDIT_TOOL_ELEMENT_X_OFFSET + MAPCHIP_SIZE) * i + MAPCHIP_SIZE,
						EDIT_TOOL_ELEMENT_Y + MAPCHIP_SIZE,
						GetColor(255, 0, 0), true);
				}
				continue;
			}

			if (mapImage[i] != -1)
			{
				DrawExtendGraph(EDIT_TOOL_ELEMENT_X_OFFSET + (EDIT_TOOL_ELEMENT_X_OFFSET + MAPCHIP_SIZE) * i,
					EDIT_TOOL_ELEMENT_Y,
					EDIT_TOOL_ELEMENT_X_OFFSET + (EDIT_TOOL_ELEMENT_X_OFFSET + MAPCHIP_SIZE) * i + MAPCHIP_SIZE,
					EDIT_TOOL_ELEMENT_Y + MAPCHIP_SIZE,
					mapImage[i], true);
			}
			else
			{
				DrawBox(EDIT_TOOL_ELEMENT_X_OFFSET + (EDIT_TOOL_ELEMENT_X_OFFSET + MAPCHIP_SIZE) * i,
					EDIT_TOOL_ELEMENT_Y,
					EDIT_TOOL_ELEMENT_X_OFFSET + (EDIT_TOOL_ELEMENT_X_OFFSET + MAPCHIP_SIZE) * i + MAPCHIP_SIZE,
					EDIT_TOOL_ELEMENT_Y + MAPCHIP_SIZE,
					GetColor(255, 0, 0), true);
			}
		}
		VECTOR mouse = Input::GetMousePos();
		if (currentToolID == (int)MAPCHIP_KIND::Air)
		{
			if (eraserImage != -1)
			{
				DrawExtendGraphF(mouse.x + 10.0f,
					mouse.y + 10.0f,
					mouse.x + 20.0f,
					mouse.y + 20.0f,
					eraserImage, true);
			}
			else
			{
				DrawBox((int)mouse.x + 10,
					(int)mouse.y + 10,
					(int)mouse.x + 20,
					(int)mouse.y + 20,
					GetColor(255, 0, 0), true);
			}
		}
		else
		{
			if (mapImage[currentToolID] != -1)
			{
				DrawExtendGraphF(mouse.x + 10.0f,
					mouse.y + 10.0f,
					mouse.x + 20.0f,
					mouse.y + 20.0f,
					mapImage[currentToolID], true);
			}
			else
			{
				DrawBox((int)mouse.x + 10,
					(int)mouse.y + 10,
					(int)mouse.x + 20,
					(int)mouse.y + 20,
					GetColor(255, 0, 0), true);
			}
		}
		break;

	case EditTool::Gimmick:
		break;
	default:
		break;
	}
}

void MapEditor::Fin()
{
	//最後のマップも保存
	int dummyInt = 0;
	GimmickID* dummyIDptr = nullptr;
	if (!gimmickID.empty())
	{
		dummyInt = (int)(gimmickID.size() / sizeof(int));
		dummyIDptr = new GimmickID[dummyInt];
		int count = 0;
		for (auto element : gimmickID)
		{
			dummyIDptr[count] = element;
			count++;
		}
	}

	MapOperation::SaveMap(data, dummyInt, dummyIDptr, true, currentEditMapID);


	if (!gimmickID.empty())
	{
		dummyInt = 0;
		delete[] dummyIDptr;
		gimmickID.erase(gimmickID.begin(), gimmickID.end());
	}

	if (eraserImage != -1)
	{
		DeleteGraph(eraserImage);
		eraserImage = -1;
	}

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
