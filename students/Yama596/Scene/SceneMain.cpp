#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneGameClear.h"
#include "SceneGameOver.h"

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
    static bool prevSpace = (CheckHitKey(KEY_INPUT_SPACE) == 1);
    static bool prevZ = (CheckHitKey(KEY_INPUT_Z) == 1);
    static bool prevX = (CheckHitKey(KEY_INPUT_X) == 1);

    // 現在の状態
    bool nowSpace = (CheckHitKey(KEY_INPUT_SPACE) == 1);
    bool nowZ = (CheckHitKey(KEY_INPUT_Z) == 1);
    bool nowX = (CheckHitKey(KEY_INPUT_X) == 1);

    // 押した瞬間だけシーン遷移させる
    if (nowSpace && !prevSpace)
    {

        // 連続遷移防止
        prevSpace = true;

        // シーン遷移
        return new SceneTitle;

    }
    else if (prevZ && !nowZ)
    {

        // 連続遷移防止
        nowZ = true;

        // シーン遷移
        return new SceneGameClear;

    }
    else if (prevX && !nowX)
    {

        // 連続遷移防止
        nowX = true;

        // シーン遷移
        return new SceneGameOver;

    }

    // 状態更新
    prevSpace = nowSpace;
    prevZ = nowZ;
    prevX = nowX;

    return this;

}

void SceneMain::Draw()
{

#ifdef _DEBUG

	printfDx("ここはメインシーンです\n");

    printfDx("スペースキーでタイトルシーンに行く\n");

    printfDx("Zキーでゲームクリアシーンに行く\n");

#endif

}
