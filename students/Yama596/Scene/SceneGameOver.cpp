#include "SceneGameOver.h"
#include "SceneTitle.h"
#include "DxLib.h"

SceneGameOver::SceneGameOver()
{
}

void SceneGameOver::Init()
{
}

void SceneGameOver::End()
{
}

SceneBase* SceneGameOver::Update()
{

    // 1F前の状態
    static bool prevX = (CheckHitKey(KEY_INPUT_X) == 1);

    // 現在の状態
    bool nowX = (CheckHitKey(KEY_INPUT_X) == 1);

    // 押した瞬間だけシーン遷移させる
    if (nowX && !prevX)
    {

        // 連続遷移防止
        prevX = true;

        // シーン遷移
        return new SceneTitle;

    }

    // 状態更新
    prevX = nowX;

    return this;

}

void SceneGameOver::Draw()
{

#ifdef _DEBUG

    printfDx("ここはゲームクリアシーンです\n");

    printfDx("Xキーでタイトルシーンに行く\n");

#endif

}
