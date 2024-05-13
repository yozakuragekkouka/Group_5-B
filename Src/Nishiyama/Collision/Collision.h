#pragma once
#include "DxLib.h"

class Collision
{
public:
	//IsHitRect�̃v���g�^�C�v�錾
	static bool IsHitRect(VECTOR Rect1_Pos, VECTOR Rect2_Pos, VECTOR Rect1_Size, VECTOR Rect2_Size);

	//IsHitCircle�̃v���g�^�C�v�錾
	static bool IsHitCircle(VECTOR Circle1_Pos, VECTOR Circle2_Pos, float Circle1_Radius, float Circle2_Radius);


	//IsHitRect�̃v���g�^�C�v�錾
	static bool IsHitRectNormal(int myPos_X, int myPos_Y, int side, int Vertical,
		int pos_1X, int pos_1Y, int Rectside, int RectVertical);

	//IsHitCircle�̃v���g�^�C�v�錾
	static bool IsHitCircleNormal(int PosX, int PosY, int circle1, int aPosX, int aPosY, int circle2);
};