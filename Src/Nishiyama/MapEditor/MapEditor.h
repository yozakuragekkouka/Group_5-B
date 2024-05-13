#pragma once
#include <vector>
#include "DxLib.h"
#include "../Map/MapData.h"
#include "../Gimmick/Gimmick.h"

constexpr char ERASER_PATH[128] = "Data/Image/Map/eraser.png";

constexpr int MAP_SELECT_X = 100;
constexpr int EDIT_TOOL_SELECT_SIZE_X = 200;
constexpr int EDIT_TOOL_SELECT_X_OFFSET = 30;
constexpr int EDIT_TOOL_SELECT_Y = 30;
constexpr int EDIT_TOOL_Y = 100 + EDIT_TOOL_SELECT_Y;

constexpr int EDIT_TOOL_ELEMENT_X_OFFSET = 30;
constexpr int EDIT_TOOL_ELEMENT_Y = 60;

constexpr int MAP_SELECT_Y_OFFSET = 30;
constexpr int MAP_SELECT_SIZE_Y = 60;

enum class EditTool
{
	Block,
	Gimmick,

	KindNum
};

constexpr char EDIT_TOOL_NAME[(int)EditTool::KindNum][128] =
{
	"Block",
	"Gimmick",
};

class MapEditor
{
private:
	VECTOR screenPos;

	bool MoveFlag;

	int currentEditMapID;
	bool mapSelectFlag;

	EditTool currentSelectTool;
	bool toolSelectFlag;

	int currentToolID;
	bool toolElementSelectFlag;

	int eraserImage;
	int mapImage[(int)MAPCHIP_KIND::KindNum];
	MapData data;

	bool MoveNowFlag;
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