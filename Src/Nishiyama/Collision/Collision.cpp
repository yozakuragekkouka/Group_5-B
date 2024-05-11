#include "DxLib.h"
#include "Collision.h"

//IsHitRect�̒�`
//��`���������Ă��邩�i�߂荞��ł��邩�j�̔���
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


//IsHitCircle�̒�`
//�~���������Ă��邩�i�߂荞��ł��邩�j�̔���
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
