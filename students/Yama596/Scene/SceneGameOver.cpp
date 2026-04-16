#include "SceneGameOver.h"
#include "SceneTitle.h"
#include "SceneMain.h"

#include "DxLib.h"
#include <cassert>

#include "../Utility/Color.h"
#include "../Utility/Game.h"

namespace {

    const char* const kGrapPath = ".\\Resource\\BackGround_1.jpg";    // 背景のファイルパス

    constexpr int kPosX = 1980 / 2;                                   // 背景の初期X座標(仮)

    constexpr int kPosY = 1080 / 1.8f;                                // 背景の初期Y座標(仮)

}

SceneGameOver::SceneGameOver() :
    m_graphHandle(-1),
    m_select(0),
    m_firstFrame(false),
    m_retrySelect(false),
    m_titleSelect(false)
{
}

void SceneGameOver::Init()
{

    // 画像を読み込む
    m_graphHandle = LoadGraph(kGrapPath);

    // 読み込みが失敗していたら警告する
    if (m_graphHandle == -1) {

        assert(false && "画像読み込み失敗");

    }

}

void SceneGameOver::End()
{

    // 読み込んだ画像のグラフィックハンドルを削除
    DeleteGraph(m_graphHandle);

}

SceneBase* SceneGameOver::Update()
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

            m_retrySelect = true;

            StartFadeOut();

        }
        else if (m_select == 1) {

            m_titleSelect = true;

            StartFadeOut();

        }

    }

    UpdateFade();

    if (IsFadeOutEnd()) {

        if (m_retrySelect) {

            // シーン遷移
            return new SceneMain;

        }
        else if (m_titleSelect) {

            // シーン遷移
            return new SceneTitle;

        }

    }

    // 状態更新
    prevReturn = nowReturn;
    prevZ = nowZ;

    /*

    // 1F前の状態
    static bool prevX = (CheckHitKey(KEY_INPUT_X) == 1);

    // 現在の状態
    bool nowX = (CheckHitKey(KEY_INPUT_X) == 1);

    // 押した瞬間だけシーン遷移させる
    if (nowX && !prevX)
    {

        // 連続遷移防止
        prevX = true;

        // シーン遷移
        return new SceneTitle;

    }

    // 状態更新
    prevX = nowX;

    */

    return this;

}

void SceneGameOver::Draw()
{

    // 背景を描画する(仮)
    DrawExtendGraph(0, 0, kPosX, kPosY, m_graphHandle, TRUE);

    DrawTitleMenu();

    DrawFade();

#ifdef _DEBUG

    printfDx("ここはゲームオーバーシーンです\n");

    printfDx("m_select : %d\n", m_select);

    printfDx("WSで選択、ENTERで決定\n");

#endif

}

void SceneGameOver::SelectMenu()
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

        if (m_select < 0) m_select = 1;

    }

    if (nowS && !prevS || nowDown && !prevDown) {

        m_select++;

        if (m_select > 1) m_select = 0;

    }

    // 状態更新
    prevW = nowW;
    prevS = nowS;
    prevUp = nowUp;
    prevDown = nowDown;

}

void SceneGameOver::DrawTitleMenu()
{

    int width1 = GetDrawStringWidth("ゲームオーバー", strlen("ゲームオーバー"));

    DrawString((Game::kScreenWidth - width1) / 2, 150, "ゲームオーバー", Color::kWhite);

    int width2 = GetDrawStringWidth("もういちど", strlen("もういちど"));

    DrawString((Game::kScreenWidth - width2) / 2, 425, "もういちど", m_select == 0 ? Color::kYellow : Color::kWhite);

    int width3 = GetDrawStringWidth("タイトルに戻る", strlen("タイトルに戻る"));

    DrawString((Game::kScreenWidth - width3) / 2, 475, "タイトルに戻る", m_select == 1 ? Color::kYellow : Color::kWhite);

}
