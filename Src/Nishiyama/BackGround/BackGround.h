#pragma once
#include "../Shapes/Shapes.h"

enum class BackGroundKind
{
	NONE,

	KindNum
};

constexpr int BACK_GROUND_NUM = 3;
constexpr int BACK_GROUND_DEFAULT_SPEED = 10;

constexpr int BACK_GROUND_SIZEW = 1280;
constexpr int BACK_GROUND_SIZEH = 720;
constexpr int BACK_GROUND_OVER = 30 + BACK_GROUND_SIZEW;

constexpr char BACK_GROUND_PATH[(int)BackGroundKind::KindNum][128] =
{
	"aaaaa",
};

class BackGround
{
public:

private:
	float speed;
	int ResultBackCount;
	Rect_Data BG_Image[BACK_GROUND_NUM];
	BackGroundKind kind;

	/*int BgHundl[2][3];
	int BgPosX;*/

public:
	BackGround();
	~BackGround();

	void Init(BackGroundKind Kind);
	void Step();
	void Draw();
	void Fin();

	void SetSpeed(float New_Speed) { speed = New_Speed; }
};