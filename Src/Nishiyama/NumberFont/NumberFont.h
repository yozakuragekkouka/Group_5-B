#pragma once
#include "NumberFontData.h"

class c_Number
{
private:
	int handle[13];
	int* viewNum;
	int posX;
	int posY;
	NumberFontType currentFontType;

public:
	c_Number();
	~c_Number();

	void Init();
	void Fin();

	inline int GetposX() { return posX; }
	inline int GetposY() { return posY; }
	inline void Set_posX(int NewposX) { posX = NewposX; }
	inline void Set_posY(int NewposY) { posY = NewposY; }

	void SetNumberFont(NumberFontType fontType);

	void Draw_int(const int drawNumber, bool RightFlag = false, bool PositionY_UnderFlag = false);

	void Draw_float(float drawNumber, int shousu_n_keta, bool RightFlag = false, bool PositionY_UnderFlag = false);
};