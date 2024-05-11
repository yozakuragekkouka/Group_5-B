//奥村
#pragma once

// 各マップのデータ数
const int MAP_DATA_Y = 25;
const int MAP_DATA_X = 40;

// マップサイズ
const int MAP_SIZE = 32;

//マップデータバリエーション


// マップクラス
class _Map
{
private:
	// マップチップハンドル
	int mapHandle[4];
	int mapSelect[4];
	bool Invert_Color_flag[MAP_DATA_Y][MAP_DATA_X] = { false };
	bool Invert_Color_flag_full = false;
public:
	_Map();
	~_Map();

	// マップデータ
	const int m_MapData[MAP_DATA_Y][MAP_DATA_X] = { 0 };
	int mposX;  //マップ座標

	// 初期化
	void Init();

	// 描画
	void Draw();

	bool Get_Invert_Color() { return Invert_Color_flag_full; };

	bool IsBlockAt(int x, int y);


};

