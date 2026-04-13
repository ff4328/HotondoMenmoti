#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneTutorial.h"

#include "DxLib.h"

#include "../Utility/Color.h"
#include "../Utility/Game.h"

SceneTitle::SceneTitle() :
    m_firstFrame(true)
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

    // 1F前の状態
    static bool prevSpace = (CheckHitKey(KEY_INPUT_SPACE) == 1);
    static bool prevEscape = (CheckHitKey(KEY_INPUT_ESCAPE) == 1);
    static bool prevE = (CheckHitKey(KEY_INPUT_E) == 1);

    // 現在の状態
    bool nowSpace = (CheckHitKey(KEY_INPUT_SPACE) == 1);
    bool nowEscape = (CheckHitKey(KEY_INPUT_ESCAPE) == 1);
    bool nowE = (CheckHitKey(KEY_INPUT_E) == 1);

    if (m_firstFrame) {

        // 連続遷移防止
        prevSpace = true;
        prevEscape = true;

        m_firstFrame = false;

    }

    // 押した瞬間だけシーン遷移させる
    if (nowSpace && !prevSpace)
    {

        // シーン遷移
        return new SceneMain;

    }
    if (nowEscape && !prevEscape)
    {

        // シーン遷移
        return new SceneTutorial;

    }
    if (nowE && !prevE)
    {

        DxLib_End();

        return nullptr;

    }

    // 状態更新
    prevSpace = nowSpace;
    prevEscape = nowEscape;

	return this;

}

void SceneTitle::Draw()
{

    int width1 = GetDrawStringWidth("Adventure Survivor", strlen("Adventure Survivor"));

    DrawString((Game::kScreenWidth - width1) / 2, 150, "Adventure Survivor", Color::kWhite);

    int width2 = GetDrawStringWidth("スタート", strlen("スタート"));

    DrawString((Game::kScreenWidth - width2) / 2, 400, "スタート", Color::kWhite);

    int width3 = GetDrawStringWidth("チュートリアル", strlen("チュートリアル"));

    DrawString((Game::kScreenWidth - width3) / 2, 450, "チュートリアル", Color::kWhite);

    int width4 = GetDrawStringWidth("終了", strlen("終了"));

    DrawString((Game::kScreenWidth - width4) / 2, 500, "終了", Color::kWhite);

#ifdef _DEBUG

	printfDx("ここはタイトルシーンです\n");

    printfDx("スペースキーでメインシーンに行く\n");

    printfDx("ESCキーでチュートリアルシーンに行く\n");

    printfDx("Eキーでゲームを終了\n");

#endif

}
