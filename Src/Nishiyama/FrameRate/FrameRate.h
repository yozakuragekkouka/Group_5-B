#pragma once

//�ݒ�t���[�����[�g
#define FRAME_RATE 60

//1�t���[���̎��ԁi�~���b�j
#define FRAME_TIME (1000 / FRAME_RATE)

//�t���[�����[�g���
struct FrameRateInfo
{
	int currentTime;	//���݂̎���
	int lastFrateTime;	//�O��̃t���[�����s���̎���
	int count;			//�t���[���J�E���g�p
	int calcFpsTime;	//FPS���v�Z��������
	float fps;			//�v������FPS�i�\���p�j
};

//�t���[�����[�g���ϐ�
extern FrameRateInfo frameRateInfo;

//FPS�Ǘ��֐�
bool FrameRateAdmin();

//FPS�v�Z
void CalcFPS();

//FPS�\���i�f�o�b�N�p�j
void DrawFPS();
