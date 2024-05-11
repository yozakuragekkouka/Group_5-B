//����
#include "DefaultMap.h"
#include "DxLib.h"
#include "../Player/player.h"

//�}�b�v����

// ���������X�g��const�̃����o�ϐ���������
//�X�e�[�W�\��
_Map::_Map() :m_MapData{}
{
	mapHandle[0] = -1;
	mapHandle[1] = -1;
	mapHandle[2] = -1;
	mapHandle[3] = -1;
}

_Map::~_Map() {}

void _Map::Init() {
	// �摜�̓ǂݍ���
	LoadDivGraph("Data/Image/Map/z_map_div.png", 10, 5, 2, 32, 32, mapHandle);

	// �}�b�v�f�[�^��ǂݍ���
	FILE* fp = 0;
		fopen_s(&fp, "Data/MapData/Map_1/map1.csv", "r"); // �t�@�C�����J��
	if (fp == NULL) // �t�@�C�����J���Ȃ�������
	{
		DrawString(0, 0, "dgsgh", GetColor(255, 255, 255));
		return; // �I��
	}
	for (int i = 0; i < MAP_DATA_Y; i++) // �}�b�v�̍������J��Ԃ�
	{
		for (int j = 0; j < MAP_DATA_X; j++) // �}�b�v�̕����J��Ԃ�
		{
			fscanf_s(fp, "%d,", &m_MapData[i][j]); // �}�b�v�f�[�^��ǂݍ���
		}
	}
	fclose(fp); // �t�@�C�������
}



void _Map::Draw() {

	for (int y = 0; y < MAP_DATA_Y; y++)
	{
		for (int x = 0; x < MAP_DATA_X; x++)
		{
			// �u���b�N��`��
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
	// ���W���}�b�v�f�[�^�̃C���f�b�N�X�ɕϊ�
	int mapIndexX = x / MAP_SIZE;
	int mapIndexY = y / MAP_SIZE;

	// �}�b�v�f�[�^�͈͓̔����ǂ���
	if (mapIndexX < 0 || mapIndexX >= MAP_DATA_X || mapIndexY < 0 || mapIndexY >= MAP_DATA_Y) {
		return false; // �͈͊O�Ȃ�u���b�N�͂Ȃ�
	}

	// �}�b�v�f�[�^����u���b�N�̗L�����擾
	return m_MapData[mapIndexY][mapIndexX] != 0; // 0�ȊO�̒l�̓u���b�N
}

