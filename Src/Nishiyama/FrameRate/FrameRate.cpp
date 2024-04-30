#include "DxLib.h"
#include "FrameRate.h"
#include "../NumberFont/NumberFont.h"
#include "../NumberFont/NumberFontData.h"
#include "../../Common.h"

FrameRateInfo frameRateInfo;

c_Number FrameNumData;

bool FrameRateAdmin()
{
	Sleep(1);	//�V�X�e���ɏ�����Ԃ�

	//���݂̎��Ԃ��擾
	frameRateInfo.currentTime = GetNowCount();

	//�ŏ��̃��[�v�Ȃ�
	// �i���o�[�t�H���g�f�[�^��������
	//���݂̎��Ԃ��AFPS�̌v�Z���������Ԃɐݒ�
	if (frameRateInfo.calcFpsTime == 0.0f)
	{
		FrameNumData.Init();
		FrameNumData.SetNumberFont(Number_6_12_white);
		FrameNumData.Set_posX(SCREEN_SIZE_X);
		FrameNumData.Set_posY(SCREEN_SIZE_Y);

		frameRateInfo.calcFpsTime = frameRateInfo.currentTime;
		frameRateInfo.fps = (float)FRAME_RATE;
	}

	//���݂̎��Ԃ��A�O��̃t���[�������
	//FRAME_TIME�ȏ�o�߂��Ă����珈�������s����
	if (frameRateInfo.currentTime - frameRateInfo.lastFrateTime >= FRAME_TIME)
	{
		//�t���[�����s���̎��Ԃ��X�V
		frameRateInfo.lastFrateTime = frameRateInfo.currentTime;

		//�t���[�������J�E���g
		frameRateInfo.count++;

		return true;
	}

	return false;
}

void CalcFPS()
{
	//�O���FPS���v�Z�������Ԃ���̌o�ߎ��Ԃ����߂�
	int difTime = frameRateInfo.currentTime - frameRateInfo.calcFpsTime;

	//�O���FPS���v�Z�������Ԃ���
	//1�b�ȏ�o�߂��Ă�����FPS���v�Z����
	if (difTime > 1000)
	{
		//�t���[���񐔂��~���b�ɍ��킹��
		//�����܂ŏo�������̂�float�ɃL���X�g
		float frameCount = (float)(frameRateInfo.count * 1000.0f);

		//FPS�����߂�
		//���z�̐��l�� 60000 / 1000 �� 60 �ƂȂ�	(FRAME_RATE = 60 �̏ꍇ)
		frameRateInfo.fps = frameCount / difTime;

		//�t���[�����[�g�J�E���g���N���A
		frameRateInfo.count = 0;

		//FPS���v�Z�������Ԃ��X�V
		frameRateInfo.calcFpsTime = frameRateInfo.currentTime;
	}
}

//FPS�\���i�f�o�b�N�p�j
void DrawFPS()
{
	FrameNumData.Draw_float(frameRateInfo.fps, 2, true, true);
}
