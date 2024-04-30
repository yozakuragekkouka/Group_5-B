#include "DxLib.h"
#include "Shapes.h"
#include "../Vector/Vector.h"

Object::Object()
{
	pos = VGet(0.0f, 0.0f, 0.0f);
}

Rect_Data::Rect_Data()
{
	ImageHandle = 0;
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;
	sizeW = 0;
	sizeH = 0;
}

Rect_Data::~Rect_Data()
{
	if (ImageHandle != 0)
		DeleteGraph(ImageHandle);
}

void Rect_Data::RectInit(int init_ImageHandle, VECTOR init_pos, int init_sizeW, int init_sizeH)
{
	ImageHandle = init_ImageHandle;
	pos.x = init_pos.x;
	pos.y = init_pos.y;
	pos.z = init_pos.z;
	sizeW = init_sizeW;
	sizeH = init_sizeH;
}

void Rect_Data::RectFin()
{
	if (ImageHandle != 0)
		DeleteGraph(ImageHandle);
}

void Rect_Data::DrawRect(float Extend_float)
{
	DrawExtendGraph((int)pos.x, (int)pos.y, (int)(pos.x + (float)sizeW * Extend_float) + 1, (int)(pos.y + (float)sizeH * Extend_float) + 1, ImageHandle, true);
}

void Rect_Data::DrawRect2(bool X_Flag, bool Y_Flag, float Extend_float)
{
	if (X_Flag)
	{
		if (Y_Flag)
		{
			DrawExtendGraph((int)pos.x, (int)pos.y, (int)(pos.x + (float)sizeW * Extend_float) + 1, (int)(pos.y + (float)sizeH * Extend_float) + 1, ImageHandle, true);
		}
		else
		{
			DrawExtendGraph((int)pos.x, (int)pos.y, (int)(pos.x + (float)sizeW * Extend_float) + 1, (int)(pos.y + (float)sizeH) + 1, ImageHandle, true);
		}
	}
	else
	{
		if (Y_Flag)
		{
			DrawExtendGraph((int)pos.x, (int)pos.y, (int)(pos.x + (float)sizeW) + 1, (int)(pos.y + (float)sizeH * Extend_float) + 1, ImageHandle, true);
		}
		else
		{
			DrawExtendGraph((int)pos.x, (int)pos.y, (int)(pos.x + (float)sizeW) + 1, (int)(pos.y + (float)sizeH) + 1, ImageHandle, true);
		}
	}
}

void Rect_Data::DrawRect_Rota(float Extend_float, float Angle)
{
	DrawRotaGraph((int)pos.x + sizeW / 2, (int)pos.y + sizeH / 2, Extend_float, Angle, ImageHandle, true);
}

void Rect_Data::DrawRect_Rota_Center(float Extend_float, float Angle)
{
	DrawRotaGraph((int)pos.x, (int)pos.y, Extend_float, Angle, ImageHandle, true);
}

Circle::Circle()
{
	ImageHandle = 0;
	radius = 0;
	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;
}

Circle::~Circle()
{
	if (ImageHandle != 0)
		DeleteGraph(ImageHandle);
}

void Circle::CircleInit(int init_ImageHandle, VECTOR init_pos, int init_radius)
{
	ImageHandle = init_ImageHandle;
	pos.x = init_pos.x;
	pos.y = init_pos.y;
	pos.z = init_pos.z;
	radius = init_radius;
}

void Circle::DrawCircle(float Extend_float)
{
	DrawRotaGraph((int)pos.x, (int)pos.y, Extend_float, 0.0, ImageHandle, true);
}