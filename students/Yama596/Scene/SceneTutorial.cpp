#include "SceneTutorial.h"
#include "SceneTitle.h"

#include "DxLib.h"

#include "../Utility/Color.h"
#include "../Utility/Game.h"
#include "../Utility/Input.h"

SceneTutorial::SceneTutorial() :
    m_firstFrame(false),
    m_tutorialEnd(false),
    m_Pause(false)
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

    // 最初のフレームだったら
    if (m_firstFrame) {

        // 連続遷移防止
        prevEscape = true;

        // フラグを落とす
        m_firstFrame = false;

    }

    // 押した瞬間だけシーン遷移させる
    if (nowEscape && !prevEscape)
    {

        m_tutorialEnd = true;

        StartFadeOut();

    }

    UpdateFade();

    if (IsFadeOutEnd()) {

        // シーン遷移
        return new SceneTitle;

    }

    // 状態更新
    prevEscape = nowEscape;

    return this;

}

void SceneTutorial::Draw()
{

    DrawFade();

#ifdef _DEBUG

    printfDx("ここはチュートリアルシーンです\n");

    printfDx("ESCキーでタイトルシーンに行く\n");

    printfDx("Pause : %s\n", m_Pause ? "はい" : "いいえ");

#endif

}