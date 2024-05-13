#include "MapEditor.h"
#include "../Input/Input.h"

MapEditor::MapEditor()
{
	memset(&screenPos, 0, sizeof(VECTOR));

	MoveFlag = false;

	currentEditMapID = 0;
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
	MoveFlag = false;

	currentEditMapID = 0;
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

	DrawRate = 1.0f;

	if (!gimmickID.empty())
	{
		gimmickID.erase(gimmickID.begin(), gimmickID.end());
	}
}

void MapEditor::Step()
{
	int MouseState = GetMouseInput();
	//�}�b�v�g�k
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

	//�}�b�v�ړ�
	if (!MoveNowFlag)
	{
		if ((MouseState & MOUSE_INPUT_RIGHT) != 0)
		{
			//������Ă���
			if (MoveFlag == false)
			{
				//������Â��Ă��Ȃ�
				MoveFlag = true;
				
				MoveNowFlag = true;
				MouseLogPos = Input::GetMousePos();
			}
		}
		else
		{
			//������Ă��Ȃ�
			MoveFlag = false;
		}
	}
	else
	{
		if ((MouseState & MOUSE_INPUT_RIGHT) != 0)
		{
			//������Ă���
			screenPos.x -= Input::GetMousePos().x - MouseLogPos.x;
			screenPos.y -= Input::GetMousePos().y - MouseLogPos.y;

			MouseLogPos = Input::GetMousePos();
		}
		else
		{
			//������Ă��Ȃ�
			if (MoveFlag == true)
			{
				//������Â��Ă���
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

	//�c�[���ύX
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
				//������Ă���
				if (toolSelectFlag == false)
				{
					//������Â��Ă��Ȃ�
					toolSelectFlag = true;

					currentToolID = 0;
					currentSelectTool = (EditTool)i;
				}
			}
			else
			{
				//������Ă��Ȃ�
				toolSelectFlag = false;
			}
		}
		else
		{
			toolSelectFlag = false;
		}
	}

	switch (currentSelectTool)
	{
	case EditTool::Block:
		for (int i = 0; i < (int)MAPCHIP_KIND::KindNum; i++)
		{
			VECTOR mouse = Input::GetMousePos();
			if (mouse.x > EDIT_TOOL_ELEMENT_X_OFFSET + (EDIT_TOOL_ELEMENT_X_OFFSET + MAPCHIP_SIZE) * i &&
				mouse.y > EDIT_TOOL_ELEMENT_Y &&
				mouse.x < EDIT_TOOL_ELEMENT_X_OFFSET + (EDIT_TOOL_ELEMENT_X_OFFSET + MAPCHIP_SIZE) * i + MAPCHIP_SIZE &&
				mouse.y < EDIT_TOOL_ELEMENT_Y + MAPCHIP_SIZE)
			{
				if ((MouseState & MOUSE_INPUT_LEFT) != 0)
				{
					//������Ă���
					if (toolElementSelectFlag == false)
					{
						//������Â��Ă��Ȃ�
						toolElementSelectFlag = true;

						currentToolID = i;
					}
				}
				else
				{
					//������Ă��Ȃ�
					toolElementSelectFlag = false;
				}
			}
			else
			{
				toolElementSelectFlag = false;
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
	//�w�i
	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, GetColor(15, 15, 15), true);

	int chip_size = (int)((float)MAPCHIP_SIZE * DrawRate);	//�}�b�v�`�b�v�g�k
	//�ҏW�̈�w�i
	DrawBox((int)(chip_size * -MAPCHIP_OVER - screenPos.x),
		(int)(chip_size * -MAPCHIP_OVER - screenPos.y),
		(int)(chip_size * -MAPCHIP_OVER + chip_size * MAPCHIP_NUM_X - screenPos.x),
		(int)(chip_size * -MAPCHIP_OVER + chip_size * MAPCHIP_NUM_Y - screenPos.y)
		, GetColor(50, 50, 50), true);
	//��ʊO�̈�
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

	//UI �}�b�v�Z���N�g
	DrawBox(0, EDIT_TOOL_Y, MAP_SELECT_X, SCREEN_SIZE_Y, GetColor(110, 110, 110), true);
	//UI �c�[��
	DrawBox(0, 0, SCREEN_SIZE_X, EDIT_TOOL_Y, GetColor(30, 30, 30), true);
	DrawBox(0, EDIT_TOOL_SELECT_Y, SCREEN_SIZE_X, EDIT_TOOL_Y, GetColor(130, 130, 130), true);
	
	//�c�[���Z���N�g����
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

	//�c�[��.���e
	switch (currentSelectTool)
	{
	case EditTool::Block:
		//�c�[���A�C�R���\��
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
