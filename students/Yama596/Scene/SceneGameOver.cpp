#include "SceneGameOver.h"
#include "SceneTitle.h"

#include "DxLib.h"

#include "../Utility/Color.h"
#include "../Utility/Game.h"

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

    // 次に遷移するシーン
    SceneBase* next = this;

    // 1F前のキーの状態
    static bool prevX = (CheckHitKey(KEY_INPUT_X) == 1);

    // 現在のキーの状態
    bool nowX = (CheckHitKey(KEY_INPUT_X) == 1);

    // シーン開始直後なら
    if (m_firstFrame)
    {

        // 連続遷移防止
        prevX = true;

        m_firstFrame = false;

    }

    // 押した瞬間だけシーン遷移させる
    if (nowX && !prevX)
    {

        // シーン遷移
        next = new SceneTitle;

    }

    // 状態更新
    prevX = nowX;

    return next;

}

void SceneGameOver::Draw()
{

    int width1 = GetDrawStringWidth("Game Over", strlen("Game Over"));

    DrawString((Game::kScreenWidth - width1) / 2, 150, "Game Over", Color::kWhite);

#ifdef _DEBUG

    printfDx("ここはゲームクリアシーンです\n");

    printfDx("Xキーでタイトルシーンに行く\n");

#endif

}
