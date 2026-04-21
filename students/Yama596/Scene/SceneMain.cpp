#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneGameClear.h"
#include "SceneGameOver.h"

//#include "../students/FIREBAR/FIREBAR_Scene.h"
#include "../students/FIREBAR/LotteryPusive.h"
#include "../students/bamboojr36/Items.h"
#include "../students/mcd6752Tuyoshi/Map/Map.h"
#include "../students/mcd6752Tuyoshi/ExpBar/EXPBar.h"
#include "../students/mcd6752Tuyoshi/Timer/Timer.h"
#include "../students/Yama596/Enemy/EnemyManagerYama.h"
#include "../students/oreistake/Camera.h"

#include "DxLib.h"
#include <cassert>
#include <string>
#include <vector>
#include <iostream>

bool k = false;

SceneMain::SceneMain() :
    m_firstFrame(false),
    m_bossDead(false),
    m_playerDead(false),
    m_playerHit(false),
    m_Pause(false),
    m_playerInvincibleTime(0.0f),
    m_pPlayer(nullptr),
    m_pEnemy(nullptr),
    // m_pEnemyMgr(nullptr),
    m_pMap(nullptr),
    m_pCollision(nullptr),
    m_Item(nullptr),
    m_pTimer(nullptr),
    m_pLotteryPassive(nullptr),
    m_pWeaponManager(nullptr),
    m_pPlayerStatus(nullptr),
    m_pEXPBar(nullptr),
    m_pCamera(nullptr)
{
    m_pPlayerStatus = new PlayerStatus();

    m_pPlayer = new PlayerMove(m_pPlayerStatus);

    m_pEnemy = new EnemyYama();

    // m_pEnemyMgr = new EnemyManagerYama();

    m_pMap = new Map();

    m_pCollision = new Collision();

    m_Item = std::make_unique<Items>(m_pPlayer, m_pEnemy, m_pPlayerStatus);

    m_pTimer = std::make_unique<Timer>();

    m_pWeaponManager = new WeaponStatus(m_pPlayer);

    m_pEXPBar = new EXPBar(m_pPlayerStatus);

    m_pCamera = new Camera();

    m_pLotteryPassive = new LotteryPassive(m_pWeaponManager, m_pPlayerStatus, m_pEXPBar);
}

void SceneMain::Init()
{

    m_pTimer->Init(false, 5);

    m_pPlayer->Init();

    m_pWeaponManager->Init();

    m_pEnemy->Init();

    // m_pEnemyMgr->Init();

    m_pMap->Init();

    m_pEnemy->SetPlayer(m_pPlayer);

    m_Item->Init();

    //m_pWeaponManager->Init();

    m_pPlayerStatus->Init();

    m_pEXPBar->Init();

    m_pCamera->Init(m_pPlayer,m_pMap);

    m_pLotteryPassive->Init();
}

void SceneMain::End()
{

    m_pPlayer->End();
    delete m_pPlayer;
    m_pPlayer = nullptr;

    m_pEnemy->End();
    delete m_pEnemy;
    m_pEnemy = nullptr;

    //m_pEnemyMgr->End();
    //delete m_pEnemyMgr;
    //m_pEnemyMgr = nullptr;

    m_pMap->End();
    delete m_pMap;
    m_pMap = nullptr;

    m_pWeaponManager->End();
    delete m_pWeaponManager;
    m_pWeaponManager = nullptr;

    m_pPlayerStatus->End();
    delete m_pPlayerStatus;
    m_pPlayerStatus = nullptr;

    m_pEXPBar->End();
    delete m_pEXPBar;
    m_pEXPBar = nullptr;

    m_pCamera->End();
    delete m_pCamera;
    m_pCamera = nullptr;

    m_pLotteryPassive->End();
    delete m_pLotteryPassive;
    m_pLotteryPassive = nullptr;

    m_Item->End();

    m_pTimer->End();
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
    if ((!m_playerDead && m_pCollision->CheckRectCommon(m_pPlayer->GetCheckRect(), m_pEnemy->GetCheckRectBat())
        || !m_playerDead && m_pCollision->CheckRectCommon(m_pPlayer->GetCheckRect(), m_pEnemy->GetCheckRectGoblin())
        || !m_playerDead && m_pCollision->CheckRectCommon(m_pPlayer->GetCheckRect(), m_pEnemy->GetCheckRectSkeleton())
        || !m_playerDead && m_pCollision->CheckRectCommon(m_pPlayer->GetCheckRect(), m_pEnemy->GetCheckRectMush())
        )&& !m_playerHit) {

        m_pPlayer->Damage(1);
        //m_pPlayerStatus->SetCurrentHP(1);
        m_playerHit = true;

    }
    
    if (m_playerHit)
    {
        m_playerInvincibleTime++;
        if (m_playerInvincibleTime >= 25.0f)
        {
            m_playerHit = false;
            m_playerInvincibleTime = 0;
        }
    }
    
    if (m_pEnemy->Dead()) {

        // 連続遷移防止
        prevSpace = true;

        // 死亡している
        m_bossDead = true;

        StartFadeOut();

    }
    else if (m_pPlayer->Dead()) {

        // 連続遷移防止
        prevSpace = true;

        StartFadeOut();

    }
    else if (nowF && !prevF)
    {

        // 連続遷移防止
        prevF = true;

        // シーン遷移
        k = true;

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
        k = true;

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
    m_pEXPBar->Update(/*m_Item->GetEXP()*/k, 10);

    m_Item->Setexp(false);

    k = false;

    m_pLotteryPassive->Update();

    if (m_pLotteryPassive->ShowSlot())return this;

    m_pTimer->Update();

    m_pWeaponManager->Update();

    //m_pPlayer->Update();

    m_pPlayer->Update(m_pPlayerStatus);

    m_pEnemy->Update();

    //m_pEnemyMgr->Update();

    m_Item->Update();

    m_pCamera->Update();

    return this;

}

void SceneMain::Draw()
{

    SetDrawScreen(m_pCamera->GetWorldScreen());

    m_pMap->Draw();

    m_pPlayer->Draw();

    m_pEnemy->Draw();

    m_Item->Draw();

    m_pWeaponManager->Draw();

    SetDrawScreen(DX_SCREEN_BACK);

    m_pCamera->Draw();

    DrawFade();

    if (m_pLotteryPassive->ShowSlot())
    {
        m_pLotteryPassive->Draw();
    }

    m_pEXPBar->Draw();

    m_pTimer->Draw();

#ifdef _DEBUG

    printfDx("ここはメインシーンです\n");

    printfDx("FキーでFIREBARのシーンに行く\n");

    printfDx("\n");

    printfDx("Pキーでプレイヤーの攻撃フラグが立つ\n");

    printfDx("ボスが死んだかどうか : %s\n", m_bossDead ? "はい" : "いいえ");

    printfDx("プレイヤーが死んだかどうか : %s\n", m_playerDead ? "はい" : "いいえ");

#endif

}