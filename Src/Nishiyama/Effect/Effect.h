
#ifndef __EFFECT_H__
#define __EFFECT_H__

//設定フレームレート（60FPS）
#define FRAME_RATE	(60)

//１フレームの時間（ミリ秒）
#define FRAME_TIME	(1000 / FRAME_RATE)


//エフェクトの種類
enum EFFECT_TYPE
{
	EFFECT_TYPE_JUMP = 0,	//ジャンプ
	EFFECT_TYPE_HIT,		//ヒット

	EFFECT_TYPE_NUM,
};

//エフェクトの読み込み
//引数	：エフェクトの種類、作成数
void LoadEffect(EFFECT_TYPE type, int create_num);

//エフェクトの初期化
void InitEffect();

//エフェクト通常処理
void StepEffect();

//エフェクト描画処理
void DrawEffect();

//エフェクトの後処理
void FinEffect();

//エフェクトの再生
//引数	：エフェクトの種類, Ｘ座標, Ｙ座標, １枚あたりの表示時間
void PlayEffect(EFFECT_TYPE type, int x, int y);


#endif
