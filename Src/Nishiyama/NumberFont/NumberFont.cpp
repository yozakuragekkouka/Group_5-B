#include <stdlib.h>
#include <math.h>
#include "DxLib.h"
#include "NumberFontData.h"
#include "NumberFont.h"

const char numberFontPath[NumberFontNum][256] =
{
	"Data/Image/Number/number4x8_00.png",
	"Data/Image/Number/number4x8_01.png",
	"Data/Image/Number/number4x8_02.png",
	"Data/Image/Number/number4x8_03.png",
	"Data/Image/Number/number4x8_04.png",
	"Data/Image/Number/number4x8_05.png",
	"Data/Image/Number/number4x8_06.png",
	"Data/Image/Number/number4x8_07.png",
	"Data/Image/Number/number6x12_00.png",
	"Data/Image/Number/number6x12_01.png",
	"Data/Image/Number/number6x12_02.png",
	"Data/Image/Number/number6x12_03.png",
	"Data/Image/Number/number6x12_04.png",
	"Data/Image/Number/number6x12_05.png",
	"Data/Image/Number/number6x12_06.png",
	"Data/Image/Number/number6x12_07.png",
	"Data/Image/Number/number8x16_00.png",
	"Data/Image/Number/number8x16_01.png",
	"Data/Image/Number/number8x16_02.png",
	"Data/Image/Number/number8x16_03.png",
	"Data/Image/Number/number8x16_04.png",
	"Data/Image/Number/number8x16_05.png",
	"Data/Image/Number/number8x16_06.png",
	"Data/Image/Number/number8x16_07.png",
	"Data/Image/Number/number12x24_00.png",
	"Data/Image/Number/number12x24_01.png",
	"Data/Image/Number/number12x24_02.png",
	"Data/Image/Number/number12x24_03.png",
	"Data/Image/Number/number12x24_04.png",
	"Data/Image/Number/number12x24_05.png",
	"Data/Image/Number/number12x24_06.png",
	"Data/Image/Number/number12x24_07.png",
	"Data/Image/Number/number16x32_00.png",
	"Data/Image/Number/number16x32_01.png",
	"Data/Image/Number/number16x32_02.png",
	"Data/Image/Number/number16x32_03.png",
	"Data/Image/Number/number16x32_04.png",
	"Data/Image/Number/number16x32_05.png",
	"Data/Image/Number/number16x32_06.png",
	"Data/Image/Number/number16x32_07.png"
};

c_Number::c_Number()
{
	for (int i = 0; i < 13; i++)
	{
		handle[i] = 0;
	}
	posX = 0;
	posY = 0;
	currentFontType = Number_4_8_white;
}

c_Number::~c_Number()
{
	for (int i = 0; i < 13; i++)
	{
		if (handle[i])
		{
			DeleteGraph(handle[i]);
		}
	}
	posX = 0;
	posY = 0;
	currentFontType = Number_4_8_white;
}

void c_Number::Init()
{
	for (int i = 0; i < 13; i++)
	{
		handle[i] = 0;
	}
	posX = 0;
	posY = 0;
	currentFontType = Number_4_8_white;
}

void c_Number::Fin()
{
	for (int i = 0; i < 13; i++)
	{
		if (handle[i] != 0)
		{
			DeleteGraph(handle[i]);
		}
	}
	posX = 0;
	posY = 0;
	currentFontType = Number_4_8_white;
}

void c_Number::SetNumberFont(NumberFontType fontType)
{
	for (int i = 0; i < 13; i++)
	{
		if (handle[i] != 0)
		{
			DeleteGraph(handle[i]);
		}
	}

	currentFontType = fontType;

	LoadDivGraph(numberFontPath[fontType], 13, 13, 1, fontData[fontType].sizeX, fontData[fontType].sizeY, handle);
}

void c_Number::Draw_int(const int drawNumber, bool RightFlag, bool PositionY_UnderFlag)
{
	int keisanyou = drawNumber;
	int numLen = 0;

	if (drawNumber == 0)
	{
		numLen = 1;
	}
	else
	{
		while (true)
		{
			if (keisanyou > 0)
			{
				keisanyou /= 10;
				numLen++;
			}
			else
			{
				break;
			}
		}
	}

	viewNum = (int*)malloc(sizeof(int) * numLen);

	for (int i = 0; i < numLen; i++)
	{
		viewNum[i] = drawNumber / (int)pow((double)10, ((double)numLen - 1 - i)) % 10;
	}

	if (RightFlag == false)
	{
		if (PositionY_UnderFlag == false)
		{
			for (int i = 0; i < numLen; i++)
			{
				DrawGraph(posX + fontData[currentFontType].sizeX * i, posY, handle[viewNum[i]], true);
			}
		}
		else if (PositionY_UnderFlag == true)
		{
			for (int i = 0; i < numLen; i++)
			{
				DrawGraph(posX + fontData[currentFontType].sizeX * i, posY - fontData[currentFontType].sizeY, handle[viewNum[i]], true);
			}
		}
	}

	if (RightFlag == true)
	{
		int currentNumLen = numLen;

		if (PositionY_UnderFlag == false)
		{
			for (int i = 0; i < numLen; i++)
			{
				DrawGraph(posX - fontData[currentFontType].sizeX * currentNumLen, posY, handle[viewNum[i]], true);

				currentNumLen--;
			}
		}
		if (PositionY_UnderFlag == true)
		{
			for (int i = 0; i < numLen; i++)
			{
				DrawGraph(posX - fontData[currentFontType].sizeX * currentNumLen, posY - fontData[currentFontType].sizeY, handle[viewNum[i]], true);

				currentNumLen--;
			}
		}
	}

	if (viewNum != NULL)
	{
		free(viewNum);
	}
}

void c_Number::Draw_float(float drawNumber, int shousu_n_keta, bool RightFlag, bool PositionY_UnderFlag)
{
	bool mainasu_Flag = false;
	if (drawNumber < 0.0f)
	{
		mainasu_Flag = true;
		drawNumber = fabsf(drawNumber);
	}

	int keisanyou = (int)(drawNumber * (int)pow((double)10, (double)shousu_n_keta));
	int numLen = 0;

	if (drawNumber < 1)
	{
		numLen = 1 + shousu_n_keta;
	}
	else
	{
		while (true)
		{
			if (keisanyou > 0)
			{
				keisanyou /= 10;
				numLen++;
			}
			else
			{
				keisanyou = (int)(drawNumber * (int)pow((double)10, (double)shousu_n_keta));
				break;
			}
		}
	}
	if (mainasu_Flag)
		numLen++;

	viewNum = (int*)malloc(sizeof(int) * numLen);

	if (mainasu_Flag)
	{
		viewNum[0] = 11;
		for (int i = 1; i < numLen; i++)
		{
			viewNum[i] = keisanyou / (int)pow((double)10, ((double)numLen - 1 - i)) % 10;
		}
	}
	else
	{
		for (int i = 0; i < numLen; i++)
		{
			viewNum[i] = keisanyou / (int)pow((double)10, ((double)numLen - 1 - i)) % 10;
		}
	}

	if (RightFlag == false)
	{
		if (PositionY_UnderFlag == false)
		{
			for (int i = 0; i < numLen - shousu_n_keta; i++)
			{
				DrawGraph(posX + fontData[currentFontType].sizeX * i, posY, handle[viewNum[i]], true);
			}

			DrawGraph(posX + fontData[currentFontType].sizeX * numLen, posY, handle[12], true);

			for (int i = 0; i < shousu_n_keta; i++)
			{
				DrawGraph(posX + fontData[currentFontType].sizeX * (numLen + 1 + i), posY, handle[viewNum[numLen - shousu_n_keta + i]], true);
			}
		}
		else if (PositionY_UnderFlag == true)
		{
			for (int i = 0; i < numLen; i++)
			{
				DrawGraph(posX + fontData[currentFontType].sizeX * i, posY - fontData[currentFontType].sizeY, handle[viewNum[i]], true);
			}

			DrawGraph(posX + fontData[currentFontType].sizeX * numLen, posY - fontData[currentFontType].sizeY, handle[12], true);

			for (int i = 0; i < shousu_n_keta; i++)
			{
				DrawGraph(posX + fontData[currentFontType].sizeX * (numLen + 1 + i), posY - fontData[currentFontType].sizeY, handle[viewNum[numLen - shousu_n_keta + i]], true);
			}
		}
	}

	if (RightFlag == true)
	{
		int currentNumLen = numLen + 1;

		if (PositionY_UnderFlag == false)
		{
			for (int i = 0; i < numLen - shousu_n_keta; i++)
			{
				DrawGraph(posX - fontData[currentFontType].sizeX * currentNumLen, posY, handle[viewNum[i]], true);

				currentNumLen--;
			}

			DrawGraph(posX - fontData[currentFontType].sizeX * currentNumLen, posY, handle[12], true);

			currentNumLen--;

			for (int i = 0; i < shousu_n_keta; i++)
			{
				DrawGraph(posX - fontData[currentFontType].sizeX * currentNumLen, posY, handle[viewNum[numLen - shousu_n_keta + i]], true);

				currentNumLen--;
			}
		}
		if (PositionY_UnderFlag == true)
		{
			for (int i = 0; i < numLen - shousu_n_keta; i++)
			{
				DrawGraph(posX - fontData[currentFontType].sizeX * currentNumLen, posY - fontData[currentFontType].sizeY, handle[viewNum[i]], true);

				currentNumLen--;
			}

			DrawGraph(posX - fontData[currentFontType].sizeX * currentNumLen, posY - fontData[currentFontType].sizeY, handle[12], true);

			currentNumLen--;

			for (int i = 0; i < shousu_n_keta; i++)
			{
				DrawGraph(posX - fontData[currentFontType].sizeX * currentNumLen, posY - fontData[currentFontType].sizeY, handle[viewNum[numLen - shousu_n_keta + i]], true);

				currentNumLen--;
			}
		}
	}

	if (viewNum != NULL)
	{
		free(viewNum);
	}
}