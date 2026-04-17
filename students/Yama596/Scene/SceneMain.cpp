#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneGameClear.h"
#include "SceneGameOver.h"
#include "../students/FIREBAR/FIREBAR_Scene.h"
#include "../students/bamboojr36/Items.h"
#include "../students/mcd6752Tuyoshi/Map/Map.h"
#include "DxLib.h"
#include <cassert>
#include <string>
#include <vector>
#include <iostream>

SceneMain::SceneMain() :
    m_firstFrame(false),
    m_bossDead(false),
    m_playerDead(false),
    m_Pause(false),
    m_pPlayer(nullptr),
    m_pEnemy(nullptr),
    m_pMap(nullptr),
    m_collision(nullptr),
    m_Item(nullptr)
{

    m_pPlayer = new PlayerMove();

    m_pEnemy = new EnemyYama();

    m_pMap = new Map();

    m_collision = std::make_unique<Collision>();
    m_Item = std::make_unique<Items>(m_pPlayer);
}

void SceneMain::Init()
{

    m_pPlayer->Init();

    m_pEnemy->Init();

    m_pMap->Init();

    m_pEnemy->SetPlayer(m_pPlayer);
    m_Item->Init();

}

void SceneMain::End()
{

    m_pPlayer->End();
    delete m_pPlayer;
    m_pPlayer = nullptr;

    m_pEnemy->End();
    delete m_pEnemy;
    m_pEnemy = nullptr;

    m_pMap->End();
    delete m_pMap;
    m_pMap = nullptr;

    m_Item->End();
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

    // 攻撃したら敵に100ダメージ
    if (m_pPlayer->Attack()) {

        m_pEnemy->Damege(100);

    }

    // プレイヤーと敵が当たったらプレイヤーにダメージ
    if (!m_playerDead && m_collision->CheckRectCommon(m_pPlayer->GetCheckRect(), m_pEnemy->GetCheckRectSkeleton())){

        // m_pPlayer->Damege(1);

        m_playerDead = true;

    }

    if (m_pEnemy->Dead()) {

        // 連続遷移防止
        prevSpace = true;

        // 死亡している
        m_bossDead = true;

        StartFadeOut();

    }
    else if (m_playerDead) {

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

        if (m_bossDead) {

            // シーン遷移
            return new SceneGameClear;

        }
        else if (!m_bossDead) {

            // シーン遷移
            return new SceneGameOver;

        }

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
    m_Item->Update();
    return this;

}

void SceneMain::Draw()
{

    m_pMap->Draw();

    m_pPlayer->Draw();

    m_pEnemy->Draw();

    m_Item->Draw();

    DrawFade();

#ifdef _DEBUG

	printfDx("ここはメインシーンです\n");

    printfDx("FキーでFIREBARのシーンに行く\n");

    printfDx("\n");

    printfDx("Pキーでプレイヤーの攻撃フラグが立つ\n");

    printfDx("ボスが死んだかどうか : %s\n", m_bossDead ? "はい" : "いいえ");

    printfDx("プレイヤーが死んだかどうか : %s\n", m_playerDead ? "はい" : "いいえ");

#endif

}
