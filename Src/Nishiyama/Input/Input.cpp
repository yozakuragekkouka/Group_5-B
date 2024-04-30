#include "DxLib.h"
#include "Input.h"
#include "../../Common.h"

//キーボード関連
const int Input::KEY_BUF_LEN;
char Input::key_log[KEY_BUF_LEN];
char Input::key_now[KEY_BUF_LEN];

//マウス関連
Object Input::Mouse;
int Input::MouseWheelRota;
bool Input::mouse_flag;

void Input::AllInputInit()
{
	KeyLogInit();
	MouseInit();
}

void Input::AllInputDataSet()
{
	Get_Key_Input_Log();
	GetCurrentMouseState();
}

//キーボード関連
void Input::KeyLogInit()
{
	for (int i = 0; i < KEY_BUF_LEN; i++)
	{
		key_log[i] = 0;
	}

	for (int i = 0; i < KEY_BUF_LEN; i++)
	{
		key_now[i] = 0;
	}
}

void Input::Get_Key_Input_Log()
{
	for (int i = 0; i < KEY_BUF_LEN; i++)
	{
		key_log[i] = key_now[i];
	}

	GetHitKeyStateAll(key_now);
}

bool Input::IsKeyDown(int key_code)
{
	if (key_now[key_code])
		return true;
	
	return false;
}

bool Input::IsKeyPush(int key_code)
{
	if(key_now[key_code])
	{
		if (key_log[key_code] == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool Input::IsKeyKeep(int key_code)
{
	if (key_now[key_code])
	{
		if (key_log[key_code] == 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

bool Input::IsKeyRelease(int key_code)
{
	if (key_log[key_code])
	{
		if (key_now[key_code] == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool Input::PressAnyKey()
{
	for (int i = 0; i < KEY_BUF_LEN; i++)
	{
		if (key_now[i] && key_log[i] == 0)
		{
			return true;
		}
	}
	return false;
}

int Input::PressAnyKey_name()
{
	for (int i = 0; i < KEY_BUF_LEN; i++)
	{
		if (key_now[i] && key_log[i] == 0)
		{
			return i;
		}
	}
	return -1;
}

//マウス関連
void Input::MouseInit()
{
	Mouse.Set_pos(VGet(0.0f, 0.0f, 0.0f));

	MouseWheelRota = 0;

	mouse_flag = false;
}

void Input::GetCurrentMouseState()
{
	int x = 0, y = 0;
	GetMousePoint(&x, &y);

	Mouse.Set_posX((float)x);
	Mouse.Set_posY((float)y);

	MouseWheelRota = -GetMouseWheelRotVol();
}

void Input::Mouse_SetCenter()
{
	SetMouseDispFlag(true);
	SetMousePoint(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2);
}

void Input::Mouse_Disappear()
{
	SetMouseDispFlag(false);
}

bool Input::Mouse_on_the_Rect(Rect_Data& rect, float ExRate)
{
	VECTOR r_pos = rect.Get_pos();
	int r_sizeX = (int)(rect.Get_sizeW() * ExRate);
	int r_sizeY = (int)(rect.Get_sizeH() * ExRate);

	VECTOR m_pos = Mouse.Get_pos();

	if (m_pos.x >= r_pos.x && m_pos.x <= r_pos.x + r_sizeX &&
		m_pos.y >= r_pos.y && m_pos.y <= r_pos.y + r_sizeY)
	{
		//矩形の中にある
		return true;
	}
	else
	{
		//矩形の中にない
		return false;
	}
}

bool Input::Mouse_on_the_Rect_Center(Rect_Data& rect, float ExRate)
{
	VECTOR r_pos = rect.Get_pos();
	int r_sizeX_2 = (int)(rect.Get_sizeW() / 2 * ExRate);
	int r_sizeY_2 = (int)(rect.Get_sizeH() / 2 * ExRate);

	VECTOR m_pos = Mouse.Get_pos();

	if (m_pos.x >= r_pos.x - r_sizeX_2 && m_pos.x <= r_pos.x + r_sizeX_2 &&
		m_pos.y >= r_pos.y - r_sizeY_2 && m_pos.y <= r_pos.y + r_sizeY_2)
	{
		//矩形の中にある
		return true;
	}
	else
	{
		//矩形の中にない
		return false;
	}
}

bool Input::ClickRect(Rect_Data& rect, float ExRate)
{
	if (Mouse_on_the_Rect(rect, ExRate))
	{
		//矩形の中にある
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{
			//押されている
			if (mouse_flag == false)
			{
				//押されつづけていない
				mouse_flag = true;
				return true;
			}
			return false;
		}
		else
		{
			//押されていない
			mouse_flag = false;
			return false;
		}
	}
	else
	{
		//矩形の中にない
		return false;
	}
}

bool Input::ClickRect_Center(Rect_Data& rect, float ExRate)
{
	if (Mouse_on_the_Rect_Center(rect, ExRate))
	{
		//矩形の中にある
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{
			//押されている
			if (mouse_flag == false)
			{
				//押されつづけていない
				mouse_flag = true;
				return true;
			}
			return false;
		}
		else
		{
			//押されていない
			mouse_flag = false;
			return false;
		}
	}
	else
	{
		//矩形の中にない
		return false;
	}
}