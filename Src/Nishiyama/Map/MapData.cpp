#include <iostream>
#include <fstream>
#include <sstream>

#include "MapData.h"

void MapOperation::LoadMap(MapData& chipData, int& gimmickNum, GimmickID* gimmickID, bool isEdit, int MapID)
{
	std::ifstream SaveDataFile_bin_i;
	if (!isEdit)
	{
		SaveDataFile_bin_i.open(ORIGINAL_MAP_PATH[MapID], std::ios_base::binary);
	}
	else
	{
		SaveDataFile_bin_i.open(EDIT_MAP_PATH[MapID], std::ios_base::binary);
	}

	if (!SaveDataFile_bin_i)
	{
		memset(&chipData, 0, sizeof(MapData));
		memset(&gimmickNum, 0, sizeof(int));

		return;
	}

	SaveDataFile_bin_i.read(reinterpret_cast<char*>(&chipData), sizeof(MapData));
	SaveDataFile_bin_i.read(reinterpret_cast<char*>(&gimmickNum), sizeof(int));
	if (gimmickNum > 0)
	{
		gimmickID = new GimmickID[gimmickNum];
		SaveDataFile_bin_i.read(reinterpret_cast<char*>(gimmickID), sizeof(gimmickID));
	}

	SaveDataFile_bin_i.close();
}

void MapOperation::SaveMap(MapData& chipData, int& gimmickNum, GimmickID* gimmickID, bool isEdit, int MapID)
{
	std::ofstream SaveDataFile_bin_o;
	if (!isEdit)
	{
		SaveDataFile_bin_o.open(ORIGINAL_MAP_PATH[MapID], std::ios_base::binary);
	}
	else
	{
		SaveDataFile_bin_o.open(EDIT_MAP_PATH[MapID], std::ios_base::binary);
	}

	SaveDataFile_bin_o.write(reinterpret_cast<char*>(&chipData), sizeof(MapData));
	SaveDataFile_bin_o.write(reinterpret_cast<char*>(&gimmickNum), sizeof(int));
	if (gimmickNum > 0)
	{
		SaveDataFile_bin_o.write(reinterpret_cast<char*>(gimmickID), sizeof(gimmickID));
	}
	
	SaveDataFile_bin_o.close();
}