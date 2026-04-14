#include "SceneGameClear.h"
#include "SceneTitle.h"

#include "DxLib.h"

#include "../Utility/Color.h"
#include "../Utility/Game.h"

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
    static bool prevZ = (CheckHitKey(KEY_INPUT_Z) == 1);

    // 現在の状態
    bool nowZ = (CheckHitKey(KEY_INPUT_Z) == 1);

    // 押した瞬間だけシーン遷移させる
    if (nowZ && !prevZ)
    {

        // 連続遷移防止
        prevZ = true;

        // シーン遷移
        return new SceneTitle;

    }

    // 状態更新
    prevZ = nowZ;

    return this;

}

void SceneGameClear::Draw()
{

    int width1 = GetDrawStringWidth("Game Clear", strlen("Game Clear"));

    DrawString((Game::kScreenWidth - width1) / 2, 150, "Game Clear", Color::kWhite);

#ifdef _DEBUG

    printfDx("ここはゲームクリアシーンです\n");

    printfDx("Zキーでタイトルシーンに行く\n");

#endif

}
