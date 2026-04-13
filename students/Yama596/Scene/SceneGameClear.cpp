#include "SceneGameClear.h"
#include "SceneTitle.h"
#include "DxLib.h"

SceneGameClear::SceneGameClear()
{
}

void SceneGameClear::Init()
{
}

void SceneGameClear::End()
{
}

SceneBase* SceneGameClear::Update()
{

    // 1F前の状態
    static bool prev = (CheckHitKey(KEY_INPUT_SPACE) == 1);

    // 現在の状態
    bool now = (CheckHitKey(KEY_INPUT_SPACE) == 1);

    // 押した瞬間だけシーン遷移させる
    if (now && !prev)
    {

        // 連続遷移防止
        prev = true;

        // シーン遷移
        return new SceneTitle;

    }

    // 状態更新
    prev = now;

    return this;

}

void SceneGameClear::Draw()
{

#ifdef _DEBUG

    printfDx("ここはゲームクリアシーンです\n");

    printfDx("Zキーでタイトルシーンに行く\n");

#endif

}
