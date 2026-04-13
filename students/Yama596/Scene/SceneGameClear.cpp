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

    // 次に遷移するシーン
    SceneBase* next = this;

    // 1F前のキーの状態
    static bool prevZ = (CheckHitKey(KEY_INPUT_Z) == 1);

    // 現在のキーの状態
    bool nowZ = (CheckHitKey(KEY_INPUT_Z) == 1);

    // シーン開始直後なら
    if (m_firstFrame)
    {

        // 連続遷移防止
        prevZ = true;

        m_firstFrame = false;

    }

    // 押した瞬間だけシーン遷移させる
    if (nowZ && !prevZ)
    {

        // シーン遷移
        next = new  SceneTitle;

    }

    // 状態更新
    prevZ = nowZ;

    return next;

}

void SceneGameClear::Draw()
{

#ifdef _DEBUG

    printfDx("ここはゲームクリアシーンです\n");

    printfDx("Zキーでタイトルシーンに行く\n");

#endif

}
