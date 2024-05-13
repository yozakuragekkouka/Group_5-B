#pragma once

#include <DxLib.h>

//��x�ɕ\���ł���G�t�F�N�g�ő吔
#define EFFECT_MAX_NUM		(20)

//�W�����v�G�t�F�N�g
#define JUMP_EFFECT_HNDL_PATH		"Data/Image/Player/JumpEffect.png"
#define JUMP_ANIME_NUM		(6)

//�q�b�g�G�t�F�N�g
#define HIT_EFFECT_HNDL_PATH		"Data/Image/Player/HitEffect.png"
#define HIT_ANIME_NUM		(12)

struct Hundle
{
	int JumpHndl[2][JUMP_ANIME_NUM];
	int HitHndl[2][HIT_ANIME_NUM];
};

// �G�t�F�N�g�A�j���[�V�����N���X
class EffectAnimation {
public:
    // �G�t�F�N�g�̈ʒu
    int x, y;
    // �G�t�F�N�g�̌��݂̃X�P�[��
    float scale;
    // �A�j���[�V�����̃t���[���J�E���^
    int frameCount;
    // �A�j���[�V�������I���������ǂ���
    bool isFinished;
    // �R���X�g���N�^
    EffectAnimation(int startX, int startY) : x(startX), y(startY), 
        scale(1.0f), frameCount(0), isFinished(false) {}
    // �A�j���[�V�������X�V����֐�
    void Update() {
        // �A�j���[�V�������I�����Ă��Ȃ��ꍇ�͍X�V�𑱂���
        if (!isFinished) {
            // �X�P�[���𑝉�������
            scale += 0.1f;
            // �t���[���J�E���g�𑝉�������
            frameCount++;
     
            DrawEffect();
            // �A�j���[�V�����̏I���������`�F�b�N
            if (frameCount > 30) {
                // �A�j���[�V�������I������
                isFinished = true;
            }
        }
    }
    // �G�t�F�N�g��`�悷��֐�
    void DrawEffect() {
        // �����ŃG�t�F�N�g�̕`����s��
        // ��: DrawRotaGraph(x, y, scale, 0, imageHandle, TRUE);
    }
};
// �G�t�F�N�g�A�j���[�V�����̃C���X�^���X���쐬
EffectAnimation effect(100, 100);
