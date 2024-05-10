#pragma once
#include <vector>
#include "DxLib.h"
#include "../Map/MapData.h"
#include "../Gimmick/Gimmick.h"

constexpr int MAP_SELECT_X = 100;
constexpr int EDIT_TOOL_SELECT_SIZE_X = 200;
constexpr int EDIT_TOOL_SELECT_X_OFFSET = 30;
constexpr int EDIT_TOOL_SELECT_Y = 30;
constexpr int EDIT_TOOL_Y = 100 + EDIT_TOOL_SELECT_Y;

enum class EditTool
{
	Move,
	Draw,

	KindNum
};

constexpr char EDIT_TOOL_NAME[(int)EditTool::KindNum][128] =
{
	"Move",
	"Draw",
};

class MapEditor
{
private:
	VECTOR screenPos;

	int currentEditMapID;

	EditTool currentSelectTool;
	bool toolSelectFlag;

	int currentToolID;

	int mapImage[(int)MAPCHIP_KIND::KindNum];
	MapData data;

	bool MoveFlag;
	VECTOR MouseLogPos;
	bool isSet[MAPCHIP_NUM_Y][MAPCHIP_NUM_X];

	float DrawRate;

	std::vector<GimmickID> gimmickID;
	GimmickBase** gimmick;

public:
	MapEditor();
	~MapEditor();

	void Init();
	void Step();
	void Draw();
	void Fin();
};