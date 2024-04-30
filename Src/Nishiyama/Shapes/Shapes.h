#pragma once
#include "DxLib.h"

//オブジェクトデータクラス
class Object
{
protected:
	VECTOR pos;		//座標

public:
	Object();

	VECTOR Get_pos() { return pos; }

	float Get_posX() { return pos.x; }
	float Get_posY() { return pos.y; }
	float Get_posZ() { return pos.z; }

	float* Get_posX_pointer() { return &pos.x; }
	float* Get_posY_pointer() { return &pos.y; }
	float* Get_posZ_pointer() { return &pos.z; }

	void Set_pos(VECTOR Newpos) { pos = Newpos; }
	void Set_posX(float NewposX) { pos.x = NewposX; }
	void Set_posY(float NewposY) { pos.y = NewposY; }
	void Set_posZ(float NewposZ) { pos.z = NewposZ; }

	void Move_position(VECTOR MoveVec) { pos.x += MoveVec.x; pos.y += MoveVec.y; pos.z += MoveVec.z; }
	void Move_X(float MoveX) { pos.x += MoveX;}
	void Move_Y(float MoveY) { pos.y += MoveY;}
	void Move_Z(float MoveZ) { pos.z += MoveZ;}
};

//矩形のデータクラス
class Rect_Data : public Object
{
private:
	int ImageHandle;	//画像ハンドル

protected:
	int sizeW;			//横幅
	int sizeH;			//縦幅

public:
	Rect_Data();
	~Rect_Data();

	void RectInit(int ImageHandle, VECTOR pos, int sizeW, int sizeH);
	void RectFin();

	int Get_sizeW() { return sizeW; }
	int Get_sizeH() { return sizeH; }

	void Set_ImageHandle(int NewImage) { ImageHandle = NewImage; }
	void Set_sizeW(int NewsizeW) { sizeW = NewsizeW; }
	void Set_sizeH(int NewsizeH) { sizeH = NewsizeH; }

	void DrawRect(float Extend_float = 1.0f);
	void DrawRect2(bool X_Flag, bool Y_Flag, float Extend_float = 1.0f);

	void DrawRect_Rota(float Extend_float = 1.0f, float Angle = 0.0f);
	void DrawRect_Rota_Center(float Extend_float = 1.0f, float Angle = 0.0f);
};

//円のデータクラス
class Circle : public Object
{
private:
	int ImageHandle;	//画像ハンドル

protected:
	int radius;			//半径

public:
	Circle();
	~Circle();

	void CircleInit(int init_ImageHandle, VECTOR init_pos, int init_radius);

	float Get_radius() { return (float)radius; }

	void Set_ImageHandle(int NewImage) { ImageHandle = NewImage; }
	void Set_radius(int Newradius) { radius = Newradius; }

	void DrawCircle(float Extend_float = 1.0f);
};
