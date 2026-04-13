#include "SceneTitle.h"
#include "SceneMain.h"

#include "DxLib.h"
#include "SceneBase.h"

#include "../Utility/Color.h"
#include "../Utility/Game.h"

SceneTitle::SceneTitle()
{
}

void SceneTitle::Init()
{
}

void SceneTitle::End()
{
}

SceneBase* SceneTitle::Update()
{

    // 次に遷移するシーン
    SceneBase* next = this;

    // 1F前のキーの状態
    static bool prevSpace = (CheckHitKey(KEY_INPUT_SPACE) == 1);

    // 現在のキーの状態
    bool nowSpace = (CheckHitKey(KEY_INPUT_SPACE) == 1);

    // シーン開始直後なら
    if (m_firstFrame)
    {

        // 連続遷移防止
        prevSpace = true;

        m_firstFrame = false;

    }

    // 押した瞬間だけシーン遷移させる
    if (nowSpace && !prevSpace)
    {

        // シーン遷移
        next = new SceneMain;

    }

    // 状態更新
    prevSpace = nowSpace;

	return next;

}

void SceneTitle::Draw()
{

    int width1 = GetDrawStringWidth("Adventures Survivor", strlen("Adventures Survivor"));

    DrawString((Game::kScreenWidth - width1) / 2, 150, "Adventures Survivor", Color::kWhite);

    int width2 = GetDrawStringWidth("スタート", strlen("スタート"));

    DrawString((Game::kScreenWidth - width2) / 2, 400, "スタート", Color::kWhite);

    int width3 = GetDrawStringWidth("チュートリアル", strlen("チュートリアル"));

    DrawString((Game::kScreenWidth - width3) / 2, 450, "チュートリアル", Color::kWhite);

    int width4 = GetDrawStringWidth("終了", strlen("終了"));

    DrawString((Game::kScreenWidth - width4) / 2, 500, "終了", Color::kWhite);

#ifdef _DEBUG

	printfDx("ここはタイトルシーンです\n");

    printfDx("スペースキーでメインシーンに行く\n");

#endif

}
