#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneGameClear.h"
#include "SceneGameOver.h"
//#include "../students/FIREBAR/FIREBAR_Scene.h"

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

    // 次に遷移するシーン
    SceneBase* next = this;

    // 1F前のキーの状態
    static bool prevSpace = (CheckHitKey(KEY_INPUT_SPACE) == 1);
    static bool prevZ = (CheckHitKey(KEY_INPUT_Z) == 1);
    static bool prevX = (CheckHitKey(KEY_INPUT_X) == 1);
    //static bool prevF = (CheckHitKey(KEY_INPUT_F) == 1);

    // 現在のキーの状態
    bool nowSpace = (CheckHitKey(KEY_INPUT_SPACE) == 1);
    bool nowZ = (CheckHitKey(KEY_INPUT_Z) == 1);
    bool nowX = (CheckHitKey(KEY_INPUT_X) == 1);
    //bool nowF = (CheckHitKey(KEY_INPUT_F) == 1);

    // シーン開始直後なら
    if (m_firstFrame)
    {

        // 連続遷移防止
        prevSpace = true;
        prevZ = true;
        prevX = true;

        m_firstFrame = false;

    }

    // 押した瞬間だけシーン遷移させる
    if (nowSpace && !prevSpace)
    {

        // シーン遷移
        next = new SceneTitle;

    }
    if (nowZ && !prevZ)
    {

        // シーン遷移
        next = new SceneGameClear;

    }
    if (nowX && !prevX)
    {

        // シーン遷移
        next = new SceneGameOver;

    }
    //else if (prevF && !nowF)
    //{

    //    // 連続遷移防止
    //    prevF = true;

    //    // シーン遷移
    //    return new FIREBAR_Scene;

    //}

    // 状態更新
    prevSpace = nowSpace;
    prevZ = nowZ;
    prevX = nowX;
    //prevF = nowF;

    return next;

}

void SceneMain::Draw()
{

#ifdef _DEBUG

	printfDx("ここはメインシーンです\n");

    printfDx("スペースキーでタイトルシーンに行く\n");

    printfDx("Zキーでゲームクリアシーンに行く\n");

    printfDx("Xキーでゲームオーバーシーンに行く\n");

    //printfDx("FキーでFIREBARのシーンに行く\n");

#endif

}
