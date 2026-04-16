#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneGameClear.h"
#include "SceneGameOver.h"
#include "../students/FIREBAR/FIREBAR_Scene.h"

#include "DxLib.h"
#include <cassert>
#include <string>
#include <vector>
#include <iostream>

SceneMain::SceneMain() :
    m_firstFrame(false),
    m_dead(false),
    m_Pause(false),
    m_pPlayer(nullptr),
    m_pEnemy(nullptr)
{

    m_pPlayer = new PlayerMove();

    m_pEnemy = new EnemyYama();

}

void SceneMain::Init()
{

    m_pPlayer->Init();

    m_pEnemy->Init();

}

void SceneMain::End()
{

    m_pPlayer->End();
    delete m_pPlayer;
    m_pPlayer = nullptr;

    m_pEnemy->End();
    delete m_pEnemy;
    m_pEnemy = nullptr;

}

SceneBase* SceneMain::Update()
{

    // 1F前の状態
    static bool prevSpace = (CheckHitKey(KEY_INPUT_SPACE) == 1);
    static bool prevF = (CheckHitKey(KEY_INPUT_F) == 1);
    static bool prevG = false;

    // 現在の状態
    bool nowSpace = (CheckHitKey(KEY_INPUT_SPACE) == 1);
    bool nowF = (CheckHitKey(KEY_INPUT_F) == 1);
    bool nowG = (CheckHitKey(KEY_INPUT_G) == 1);

    // 死亡してるか切り替える(仮処理)
    if (nowG && !prevG) {

        m_dead = !m_dead;

    }

    if (!m_dead && (nowSpace && !prevSpace)) {

        // 連続遷移防止
        prevSpace = true;

        StartFadeOut();

    }
    else if (m_dead && (nowSpace && !prevSpace)) {

        // 連続遷移防止
        prevSpace = true;

        StartFadeOut();

    }
    else if (nowF && !prevF)
    {

        // 連続遷移防止
        prevF = true;

        // シーン遷移
        return new FIREBAR_Scene;

    }

    UpdateFade();

    if (IsFadeOutEnd()) {

        if (!m_dead) {

            // シーン遷移
            return new SceneGameClear;

        }
        else if (m_dead) {

            // シーン遷移
            return new SceneGameOver;

        }

    }

    if (m_pPlayer->Attack()) {

        m_pEnemy->Damege(100);

    }

    // 状態更新
    prevSpace = nowSpace;
    prevF = nowF;
    prevG = nowG;

    /*

    // 押した瞬間だけシーン遷移させる
    if (nowSpace && !prevSpace)
    {

        // 連続遷移防止
        prevSpace = true;

        // シーン遷移
        return new SceneTitle;

    }
    if (nowZ && !prevZ)
    {

        // 連続遷移防止
        prevZ = true;

        // シーン遷移
        return new SceneGameClear;

    }
    if (nowX && !prevX)
    {

        // 連続遷移防止
        prevX = true;

        // シーン遷移
        return new SceneGameOver;

    }

    */

    m_pPlayer->Update();

    m_pEnemy->Update();

    return this;

}

void SceneMain::Draw()
{

    DrawFade();

    m_pPlayer->Draw();

    m_pEnemy->Draw();

#ifdef _DEBUG

	printfDx("ここはメインシーンです\n");

    printfDx("FキーでFIREBARのシーンに行く\n");

    printfDx("\n");

    printfDx("Gキーでm_deadを切り替える\n");

    printfDx("スペースキーでゲームクリアかゲームオーバーに行く\n");

    printfDx("m_dead : %s\n", m_dead ? "true" : "false");

#endif

}
