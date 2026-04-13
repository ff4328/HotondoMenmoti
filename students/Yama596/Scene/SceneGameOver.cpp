#include "SceneGameOver.h"
#include "SceneTitle.h"
#include "SceneMain.h"

#include "DxLib.h"

#include "../Utility/Color.h"
#include "../Utility/Game.h"

SceneGameOver::SceneGameOver() :
    m_firstFrame(true)
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
    static bool prevC = (CheckHitKey(KEY_INPUT_C) == 1);

    // 現在の状態
    bool nowX = (CheckHitKey(KEY_INPUT_X) == 1);
    bool nowC = (CheckHitKey(KEY_INPUT_C) == 1);

    if (m_firstFrame) {

        // 連続遷移防止
        prevX = true;
        prevC = true;

        m_firstFrame = false;

    }

    // 押した瞬間だけシーン遷移させる
    if (nowX && !prevX)
    {

        // シーン遷移
        return new SceneTitle;

    }
    if (nowC && !prevC)
    {

        // シーン遷移
        return new SceneMain;

    }

    // 状態更新
    prevX = nowX;
    prevC = nowC;

    return this;

}

void SceneGameOver::Draw()
{

    int width1 = GetDrawStringWidth("ゲームオーバー", strlen("ゲームオーバー"));

    DrawString((Game::kScreenWidth - width1) / 2, 150, "ゲームオーバー", Color::kWhite);

#ifdef _DEBUG

    printfDx("ここはゲームクリアシーンです\n");

    printfDx("Xキーでタイトルシーンに行く\n");

    printfDx("Cキーでメインシーンに行く\n");

#endif

}
