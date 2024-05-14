#include "DxLib.h"
#include "Enemy.h"
//#include "../Player/player.h"
#include <math.h>
#include <cmath>
#include<vector>
#include"../DefaultMap/DefaultMap.h"

#include <iostream>




//�摜�p�X
#define PLAYER_PATH "Data/Image/Enemy/player_div.png"

//�v���C���[���o���Ă����ō��X�s�[�h
#define PLAYER_SPEED_MAX 6

void Enemy::Step() {
	Participate(dvd);
	m_pos = m_next_pos;
	m_next_pos.y += grav;
	Update();
	ConnectToNearestRival();
	NearsRival();
	Jump();
}

Enemy::Enemy()
{
	m_move_vec = { 0 };
	m_next_pos = { 0 };
	m_next_pos = { 0 };
}

Enemy::~Enemy() {}

//������
void Enemy::Init(int num) {


	if (num == 0)
		m_next_pos = { ((SCREEN_SIZE_X / 4) - ((float)EnemySize / 2)),
				  ((SCREEN_SIZE_Y / 4) - ((float)EnemySize / 2)),0 };
	//�摜�ǂݍ���
	LoadDivGraph("Data/Image/Player/player_div.png", 12, 4, 3, 64, 64, EnemyHan);
	speed = 0;
	animIndex = 1;
	enemyStopFlag = false;

	Walk_Sound[0] = LoadSoundMem("Data/Sound/ashi/0.mp3");
	Walk_Sound[1] = LoadSoundMem("Data/Sound/ashi/1.mp3");
	Walk_Sound[2] = LoadSoundMem("Data/Sound/ashi/2.mp3");
	Walk_Sound[3] = LoadSoundMem("Data/Sound/ashi/3.mp3");
	Walk_Sound[4] = LoadSoundMem("Data/Sound/ashi/4.mp3");
	Walk_Sound[5] = LoadSoundMem("Data/Sound/ashi/5.mp3");
	Walk_Sound[6] = LoadSoundMem("Data/Sound/ashi/6.mp3");
	Walk_Sound[7] = LoadSoundMem("Data/Sound/ashi/7.mp3");
	Walk_Sound[8] = LoadSoundMem("Data/Sound/ashi/8.mp3");
	Walk_Sound[9] = LoadSoundMem("Data/Sound/ashi/9.mp3");
	Walk_Sound[10] = LoadSoundMem("Data/Sound/ashi/10.mp3");
	Walk_Sound[11] = LoadSoundMem("Data/Sound/ashi/11.mp3");
	Walk_Sound[12] = LoadSoundMem("Data/Sound/ashi/12.mp3");

	grav = 15.0;

	radius = 10.0;

	currentRivalIndex = -1;
	nearestRivalIndex = -1;
	for (int i = 0; i < CHARACTER_MAX_NUM; i++)
	{
		dvd[i] = { (float)GetRand(SCREEN_SIZE_X / 2),
			(float)GetRand(SCREEN_SIZE_Y / 2),0 };
		next_dvd[i] = { (float)(10 * i) + (float)2.0,(float)(10 * i) + (float)2.0,0 };

		Rival[i] = { 0 };
	}

	PlayerToParticipate = -1;

	isJump = true;
	jumpPower = 20;
}

void Enemy::Participate(VECTOR Player[CHARACTER_MAX_NUM])
{
	for (int j = 0; j < CHARACTER_MAX_NUM; j++)
	{
		if (j < PlayerToParticipate)
			Rival[j] = Player[j];
		Rival[j] = dvd[j];
	}
}

void Enemy::ConnectToNearestRival()
{
	nearestRivalIndex = -1;
	double minDistance = DBL_MAX; // �ŏ���������ɑ傫�Ȓl�ŏ�����

	// �S�Ă̓G�Ƃ̋������v�Z���A�ł��߂��G��������
	for (int i = 0; i < CHARACTER_MAX_NUM; ++i) {
		double distance = CalculateDistance(m_pos.x, m_pos.y, Rival[i].x, Rival[i].y);
		if (distance < minDistance) {
			minDistance = distance;
			nearestRivalIndex = i;
		}
	}
	// �ł��߂��G�����������ꍇ�A���ݑΉ�����G���X�V
	if (nearestRivalIndex != -1)currentRivalIndex = nearestRivalIndex;
}


void Enemy::Update() {
	for (int i = 0; i < CHARACTER_MAX_NUM; i++)
	{
		dvd[i].x += next_dvd[i].x;
		dvd[i].y += next_dvd[i].y;
		// ��ʂ̒[�ɒB�����甽��
		if (dvd[i].x < radius || dvd[i].x > SCREEN_SIZE_X - radius)
			next_dvd[i].x = -next_dvd[i].x;
		if (dvd[i].y < radius || dvd[i].y > SCREEN_SIZE_Y - radius)
			next_dvd[i].y = -next_dvd[i].y;
	}
}

void Enemy::NearsRival()
{
	int dx_player = dvd[currentRivalIndex].x - m_pos.x - ((float)EnemySize / 2);
	int dy_player = dvd[currentRivalIndex].y - m_pos.y - ((float)EnemySize / 2);
	float distance_player = sqrt(dx_player * dx_player + dy_player * dy_player);

	float angle = atan2(dy_player, dx_player); // �G�ƃL�����N�^�[�̊p�x
	speed = MaxEnemySpeed;

	m_next_pos.x += speed * cos(angle); // X�����̈ړ�
}


void Enemy::Jump()
{
	//�W�����v����
	if (!isJump) {
		jumpPower = 40.0;
		//��ԋ߂��G����ɂ���ꍇ�W�����v
		if (dvd[currentRivalIndex].y < m_pos.y - EnemySize)
			isJump = true;
	}
	if (isJump) {
		m_next_pos.y -= jumpPower;
		jumpPower -= 1.2;
		if (jumpPower <= 0) {
			jumpPower = 0;
		}
	}
}



void Enemy::Fin()
{
}

void Enemy::Draw() {
	//�v���C���[��`��
	if (speed == 0.0 && !EnemyGoalFlag)
	{
		changeAnimFlame = 10;
		animFlameCount++;
		if (animFlameCount >= changeAnimFlame) {
			animFlameCount = 0;
			animIndex++;
			if (animIndex >= 4) {
				animIndex = 0;
			}
			else if (animIndex <= 0) {
				animIndex = 3;
			}
		}
	}
	else if (speed != 0.0 && !EnemyGoalFlag)
	{
		changeAnimFlame = 6;
		animFlameCount++;
		if (animFlameCount >= changeAnimFlame) {
			animFlameCount = 0;
			animIndex++;
			if (animIndex >= 8) {
				animIndex = 4;
			}
			else if (animIndex <= 4) {
				animIndex = 7;
			}
		}
	}
	else
	{
		changeAnimFlame = 10;
		animFlameCount++;
		if (animFlameCount >= changeAnimFlame) {
			animFlameCount = 0;
			animIndex++;
			if (animIndex >= 10) {
				animIndex = 8;
			}
			else if (animIndex <= 8) {
				animIndex = 9;
			}
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);
	DrawGraph(m_pos.x, m_pos.y, EnemyHan[animIndex], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	for (int i = 0; i < CHARACTER_MAX_NUM; i++)
	{
		DrawCircle(dvd[i].x, dvd[i].y, radius, GetColor(255, 255, 255), TRUE);
	}
	if (SCREEN_SIZE_X<m_pos.x &&
		0>m_pos.x &&
		SCREEN_SIZE_Y<m_pos.y &&
		0>m_pos.y)
	{

	}
		//DrawString(0, 0, "�O�ɏo��", GetColor(255, 0, 0));
	//DrawFormatString(0, 17, GetColor(255, 0, 0), "x=%f\ny=%f", m_pos.x, m_pos.y);
	//DrawFormatString(0, 51, GetColor(255, 0, 0), "x=%f\ny=%f", m_next_pos.x, m_next_pos.y);
}

// �i��ł���������`�F�b�N
// �㉺���E�̏��ɂȂ��Ă���
void Enemy::GetMoveDirection(bool* _dirArray) {
	// �E�����̃`�F�b�N
	if (GetNextEnemyPosX() > GetEnemyPosX()) {
		_dirArray[3] = true;
	}

	// �������̃`�F�b�N
	if (GetNextEnemyPosX() < GetEnemyPosX()) {
		_dirArray[2] = true;
	}
	// �������̃`�F�b�N
	if (GetNextEnemyPosY() > GetEnemyPosY()) {
		_dirArray[1] = true;
	}

	// ������̃`�F�b�N
	if (GetNextEnemyPosY() < GetEnemyPosY()) {
		_dirArray[0] = true;
	}
}

float Enemy::lerp(float start, float end, float t) {
	return start + t * (end - start);
}

void Enemy::SetEnemyOnSwitchTrue()
{
	EnemyOnSwitch = true;
}

void Enemy::SetEnemyOnSwitchFalse()
{
	EnemyOnSwitch = false;
}