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

	//‰œ‘º
	struct MAPCollision
	{
		// ƒ}ƒbƒv‚Ì“–‚½‚è”»’è
		void MapCollision(int num);

		void CheckDirectionalCollision(int num, bool checkY);

		void HandleCollision(int num, int mapIndexY, int mapIndexX,
			bool dirArray[], int Ax, int Ay, int Aw, int Ah,
			int Bx, int By, int Bw, int Bh, bool checkY);

		void HandleDiagonalCollision(int num, int Ax, int Ay, int Aw, int Ah,
			int Bx, int By, int Bw, int Bh);

		bool IsDiagonalCollision(int Ax, int Ay, int Aw, int Ah,
			int Bx, int By, int Bw, int Bh);


	};
};