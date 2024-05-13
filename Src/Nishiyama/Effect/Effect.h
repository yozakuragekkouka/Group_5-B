#pragma once

#include <DxLib.h>

//一度に表示できるエフェクト最大数
#define EFFECT_MAX_NUM		(20)

//ジャンプエフェクト
#define JUMP_EFFECT_HNDL_PATH		"Data/Image/Player/JumpEffect.png"
#define JUMP_ANIME_NUM		(6)

//ヒットエフェクト
#define HIT_EFFECT_HNDL_PATH		"Data/Image/Player/HitEffect.png"
#define HIT_ANIME_NUM		(12)

struct Hundle
{
	int JumpHndl[2][JUMP_ANIME_NUM];
	int HitHndl[2][HIT_ANIME_NUM];
};

// エフェクトアニメーションクラス
class EffectAnimation {
public:
    // エフェクトの位置
    int x, y;
    // エフェクトの現在のスケール
    float scale;
    // アニメーションのフレームカウンタ
    int frameCount;
    // アニメーションが終了したかどうか
    bool isFinished;
    // コンストラクタ
    EffectAnimation(int startX, int startY) : x(startX), y(startY), 
        scale(1.0f), frameCount(0), isFinished(false) {}
    // アニメーションを更新する関数
    void Update() {
        // アニメーションが終了していない場合は更新を続ける
        if (!isFinished) {
            // スケールを増加させる
            scale += 0.1f;
            // フレームカウントを増加させる
            frameCount++;
     
            DrawEffect();
            // アニメーションの終了条件をチェック
            if (frameCount > 30) {
                // アニメーションを終了する
                isFinished = true;
            }
        }
    }
    // エフェクトを描画する関数
    void DrawEffect() {
        // ここでエフェクトの描画を行う
        // 例: DrawRotaGraph(x, y, scale, 0, imageHandle, TRUE);
    }
};
// エフェクトアニメーションのインスタンスを作成
EffectAnimation effect(100, 100);
