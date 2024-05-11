//奥村
#include "DefaultMap.h"
#include "DxLib.h"
#include "../Player/player.h"

//マップ処理

// 初期化リストでconstのメンバ変数を初期化
//ステージ構成
_Map::_Map() :m_MapData{}
{
	mapHandle[0] = -1;
	mapHandle[1] = -1;
	mapHandle[2] = -1;
	mapHandle[3] = -1;
}

_Map::~_Map() {}

void _Map::Init() {
	// 画像の読み込み
	LoadDivGraph("Data/Image/Map/z_map_div.png", 10, 5, 2, 32, 32, mapHandle);

	// マップデータを読み込む
	FILE* fp = 0;
		fopen_s(&fp, "Data/MapData/Map_1/map1.csv", "r"); // ファイルを開く
	if (fp == NULL) // ファイルが開けなかったら
	{
		DrawString(0, 0, "dgsgh", GetColor(255, 255, 255));
		return; // 終了
	}
	for (int i = 0; i < MAP_DATA_Y; i++) // マップの高さ分繰り返す
	{
		for (int j = 0; j < MAP_DATA_X; j++) // マップの幅分繰り返す
		{
			fscanf_s(fp, "%d,", &m_MapData[i][j]); // マップデータを読み込む
		}
	}
	fclose(fp); // ファイルを閉じる
}



void _Map::Draw() {

	for (int y = 0; y < MAP_DATA_Y; y++)
	{
		for (int x = 0; x < MAP_DATA_X; x++)
		{
			// ブロックを描画
			if (m_MapData[y][x] != 0) {
				DrawGraph(x * MAP_SIZE, y * MAP_SIZE, mapHandle[m_MapData[y][x] - 1], true);
			}
			if (m_MapData[y][x] == 7 || m_MapData[y][x] == 2) {
				if (Invert_Color_flag_full)
					SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);
				DrawGraph(x * MAP_SIZE, y * MAP_SIZE, mapHandle[m_MapData[y][x] - 1], true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			if (m_MapData[y][x] == 8) {
				if (Invert_Color_flag[y][x])
					SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);
				DrawGraph(x * MAP_SIZE, y * MAP_SIZE, mapHandle[m_MapData[y][x] - 1], true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}
	}
}

bool _Map::IsBlockAt(int x, int y) {
	// 座標をマップデータのインデックスに変換
	int mapIndexX = x / MAP_SIZE;
	int mapIndexY = y / MAP_SIZE;

	// マップデータの範囲内かどうか
	if (mapIndexX < 0 || mapIndexX >= MAP_DATA_X || mapIndexY < 0 || mapIndexY >= MAP_DATA_Y) {
		return false; // 範囲外ならブロックはない
	}

	// マップデータからブロックの有無を取得
	return m_MapData[mapIndexY][mapIndexX] != 0; // 0以外の値はブロック
}

