
#ifndef __EFFECT_H__
#define __EFFECT_H__

//�ݒ�t���[�����[�g�i60FPS�j
#define FRAME_RATE	(60)

//�P�t���[���̎��ԁi�~���b�j
#define FRAME_TIME	(1000 / FRAME_RATE)


//�G�t�F�N�g�̎��
enum EFFECT_TYPE
{
	EFFECT_TYPE_JUMP = 0,	//�W�����v
	EFFECT_TYPE_HIT,		//�q�b�g

	EFFECT_TYPE_NUM,
};

//�G�t�F�N�g�̓ǂݍ���
//����	�F�G�t�F�N�g�̎�ށA�쐬��
void LoadEffect(EFFECT_TYPE type, int create_num);

//�G�t�F�N�g�̏�����
void InitEffect();

//�G�t�F�N�g�ʏ폈��
void StepEffect();

//�G�t�F�N�g�`�揈��
void DrawEffect();

//�G�t�F�N�g�̌㏈��
void FinEffect();

//�G�t�F�N�g�̍Đ�
//����	�F�G�t�F�N�g�̎��, �w���W, �x���W, �P��������̕\������
void PlayEffect(EFFECT_TYPE type, int x, int y);


#endif
