#include "DxLib.h"
#include "Common.h"
#include "Nishiyama/Input/Input.h"
#include "Nishiyama/Sound/Sound.h"
#include "Nishiyama/FrameRate/FrameRate.h"
#include "Nishiyama/NumberFont/NumberFont.h"
#include "Nishiyama/NumberFont/NumberFontData.h"
#include "Nishiyama/Scene/Scene.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	//�E�B���h�E�̏�Ԃ�ݒ�
	ChangeWindowMode(true);

	//��ʃT�C�Y��ݒ�
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);

	//����������
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	//�`�悷��X�N���[���𗠂ɐݒ�
	SetDrawScreen(DX_SCREEN_BACK);


	/*�ŏ��ɂP�x������鏈��*/
	Input::AllInputInit();

	SoundEffect::Init();

	SceneManager scene_manager;
	scene_manager.SceneInit();

	//�Q�[���̃��C�����[�v
	while (ProcessMessage() != -1)
	{
		if (FrameRateAdmin())
		{
			Input::AllInputDataSet();

			//�G�X�P�[�v�L�[�ŏI��
			if (CheckHitKey(KEY_INPUT_ESCAPE))
			{
				break;
			}

			//��ʂ�������
			ClearDrawScreen();

			// �� ���C���̏���
			if (scene_manager.SceneLoop())
			{
				break;
			}

			//FPS�v�Z
			CalcFPS();

			//FPS�\��
			DrawFPS();

			// 1���[�v�I��
			ScreenFlip();
		}
	}

	/*�Ō�ɂP�x������鏈��*/
	scene_manager.SceneFin();

	SoundEffect::Fin();

	//DxLib�̌㏈��
	DxLib_End();

	return 0;
}