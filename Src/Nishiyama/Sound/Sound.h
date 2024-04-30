#pragma once
#include "../../Common.h"

//BGM種類列挙型
enum BGM_KIND
{
	BGM_NONE = -1,
	BGM_A,

	BGM_NUM
};

//SE種類列挙型
enum SE_KIND
{
	SE_NONE = -1,
	SE_A,

	SE_NUM
};

//BGMデータクラス
class BGM_Data
{
private:
	int BGMHandle;
	int VolumePal;

public:
	BGM_Data();
	~BGM_Data();

	void SetVol(int Volume) { VolumePal = Volume; };

	void BGMInit(BGM_KIND kind);

	void FinBGM();
};

//SEデータクラス
class SE_Data
{
private:
	int SEHandle;
	
public:
	SE_Data();
	~SE_Data();

	void LoadSE(SE_KIND kind);

	void SetVolume(int VolumePal) { ChangeVolumeSoundMem(VolumePal, SEHandle); }

	void PlaySE();

	void FinSE();
};

class SoundEffect
{
private:
	static SE_Data SE[SE_NUM];

public:
	static void Init();
	static void Play(SE_KIND kind);
	static void Fin();
};
