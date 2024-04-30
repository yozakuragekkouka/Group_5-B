#include "DxLib.h"
#include "Sound.h"

SE_Data SoundEffect::SE[SE_NUM];

const char* BGMkind[BGM_NUM] =
{
	"Data/Nishiyama/Sound/NONE.mp3",
};

const char* SEkind[SE_NUM] =
{
	"Data/Nishiyama/Sound/NONE.mp3",
};

//BGM�R���X�g���N�^
BGM_Data::BGM_Data()
{
	BGMHandle = -1;
	VolumePal = 255;
}

//BGM�f�X�g���N�^
BGM_Data::~BGM_Data()
{
	if (BGMHandle)
	{
		if (CheckSoundMem(BGMHandle))
			StopSoundMem(BGMHandle);
		DeleteSoundMem(BGMHandle);
	}
}

//BGM������
void BGM_Data::BGMInit(BGM_KIND kind)
{
	BGMHandle = LoadSoundMem(BGMkind[kind]);
	ChangeNextPlayVolumeSoundMem(VolumePal, BGMHandle);
	PlaySoundMem(BGMHandle, DX_PLAYTYPE_LOOP, true);
}

//BGM�㏈��
void BGM_Data::FinBGM()
{
	if (BGMHandle)
	{
		if (CheckSoundMem(BGMHandle))
			StopSoundMem(BGMHandle);
		DeleteSoundMem(BGMHandle);
	}
}

//SE�R���X�g���N�^
SE_Data::SE_Data()
{
	SEHandle = -1;
}

//SE�f�X�g���N�^
SE_Data::~SE_Data()
{
	if (SEHandle)
	{
		if (CheckSoundMem(SEHandle))
			StopSoundMem(SEHandle);
		DeleteSoundMem(SEHandle);
	}
}

//SE�ǂݍ���
void SE_Data::LoadSE(SE_KIND kind)
{
	SEHandle = LoadSoundMem(SEkind[kind]);
}

//SE�ǂݍ���
void SE_Data::PlaySE()
{
	PlaySoundMem(SEHandle, DX_PLAYTYPE_BACK, true);
}

void SE_Data::FinSE()
{
	if (CheckSoundMem(SEHandle))
		StopSoundMem(SEHandle);
	DeleteSoundMem(SEHandle);
}

void SoundEffect::Init()
{
	for (int i = 0; i < SE_NUM; i++)
	{
		SE[i].LoadSE((SE_KIND)i);
	}
}

void SoundEffect::Play(SE_KIND kind)
{
	SE[kind].PlaySE();
}

void SoundEffect::Fin()
{
	for (int i = 0; i < SE_NUM; i++)
	{
		SE[i].FinSE();
	}
}
