#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneTutorial.h"

#include "DxLib.h"
#include <cassert>

#include "../Utility/Color.h"
#include "../Utility/Game.h"

namespace {

    const char* const kGrapPath = ".\\Resource\\BackGround_1.jpg";    // 背景のファイルパス

    constexpr int kPosX = 1980 / 2;                                   // 背景の初期X座標

    constexpr int kPosY = 1080 / 1.8f;                                // 背景の初期Y座標

}

SceneTitle::SceneTitle() :
    m_graphHandle(-1),
    m_select(0),
    m_firstFrame(true)
{
}

void SceneTitle::Init()
{

    m_graphHandle = LoadGraph(kGrapPath);

    // 読み込みが失敗していたら警告する
    if (m_graphHandle == -1) {

        assert(false && "画像読み込み失敗");

    }

}

void SceneTitle::End()
{
}

SceneBase* SceneTitle::Update()
{

    SelectMenu();

    // 1F前の状態
    static bool prevReturn = (CheckHitKey(KEY_INPUT_RETURN) == 1);
    static bool prevZ = (CheckHitKey(KEY_INPUT_Z) == 1);

    // 現在の状態
    bool nowReturn = (CheckHitKey(KEY_INPUT_RETURN) == 1);
    bool nowZ = (CheckHitKey(KEY_INPUT_Z) == 1);

    // 最初のフレームだったら
    if (m_firstFrame) {

        // 連続遷移防止
        prevReturn = true;
        prevZ = true;

        // フラグを落とす
        m_firstFrame = false;

    }

    // 押した瞬間だけシーン遷移させる
    if (nowReturn && !prevReturn || nowZ && !prevZ) {

        if (m_select == 0) {

            // シーン遷移
            return new SceneMain;

        }
        else if (m_select == 1) {

            // シーン遷移
            return new SceneTutorial;

        }
        else if (m_select == 2) {

            // 終了処理
            DxLib_End();

        }

    }

    // 状態更新
    prevReturn = nowReturn;
    prevZ = nowZ;

    /*

    // 1F前の状態
    static bool prevSpace = (CheckHitKey(KEY_INPUT_SPACE) == 1);
    static bool prevEscape = (CheckHitKey(KEY_INPUT_ESCAPE) == 1);
    static bool prevE = (CheckHitKey(KEY_INPUT_E) == 1);

    // 現在の状態
    bool nowSpace = (CheckHitKey(KEY_INPUT_SPACE) == 1);
    bool nowEscape = (CheckHitKey(KEY_INPUT_ESCAPE) == 1);
    bool nowE = (CheckHitKey(KEY_INPUT_E) == 1);

    // 押した瞬間だけシーン遷移させる
    if (nowSpace && !prevSpace)
    {

        // 連続遷移防止
        prevSpace = true;

        // シーン遷移
        return new SceneMain;

    }
    if (nowEscape && !prevEscape)
    {

        // 連続遷移防止
        prevEscape = true;

        // シーン遷移
        return new SceneTutorial;

    }
    if (nowE && !prevE)
    {

        // 終了処理
        DxLib_End();

        return nullptr;

    }

    // 状態更新
    prevSpace = nowSpace;
    prevEscape = nowEscape;

    */

	return this;

}

void SceneTitle::Draw()
{

    // 背景を描画する(仮)
    DrawExtendGraph(0, 0, kPosX, kPosY, m_graphHandle, TRUE);

    DrawTitleMenu();

#ifdef _DEBUG

	printfDx("ここはタイトルシーンです\n");

    printfDx("m_select : %d\n", m_select);

#endif

}

void SceneTitle::SelectMenu()
{

    // 1F前の状態
    static bool prevW = (CheckHitKey(KEY_INPUT_W) == 1);
    static bool prevS = (CheckHitKey(KEY_INPUT_S) == 1);
    static bool prevUp = (CheckHitKey(KEY_INPUT_UP) == 1);
    static bool prevDown = (CheckHitKey(KEY_INPUT_DOWN) == 1);

    // 現在の状態
    bool nowW = (CheckHitKey(KEY_INPUT_W) == 1);
    bool nowS = (CheckHitKey(KEY_INPUT_S) == 1);
    bool nowUp = (CheckHitKey(KEY_INPUT_UP) == 1);
    bool nowDown = (CheckHitKey(KEY_INPUT_DOWN) == 1);

    if (nowW && !prevW || nowUp && !prevUp) {

        m_select--;

        if (m_select < 0) m_select = 2;

    }

    if (nowS && !prevS || nowDown && !prevDown) {

        m_select++;

        if (m_select > 2) m_select = 0;

    }

    // 状態更新
    prevW = nowW;
    prevS = nowS;
    prevUp = nowUp;
    prevDown = nowDown;

}

void SceneTitle::DrawTitleMenu()
{

    int width1 = GetDrawStringWidth("Adventure Survivor", strlen("Adventure Survivor"));

    DrawString((Game::kScreenWidth - width1) / 2, 150, "Adventure Survivor", Color::kWhite);

    int width2 = GetDrawStringWidth("スタート", strlen("スタート"));

    DrawString((Game::kScreenWidth - width2) / 2, 400, "スタート", m_select == 0 ? Color::kYellow : Color::kWhite);

    int width3 = GetDrawStringWidth("チュートリアル", strlen("チュートリアル"));

    DrawString((Game::kScreenWidth - width3) / 2, 450, "チュートリアル", m_select == 1 ? Color::kYellow : Color::kWhite);

    int width4 = GetDrawStringWidth("終了", strlen("終了"));

    DrawString((Game::kScreenWidth - width4) / 2, 500, "終了", m_select == 2 ? Color::kYellow : Color::kWhite);

}
