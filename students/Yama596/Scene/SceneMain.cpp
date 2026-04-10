#include "SceneMain.h"
#include "SceneTitle.h"

#include "DxLib.h"

SceneMain::SceneMain()
{
}

void SceneMain::Init()
{

}

void SceneMain::End()
{

}

SceneBase* SceneMain::Update()
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

void SceneMain::Draw()
{

#ifdef _DEBUG

	printfDx("ここはメインシーンです\n");

#endif

}
