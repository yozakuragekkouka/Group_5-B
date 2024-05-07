#include <iostream>
#include <fstream>
#include <sstream>

#include "MapData.h"

void MapOperation::LoadMap(MapData& chipData, int& gimmickNum, GimmickID* gimmickID)
{
	/*std::ifstream SaveDataFile_bin_i(Map_FilePath, std::ios_base::binary);

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
		SaveDataFile_bin_i.read(reinterpret_cast<char*>(&gimmickID), sizeof(gimmickID));
	}

	SaveDataFile_bin_i.close();*/
}