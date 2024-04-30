#pragma once
#include "../Shapes/Shapes.h"

class Input
{
private:
	//キーボード関連
	static const int KEY_BUF_LEN = 256;

	static char key_log[KEY_BUF_LEN];
	static char key_now[KEY_BUF_LEN];

	//マウス関連
	static Object Mouse;
	static int MouseWheelRota;
	static bool mouse_flag;

public:
	static int GetMouseWheelRota() { return MouseWheelRota; }

	static void AllInputInit();

	static void AllInputDataSet();

	//キーボード関連
	static void KeyLogInit();

	static void Get_Key_Input_Log();

	static bool IsKeyDown(int key_code);

	static bool IsKeyPush(int key_code);

	static bool IsKeyKeep(int key_code);

	static bool IsKeyRelease(int key_code);

	static bool PressAnyKey();

	static int PressAnyKey_name();

	//マウス関連
	static void MouseInit();

	static VECTOR GetMousePos() { return Mouse.Get_pos(); }

	static void GetCurrentMouseState();

	static void Mouse_SetCenter();

	static void Mouse_Disappear();

	static bool Mouse_on_the_Rect(Rect_Data& rect, float ExRate);

	static bool Mouse_on_the_Rect_Center(Rect_Data& rect, float ExRate);

	static bool ClickRect(Rect_Data& rect, float ExRate = 1.0f);

	static bool ClickRect_Center(Rect_Data& rect, float ExRate = 1.0f);
};