#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneGameClear.h"
#include "SceneGameOver.h"

#include "../Utility/Color.h"

//#include "../students/FIREBAR/FIREBAR_Scene.h"
#include "../students/FIREBAR/LotteryPusive.h"
#include "../students/FIREBAR/DethEnemyCounter.h"
#include "../students/bamboojr36/Items.h"
#include "../students/mcd6752Tuyoshi/Map/Map.h"
#include "../students/mcd6752Tuyoshi/ExpBar/EXPBar.h"
#include "../students/mcd6752Tuyoshi/Timer/Timer.h"
#include "../students/mcd6752Tuyoshi/ShowChoice/ShowChoiceManager.h"
#include "../students/Yama596/Enemys/BatManager.h"
#include "../students/Yama596/Enemys/GoblinManager.h"
#include "../students/Yama596/Enemys/MushroomManager.h"
#include "../students/Yama596/Enemys/SkeletonManager.h"
#include "../students/oreistake/Camera.h"

#include "DxLib.h"
#include <cassert>
#include <string>
#include <vector>
#include <iostream>


namespace
{
    bool k = false;

    float kBoxPos_X = 0;
    float kBoxPos_Y = 0;

    // 2.5秒
    const int kSpawnInterval = 150;

    // ゴブリンタイマー
    const int kGoblinTimer = 600;

    // マッシュルームタイマー
    const int kMushroomTimer = 1200;

    // スケルトンタイマー
    const int kSkeletonTimer = 1800;

}

SceneMain::SceneMain() :
    m_firstFrame(false),
    m_bossDead(false),
    m_playerDead(false),
    m_playerHit(false),
    m_Pause(false),
    m_playerInvincibleTime(0.0f),
    m_spawnTimer(0),
    m_gameCount(0),
    m_spawnGoblin(false),
    m_spawnMushroom(false),
    m_spawnSkeleton(false),
    m_batDead(false),
    m_goblinDead(false),
    m_mushroomDead(false),
    m_skeletonDead(false),
    m_pPlayer(nullptr),
    m_pMap(nullptr),
    m_pCollision(nullptr),
    m_Item(nullptr),
    m_pTimer(nullptr),
    m_pShowChoiceManager(nullptr),
    m_pD_E_Counter(nullptr),
    m_pLotteryPassive(nullptr),
    m_pWeaponManager(nullptr),
    m_pPlayerStatus(nullptr),
    m_pEXPBar(nullptr),
    m_pCamera(nullptr),
    m_pBatMgr(nullptr),
    m_pGoblinMgr(nullptr),
    m_pMushroomMgr(nullptr),
    m_pSkeletonMgr(nullptr)
{

    m_pPlayerStatus = new PlayerStatus();

    m_pPlayer = new PlayerMove(m_pPlayerStatus);

    m_pMap = new Map();

    m_pCollision = new Collision();

    m_Item = std::make_unique<Items>(m_pPlayer, m_pPlayerStatus);

    m_pTimer = std::make_unique<Timer>();

    m_pShowChoiceManager = new ShowChoiceManager();

    m_pD_E_Counter = std::make_unique<DeathEnemyCounter>();

    m_pWeaponManager = new WeaponStatus(m_pPlayer);

    m_pEXPBar = new EXPBar(m_pPlayerStatus);

    m_pCamera = new Camera();

    m_pLotteryPassive = new LotteryPassive(m_pWeaponManager, m_pPlayerStatus, m_pEXPBar, m_pShowChoiceManager);

    m_pBatMgr = new BatManager();

    m_pGoblinMgr = new GoblinManager();

    m_pMushroomMgr = new MushroomManager();

    m_pSkeletonMgr = new SkeletonManager();

}

void SceneMain::Init()
{

    m_pTimer->Init(false, 5);

    m_pPlayer->Init();

    m_pWeaponManager->Init();

    m_pD_E_Counter->Init();

    m_pMap->Init();

    m_Item->Init();

    m_pPlayerStatus->Init();

    m_pEXPBar->Init();

    m_pCamera->Init(m_pPlayer,m_pMap);

    m_pShowChoiceManager->Init();

    m_pLotteryPassive->Init();

    m_pPlayer->SetMap(m_pMap);

    m_enemyManagers.push_back(m_pBatMgr);

    m_enemyManagers.push_back(m_pGoblinMgr);

    m_enemyManagers.push_back(m_pMushroomMgr);

    m_enemyManagers.push_back(m_pSkeletonMgr);

    for (auto manager : m_enemyManagers) {

        manager->SetPlayer(m_pPlayer);

        manager->SetCamera(m_pCamera);

        manager->Init();

    }

}

void SceneMain::End()
{

    m_pPlayer->End();
    delete m_pPlayer;
    m_pPlayer = nullptr;

    for (auto manager : m_enemyManagers) {

        manager->End();

    }

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

    m_pShowChoiceManager->End();
    delete m_pShowChoiceManager;
    m_pShowChoiceManager = nullptr;

    m_pTimer->End();

    m_pD_E_Counter->End();
}

SceneBase* SceneMain::Update()
{
    kBoxPos_X = m_pPlayer->GetModelPos().x;
    kBoxPos_Y = m_pPlayer->GetModelPos().y;

    // 1F前の状態
    static bool prevF = (CheckHitKey(KEY_INPUT_F) == 1);

    // 現在の状態
    bool nowF = (CheckHitKey(KEY_INPUT_F) == 1);

    // 攻撃したら敵に100ダメージ
    if (m_pPlayer->Attack()) {

        m_pBatMgr->CheckHitAttack(100);

        m_pGoblinMgr->CheckHitAttack(100);

        m_pMushroomMgr->CheckHitAttack(100);

        m_pSkeletonMgr->CheckHitAttack(100);

    }

    // プレイヤーと敵が当たったらプレイヤーにダメージ
    if ((m_pBatMgr->CheckHitPlayer(m_pPlayer->GetCheckRect())
        || m_pGoblinMgr->CheckHitPlayer(m_pPlayer->GetCheckRect())
        || m_pMushroomMgr->CheckHitPlayer(m_pPlayer->GetCheckRect())
        || m_pSkeletonMgr->CheckHitPlayer(m_pPlayer->GetCheckRect()))
        && !m_playerHit && !m_playerDead) {

        m_pPlayer->Damage(3);

        m_playerHit = true;

    }


    ////////敵と武器の当たり判定/////////////////
   
    // プレイヤーと敵が当たったらプレイヤーにダメージ
    //if (m_pBatMgr->CheckHitPlayer(m_pWeaponManager->CheckHitEnemy(0))||
    //    m_pBatMgr->CheckHitPlayer(m_pWeaponManager->CheckHitEnemy(1))||
    //    m_pBatMgr->CheckHitPlayer(m_pWeaponManager->CheckHitEnemy(2))||
    //    m_pBatMgr->CheckHitPlayer(m_pWeaponManager->CheckHitEnemy(3)))
    //{
    //    //m_pBatMgr->CheckHitAttack(100);
    //}

    //// プレイヤーと敵が当たったらプレイヤーにダメージ
    //if (m_pGoblinMgr->CheckHitPlayer(m_pWeaponManager->CheckHitEnemy(0))||
    //    m_pGoblinMgr->CheckHitPlayer(m_pWeaponManager->CheckHitEnemy(1))||
    //    m_pGoblinMgr->CheckHitPlayer(m_pWeaponManager->CheckHitEnemy(2))||
    //    m_pGoblinMgr->CheckHitPlayer(m_pWeaponManager->CheckHitEnemy(3)))
    //{
    //    //m_pGoblinMgr->CheckHitAttack(100);
    //}

    //// プレイヤーと敵が当たったらプレイヤーにダメージ
    //if (m_pMushroomMgr->CheckHitPlayer(m_pWeaponManager->CheckHitEnemy(0))||
    //    m_pMushroomMgr->CheckHitPlayer(m_pWeaponManager->CheckHitEnemy(1))||
    //    m_pMushroomMgr->CheckHitPlayer(m_pWeaponManager->CheckHitEnemy(2))||
    //    m_pMushroomMgr->CheckHitPlayer(m_pWeaponManager->CheckHitEnemy(3)))
    //{
    //    //m_pMushroomMgr->CheckHitAttack(100);
    //}

    //// プレイヤーと敵が当たったらプレイヤーにダメージ
    //if (m_pSkeletonMgr->CheckHitPlayer(m_pWeaponManager->CheckHitEnemy(0))||
    //    m_pSkeletonMgr->CheckHitPlayer(m_pWeaponManager->CheckHitEnemy(1))||
    //    m_pSkeletonMgr->CheckHitPlayer(m_pWeaponManager->CheckHitEnemy(2))||
    //    m_pSkeletonMgr->CheckHitPlayer(m_pWeaponManager->CheckHitEnemy(3)))
    //{
    //    //m_pSkeletonMgr->CheckHitAttack(100);
    //}

    // ボムが起動したら敵にダメージ
    if (m_Item->BombTrigger())
    {

        m_pBatMgr->CheckHitAttack(100);

        m_pGoblinMgr->CheckHitAttack(100);

        m_pMushroomMgr->CheckHitAttack(100);

        m_pSkeletonMgr->CheckHitAttack(100);

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

    CharacterDead();

    if (nowF && !prevF)
    {

        // 連続遷移防止
        prevF = true;

        m_pD_E_Counter->CountUP();

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

    m_pLotteryPassive->Update();

    if (m_pLotteryPassive->ShowSlot())return this;

    // カウントアップ
    m_spawnTimer++;
    m_gameCount++;

    // 敵の出現時間管理
    if (m_spawnTimer > kGoblinTimer) m_spawnGoblin = true;
    if (m_spawnTimer > kMushroomTimer) m_spawnMushroom = true;

    // 敵を出現させる処理
    if (m_gameCount >= kSpawnInterval)
    {

        // バット生成
        m_pBatMgr->Spawn(m_pBatMgr->GetRandomSpawnPos());

        // ゴブリン生成
        if (m_spawnGoblin)
        {

            m_pGoblinMgr->Spawn(m_pGoblinMgr->GetRandomSpawnPos());

        }

        // マッシュルーム生成
        if (m_spawnMushroom)
        {

            m_pMushroomMgr->Spawn(m_pMushroomMgr->GetRandomSpawnPos());

        }

        // スケルトン生成(ボス)
        if (m_spawnTimer >= kSkeletonTimer && !m_spawnSkeleton)
        {

            m_pSkeletonMgr->Spawn(m_pSkeletonMgr->GetRandomSpawnPos());

            m_spawnSkeleton = true;

        }

        m_gameCount = 0;

    }

    m_pPlayer->Update(m_pPlayerStatus);

    for (auto manager : m_enemyManagers) {

        manager->Update();

    }

    EnemyKnockBack();

    // 状態更新
    prevF = nowF;

    m_pEXPBar->Update(m_Item->GetEXP(), 250);

    m_Item->Setexp(false);

    k = false;


    m_pTimer->Update();

    m_pWeaponManager->Update();

    m_Item->Update();

    m_pCamera->Update();

    m_pPlayer->SetMap(m_pMap);

    return this;

}

void SceneMain::Draw()
{
    SetDrawScreen(m_pCamera->GetWorldScreen());

    m_pMap->Draw();

    m_pWeaponManager->Draw();

    m_pPlayer->Draw();

    for (auto manager : m_enemyManagers) 
    {
        manager->Draw();
    }

    m_Item->Draw();

    //DrawBox(kBoxPos_X - 10, kBoxPos_Y + 25, kBoxPos_X + 10, kBoxPos_Y + 30, Color::kGreen, true);

    SetDrawScreen(DX_SCREEN_BACK);

    m_pCamera->Draw();

    m_pShowChoiceManager->Draw();

    DrawFade();

    if (m_pLotteryPassive->ShowSlot())
    {

        m_pLotteryPassive->Draw();

    }

    m_pEXPBar->Draw();

    m_pD_E_Counter->Draw();

    m_pTimer->Draw();

#ifdef _DEBUG

    printfDx("ここはメインシーンです\n");

    printfDx("Fキーでデスアップ\n");

    printfDx("\n");

    printfDx("Pキーでプレイヤーの攻撃フラグが立つ\n");

    printfDx("ボスが死んだかどうか : %s\n", m_bossDead ? "はい" : "いいえ");

    printfDx("プレイヤーが死んだかどうか : %s\n", m_playerDead ? "はい" : "いいえ");

#endif

}

void SceneMain::EnemyKnockBack()
{

    std::vector<EnemyBase*> allEnemies;

    for (auto manager : m_enemyManagers)
    {

        manager->GetEnemies(allEnemies);

    }

    for (int i = 0; i < allEnemies.size(); i++)
    {

        for (int j = i + 1; j < allEnemies.size(); j++)
        {

            if (m_pCollision->CheckRectCommon(allEnemies[i]->GetCheckRect(), allEnemies[j]->GetCheckRect()))
            {
                Vector2 posA = allEnemies[i]->GetPos();

                Vector2 posB = allEnemies[j]->GetPos();

                Vector2 diff = posA - posB;

                if (diff.GetSqLength() == 0.0f) continue;

                Vector2 dir = diff.GetNormalize();

                allEnemies[i]->AddPos(dir * 1.0f);

                allEnemies[j]->AddPos(-dir * 1.0f);

            }

        }

    }

}

void SceneMain::CharacterDead()
{

    if (m_pPlayer->Dead()) {

        StartFadeOut();

    }
    else if (m_pSkeletonMgr->CheckDead() && !m_skeletonDead) {

        m_pD_E_Counter->CountUP();

        m_bossDead = true;

        m_skeletonDead = true;

        StartFadeOut();

    }

    if (m_pBatMgr->CheckDead() && !m_batDead) {

        m_pD_E_Counter->CountUP();

        m_batDead = true;

    }

    if (m_pGoblinMgr->CheckDead() && !m_goblinDead) {

        m_pD_E_Counter->CountUP();

        m_goblinDead = true;

    }

    if (m_pMushroomMgr->CheckDead() && !m_mushroomDead) {

        m_pD_E_Counter->CountUP();

        m_mushroomDead = true;

    }

}
