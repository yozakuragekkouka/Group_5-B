#pragma once
#include "Scene.h"
#include "../BackGround/BackGround.h"
#include "../Player/Player.h"

class ScenePlay : public SceneBase
{
private:
	BackGround bg;
	PLAYER *player;

	const VECTOR Player1Pos = { 32.0f, 500.0f, 0.0f };
	const VECTOR Player2Pos = { 1248.0f, 500.0f, 0.0f };



public:
	void Init();
	void Step();
	void Draw();
	void Fin();

	//����
	void MapCollision();
	void CheckCollision(int index, bool checkY);

	//�{��
	//�e�̓����蔻��
	//����1���U����H�炤�悤�ɂ��Ă܂�
	void IsHitBullet(VECTOR BulletPos, VECTOR BulletSize, VECTOR Pos, VECTOR PosSize, int Damage, int take_damageNum, int deal_damageNum);
};