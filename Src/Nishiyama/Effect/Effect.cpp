
#include <DxLib.h>
#include "Effect.h"

//��x�ɕ\���ł���G�t�F�N�g�ő吔
#define EFFECT_MAX_NUM		(20)

//�G�t�F�N�g�̃A�j���ő吔
#define EFFECT_ANIME_MAX_NUM	(4)	



//�G�t�F�N�g���
struct EffectInfo
{
	//���G�t�F�N�g�̎��
	EFFECT_TYPE type;
	//���摜�n���h��
	int animeImgHundle[EFFECT_ANIME_MAX_NUM];
	//�����W
	int x, y;
	//���g�p�t���O
	bool isUse;
	//���A�j����
	int animeUsedNum;
	//�����݂̃A�j���ԍ�
	int currentAnimeIndex;
	//���P��������̕\������
	float changeTime;
	//�����݂̃A�j������
	float currentAnimeTime;
};

//�G�t�F�N�g���
EffectInfo effectInfo[EFFECT_MAX_NUM];

//�G�t�F�N�g�̃t�@�C���p�X
const char effectFilePath[EFFECT_TYPE_NUM][256] =
{
	"Data/Image/Effect/JumpEffect.png",
	"Data/Image/Effect/HitEffect.png",
};

//�e�G�t�F�N�g�̃A�j����
const int effectAnimeImgNum[EFFECT_TYPE_NUM] =
{
	6,	//EFFECT_TYPE_JUMP
	12,	//EFFECT_TYPE_HIT
};

//�e�G�t�F�N�g�̉摜������ [0] = x, [1] = y
const int effectImageSplitNum[EFFECT_TYPE_NUM][2] =
{
	{ 6, 1,},	//EFFECT_TYPE_JUMP
	{ 4, 3,},	//EFFECT_TYPE_HIT
};

//�G�t�F�N�g�̉摜�T�C�Y
const int effectImageSize[EFFECT_TYPE_NUM] =
{
	140,	//EFFECT_TYPE_JUMP
	192,	//EFFECT_TYPE_HIT
};

//�e�G�t�F�N�g�̃A�j���摜�؂�ւ�����
const float effectChageTime[EFFECT_TYPE_NUM] =
{
	0.05f,	//EFFECT_TYPE_JUMP
	0.02f,	//EFFECT_TYPE_HIT
};

//�G�t�F�N�g�̓ǂݍ���
//����	�F�G�t�F�N�g�̎�ށA�쐬��
void LoadEffect(EFFECT_TYPE type, int create_num)
{
	//�G�t�F�N�g�̍쐬��for������
	for (int create_index = 0; create_index < create_num; create_index++) {
		//�G�t�F�N�g���\���̔z��for������
		for (int effect_index = 0; effect_index < EFFECT_MAX_NUM; effect_index++) {
			//���ǂݍ��݂��Ă��Ȃ��G�t�F�N�g����������
		//���i�ЂƂڂ̉摜�n���h�����[���Ȃ�ǂݍ��݂���ĂȂ��j
			if (effectInfo[effect_index].animeImgHundle[0] == 0)
			{
				int Anime_Image_Num = effectAnimeImgNum[type];
				int Image_Split_Num_X = effectImageSplitNum[type][0];
				int Image_Split_Num_Y = effectImageSplitNum[type][1];

				int Image_Size = effectImageSize[type];

				//���摜�𕪊��ǂݍ���
				int success_flg = LoadDivGraph(effectFilePath[type],
					Anime_Image_Num, Image_Split_Num_X, Image_Split_Num_Y,
					Image_Size, Image_Size, effectInfo[effect_index].animeImgHundle);

				//��������
				if (success_flg == 0)
				{
					//���A�j�������i�[
					effectInfo[effect_index].animeUsedNum = Anime_Image_Num;

					//���P��������̕\�����Ԃ�ݒ�
					effectInfo[effect_index].changeTime = effectChageTime[type];

					//���G�t�F�N�g�̎�ނ�ݒ�
					effectInfo[effect_index].type = type;
				}

				//�����ۂɂ�����炸������
				break;
			}
		}
	}
}

//�G�t�F�N�g�̏�����
void InitEffect()
{
	//�����ׂẴG�t�F�N�g���̕ϐ����N���A����i�[���ɂ���
	for (int effect_index = 0; effect_index < EFFECT_MAX_NUM; effect_index++)
	{
		effectInfo[effect_index].x = 0;
		effectInfo[effect_index].y = 0;
		effectInfo[effect_index].animeUsedNum = 0;
		effectInfo[effect_index].currentAnimeIndex = 0;
		effectInfo[effect_index].changeTime = 0.0f;
		effectInfo[effect_index].currentAnimeTime = 0.0f;
		effectInfo[effect_index].isUse = false;
		effectInfo[effect_index].type = EFFECT_TYPE_JUMP;
		for (int anime_index = 0; anime_index < EFFECT_ANIME_MAX_NUM; anime_index++)
		{
			effectInfo[effect_index].animeImgHundle[anime_index] = 0;
		}
	}
}

//�G�t�F�N�g�ʏ폈��
void StepEffect()
{
	for (int effect_index = 0; effect_index < EFFECT_MAX_NUM; effect_index++)
	{
		//�g�p���Ȃ�A�j�����Ԃ��o�߂����āA�A�j���ԍ����X�V����
		if (effectInfo[effect_index].isUse == true)
		{
			//�摜�؂�ւ��ɕK�v�Ȏ��Ԍo�߂�����
			if (effectInfo[effect_index].currentAnimeTime >= effectInfo[effect_index].changeTime)
			{
				//���̉摜��
				effectInfo[effect_index].currentAnimeIndex++;

				//�v�����ԃ��Z�b�g
				effectInfo[effect_index].currentAnimeTime = 0.0f;

				//���̉摜�����������Ȃ�
				if (effectInfo[effect_index].currentAnimeIndex >= effectInfo[effect_index].animeUsedNum)
				{
					//�g�p���t���O��OFF��
					effectInfo[effect_index].isUse = false;

					//�ȉ��̏����͕s�v
					continue;
				}
			}

			//���ԍX�V
			effectInfo[effect_index].currentAnimeTime += 1.0f / FRAME_RATE;
		}
	}
}

//�G�t�F�N�g�`�揈��
void DrawEffect()
{
	for (int effect_index = 0; effect_index < EFFECT_MAX_NUM; effect_index++)
	{
		//���g�p���Ȃ猻�݂̃A�j���ԍ��ŕ`�悷��
		if (effectInfo[effect_index].isUse == true)
		{
			DrawRotaGraph(effectInfo[effect_index].x, effectInfo[effect_index].y, 0.5, 0.0,
				effectInfo[effect_index].animeImgHundle[effectInfo[effect_index].currentAnimeIndex], true);
		}
	}
}


//�G�t�F�N�g�̌㏈��
void FinEffect()
{
	//�����ׂẴG�t�F�N�g���폜����
	for (int effect_index = 0; effect_index < EFFECT_MAX_NUM; effect_index++)
	{
		//�����ׂč폜����
		for (int image_index = 0; image_index < EFFECT_ANIME_MAX_NUM; image_index++)
		{
			//���[���ȊO�Ȃ�폜����
			if (effectInfo[effect_index].animeImgHundle[image_index] != 0)
			{
				//���摜�폜������ݒ肷��
				//��DeleteGraph();
				DeleteGraph(effectInfo[effect_index].animeImgHundle[image_index]);

				//���폜������[�������Ă���
				effectInfo[effect_index].animeImgHundle[image_index] = 0;
			}
		}
	}
}

//�G�t�F�N�g�̍Đ�
//����	�F�G�t�F�N�g�̎��, �w���W, �x���W, �P��������̕\������
void PlayEffect(EFFECT_TYPE type, int x, int y)
{
	//�����g�p�G�t�F�N�g��T���čĐ�
	for (int effect_index = 0; effect_index < EFFECT_MAX_NUM; effect_index++)
	{
		//���g�p���Ȃ�ȉ��s��Ȃ�
		if (effectInfo[effect_index].isUse == true)
			continue;
		//���^�C�v����v����
		if (effectInfo[effect_index].type == type)
		{
			//�����W�ݒ�
			effectInfo[effect_index].x = x;
			effectInfo[effect_index].y = y;
			//���v���p�̕ϐ����N���A
			effectInfo[effect_index].currentAnimeIndex = 0;		//���݂̃A�j���ԍ�
			effectInfo[effect_index].currentAnimeTime = 0.0f;	//���݂̃A�j������
			//���g�p���ɂ���
			effectInfo[effect_index].isUse = true;
			//��������
			break;
		}
	}
}
