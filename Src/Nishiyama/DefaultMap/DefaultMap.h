//����
#pragma once

// �e�}�b�v�̃f�[�^��
const int MAP_DATA_Y = 25;
const int MAP_DATA_X = 40;

// �}�b�v�T�C�Y
const int MAP_SIZE = 32;

//�}�b�v�f�[�^�o���G�[�V����


// �}�b�v�N���X
class _Map
{
private:
	// �}�b�v�`�b�v�n���h��
	int mapHandle[4];
	int mapSelect[4];
	bool Invert_Color_flag[MAP_DATA_Y][MAP_DATA_X] = { false };
	bool Invert_Color_flag_full = false;
public:
	_Map();
	~_Map();

	// �}�b�v�f�[�^
	const int m_MapData[MAP_DATA_Y][MAP_DATA_X] = { 0 };
	int mposX;  //�}�b�v���W

	// ������
	void Init();

	// �`��
	void Draw();

	bool Get_Invert_Color() { return Invert_Color_flag_full; };

	bool IsBlockAt(int x, int y);


};

