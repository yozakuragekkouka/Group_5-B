#include "DxLib.h"
#include "Collision.h"

//IsHitRectの定義
//矩形が当たっているか（めり込んでいるか）の判定
bool Collision::IsHitRect(VECTOR Rect1_Pos, VECTOR Rect2_Pos, VECTOR Rect1_Size, VECTOR Rect2_Size)
{
	if (Rect1_Pos.x + Rect1_Size.x > Rect2_Pos.x &&
		Rect2_Pos.x + Rect2_Size.x > Rect1_Pos.x &&
		Rect1_Pos.y + Rect1_Size.y > Rect2_Pos.y &&
		Rect2_Pos.y + Rect2_Size.y > Rect1_Pos.y)
	{
		return true;
	}
	else
		return false;
}


//IsHitCircleの定義
//円が当たっているか（めり込んでいるか）の判定
bool Collision::IsHitCircle(VECTOR Circle1_Pos, VECTOR Circle2_Pos, float Circle1_Radius, float Circle2_Radius)
{
	if ((Circle1_Radius + Circle2_Radius) * (Circle1_Radius + Circle2_Radius) >
		(Circle1_Pos.x - Circle2_Pos.x) * (Circle1_Pos.x - Circle2_Pos.x) +
		(Circle1_Pos.y - Circle2_Pos.y) * (Circle1_Pos.y - Circle2_Pos.y))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//VECTORを使わないほう
bool Collision::IsHitRectNormal(int myPos_X, int myPos_Y, int side, int Vertical,
	int pos_1X, int pos_1Y, int Rectside, int RectVertical)
{
	if (myPos_X < pos_1X + Rectside &&
		myPos_X + side > pos_1X &&
		myPos_Y + Vertical > pos_1Y &&
		myPos_Y < pos_1Y + RectVertical)
		return true;
	else
		return false;
}

//VECTORを使わないほう
bool Collision::IsHitCircleNormal(int PosX, int PosY, int circle1, int aPosX, int aPosY, int circle2)
{
	if ((circle1 + circle2) * (circle1 + circle2) >
		(aPosX - PosX) * (aPosX - PosX) + (aPosY - PosY) * (aPosY - PosY))
	{
		return true;
	}
	else
		return false;
}

