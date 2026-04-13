#include "SceneTitle.h"
#include "SceneMain.h"

#include "DxLib.h"

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

    // 1F前の状態
    static bool prevSpace = (CheckHitKey(KEY_INPUT_SPACE) == 1);

    // 現在の状態
    bool nowSpace = (CheckHitKey(KEY_INPUT_SPACE) == 1);



    // 押した瞬間だけシーン遷移させる
    if (nowSpace && !prevSpace)
    {

        // 連続遷移防止
        prevSpace = true;

        // シーン遷移
        return new SceneMain;

    }

    // 状態更新
    prevSpace = nowSpace;

	return this;

}

void SceneTitle::Draw()
{

#ifdef _DEBUG

	printfDx("ここはタイトルシーンです");

#endif

}
