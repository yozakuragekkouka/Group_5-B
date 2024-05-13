#pragma once
#include "DxLib.h"

class Collision
{
public:
	//IsHitRectのプロトタイプ宣言
	static bool IsHitRect(VECTOR Rect1_Pos, VECTOR Rect2_Pos, VECTOR Rect1_Size, VECTOR Rect2_Size);

	//IsHitCircleのプロトタイプ宣言
	static bool IsHitCircle(VECTOR Circle1_Pos, VECTOR Circle2_Pos, float Circle1_Radius, float Circle2_Radius);


	//IsHitRectのプロトタイプ宣言
	static bool IsHitRectNormal(int myPos_X, int myPos_Y, int side, int Vertical,
		int pos_1X, int pos_1Y, int Rectside, int RectVertical);

	//IsHitCircleのプロトタイプ宣言
	static bool IsHitCircleNormal(int PosX, int PosY, int circle1, int aPosX, int aPosY, int circle2);
};