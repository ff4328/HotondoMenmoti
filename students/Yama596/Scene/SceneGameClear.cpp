#include "SceneGameClear.h"
#include "SceneTitle.h"
#include "SceneMain.h"

#include "DxLib.h"

#include "../Utility/Color.h"
#include "../Utility/Game.h"

SceneGameClear::SceneGameClear() :
    m_firstFrame(true)
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
    static bool prevC = (CheckHitKey(KEY_INPUT_C) == 1);

    // 現在の状態
    bool nowZ = (CheckHitKey(KEY_INPUT_Z) == 1);
    bool nowC = (CheckHitKey(KEY_INPUT_C) == 1);

    if (m_firstFrame) {

        // 連続遷移防止
        prevZ = true;
        prevC = true;

        m_firstFrame = false;

    }

    // 押した瞬間だけシーン遷移させる
    if (nowZ && !prevZ)
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
    prevZ = nowZ;
    prevC = nowC;

    return this;

}

void SceneGameClear::Draw()
{

    int width1 = GetDrawStringWidth("ゲームクリア", strlen("ゲームクリア"));

    DrawString((Game::kScreenWidth - width1) / 2, 150, "ゲームクリア", Color::kWhite);

#ifdef _DEBUG

    printfDx("ここはゲームクリアシーンです\n");

    printfDx("Zキーでタイトルシーンに行く\n");

    printfDx("Cキーでメインシーンに行く\n");

#endif

}
