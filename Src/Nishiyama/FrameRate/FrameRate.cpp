#include "DxLib.h"
#include "FrameRate.h"
#include "../NumberFont/NumberFont.h"
#include "../NumberFont/NumberFontData.h"
#include "../../Common.h"

FrameRateInfo frameRateInfo;

c_Number FrameNumData;

bool FrameRateAdmin()
{
	Sleep(1);	//システムに処理を返す

	//現在の時間を取得
	frameRateInfo.currentTime = GetNowCount();

	//最初のループなら
	// ナンバーフォントデータを初期化
	//現在の時間を、FPSの計算をした時間に設定
	if (frameRateInfo.calcFpsTime == 0.0f)
	{
		FrameNumData.Init();
		FrameNumData.SetNumberFont(Number_6_12_white);
		FrameNumData.Set_posX(SCREEN_SIZE_X);
		FrameNumData.Set_posY(SCREEN_SIZE_Y);

		frameRateInfo.calcFpsTime = frameRateInfo.currentTime;
		frameRateInfo.fps = (float)FRAME_RATE;
	}

	//現在の時間が、前回のフレーム時より
	//FRAME_TIME以上経過していたら処理を実行する
	if (frameRateInfo.currentTime - frameRateInfo.lastFrateTime >= FRAME_TIME)
	{
		//フレーム実行時の時間を更新
		frameRateInfo.lastFrateTime = frameRateInfo.currentTime;

		//フレーム数をカウント
		frameRateInfo.count++;

		return true;
	}

	return false;
}

void CalcFPS()
{
	//前回のFPSを計算した時間からの経過時間を求める
	int difTime = frameRateInfo.currentTime - frameRateInfo.calcFpsTime;

	//前回のFPSを計算した時間から
	//1秒以上経過していたらFPSを計算する
	if (difTime > 1000)
	{
		//フレーム回数をミリ秒に合わせる
		//小数まで出したいのでfloatにキャスト
		float frameCount = (float)(frameRateInfo.count * 1000.0f);

		//FPSを求める
		//理想の数値は 60000 / 1000 で 60 となる	(FRAME_RATE = 60 の場合)
		frameRateInfo.fps = frameCount / difTime;

		//フレームレートカウントをクリア
		frameRateInfo.count = 0;

		//FPSを計算した時間を更新
		frameRateInfo.calcFpsTime = frameRateInfo.currentTime;
	}
}

//FPS表示（デバック用）
void DrawFPS()
{
	FrameNumData.Draw_float(frameRateInfo.fps, 2, true, true);
}
