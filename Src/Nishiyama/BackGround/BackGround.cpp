#include <math.h>

#include "DxLib.h"
#include "BackGround.h"

BackGround::BackGround()
{
	speed = 0.0f;
	ResultBackCount = 0;
	memset(&kind, 0, sizeof(BackGroundKind));
	for (int i = 0; i < BACK_GROUND_NUM; i++)
	{
		memset(&BG_Image[i], 0, sizeof(Rect_Data));
	}

	//for (int i = 0; i < 3; i++)
	//{
	//	BgHundl[0][i] = -1;
	//	BgHundl[1][i] = -1;
	//}
}

BackGround::~BackGround()
{

}

void BackGround::Init(BackGroundKind Kind)
{
	speed = BACK_GROUND_DEFAULT_SPEED;
	ResultBackCount = 0;
	kind = Kind;

	for (int i = 0; i < BACK_GROUND_NUM; i++)
	{
		BG_Image[i].RectInit(LoadGraph(BACK_GROUND_PATH[(int)kind] ), VGet((float)BACK_GROUND_SIZEW * i, 0.0f, 0.0f), BACK_GROUND_SIZEW, BACK_GROUND_SIZEH);
	}

	for (int i = 0; i < 2; i++)
	{
		BgHundl[i][0] = LoadGraph("Data/Play/sky.png");
		BgHundl[i][1] = LoadGraph("Data/Play/cloud.png");
		BgHundl[i][2] = LoadGraph("Data/Play/building.png");
	}
	/*BgPosX = 0;*/
}

void BackGround::Step()
{
	speed = (float)BACK_GROUND_DEFAULT_SPEED;

	BG_Image[ResultBackCount].Move_X(-speed);

	for (int i = ResultBackCount + 1; i != ResultBackCount; i++)
	{
		if (i == BACK_GROUND_NUM)
		{
			i = 0;
			if (ResultBackCount == 0)
				break;
		}
		if (i == 0)
		{
			BG_Image[i].Set_posX(BG_Image[BACK_GROUND_NUM - 1].Get_posX() + (float)BACK_GROUND_SIZEW);
		}
		else
		{
			BG_Image[i].Set_posX(BG_Image[i - 1].Get_posX() + (float)BACK_GROUND_SIZEW);
		}
	}
	if (-BACK_GROUND_OVER > BG_Image[ResultBackCount].Get_pos().x)
	{
		if (ResultBackCount == 0)
		{
			BG_Image[ResultBackCount].Set_posX(BG_Image[BACK_GROUND_NUM - 1].Get_posX() + (float)BACK_GROUND_SIZEW);
		}
		else
		{
			BG_Image[ResultBackCount].Set_posX(BG_Image[ResultBackCount - 1].Get_posX() + (float)BACK_GROUND_SIZEW);
		}
		ResultBackCount++;
		if (ResultBackCount >= BACK_GROUND_NUM)
		{
			ResultBackCount = 0;
		}
	}

	/*BgPosX -= 10;

	if (BgPosX <= 0)
	{
		BgPosX = 1280;
	}*/
}

void BackGround::Draw()
{
	
	unsigned int color[BACK_GROUND_NUM] =
	{
		GetColor(255, 0, 0),
		GetColor(0, 255, 0),
		GetColor(0, 0, 255)
	};
	for (int i = 0; i < BACK_GROUND_NUM; i++)
	{
		//BG_Image[i].DrawRect();
		DrawBox((int)BG_Image[i].Get_pos().x, (int)BG_Image[i].Get_pos().y, (int)BG_Image[i].Get_pos().x + BACK_GROUND_SIZEW, (int)BG_Image[i].Get_pos().y + BACK_GROUND_SIZEH, color[i], true);
	}

	/*for (int i = 0; i < 2; i++)
	{
		for (int a = 0; a < 3; a++)
		{
			DrawGraph(BgPosX + i * 1280, 0, BgHundl[i][a], false);
		}
	}*/
}

void BackGround::Fin()
{
	for (int i = 0; i < BACK_GROUND_NUM; i++)
	{
		BG_Image[i].RectFin();
	}
}