#include "SceneTutorial.h"
#include "SceneTitle.h"

#include "DxLib.h"

#include "../Utility/Color.h"
#include "../Utility/Game.h"

SceneTutorial::SceneTutorial()
{
}

void SceneTutorial::Init()
{
}

void SceneTutorial::End()
{
}

SceneBase* SceneTutorial::Update()
{

    // 1F前の状態
    static bool prevEscape = (CheckHitKey(KEY_INPUT_ESCAPE) == 1);

    // 現在の状態
    bool nowEscape = (CheckHitKey(KEY_INPUT_ESCAPE) == 1);

    // 押した瞬間だけシーン遷移させる
    if (nowEscape && !prevEscape)
    {

        // 連続遷移防止
        prevEscape = true;

        // シーン遷移
        return new SceneTitle;

    }

    // 状態更新
    prevEscape = nowEscape;

    return this;

}

void SceneTutorial::Draw()
{

    int width1 = GetDrawStringWidth("チュートリアル", strlen("チュートリアル"));

    DrawString((Game::kScreenWidth - width1) / 2, 150, "チュートリアル", Color::kWhite);

#ifdef _DEBUG

    printfDx("ここはチュートリアルシーンです\n");

    printfDx("ESCキーでタイトルシーンに行く\n");

#endif

}