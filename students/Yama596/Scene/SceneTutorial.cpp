#include "SceneTutorial.h"
#include "SceneTitle.h"

#include "../students/oreistake/Player.h"
#include "../students/Yama596/Enemys/BatManager.h"
#include "../students/Yama596/Enemys/GoblinManager.h"
#include "../students/Yama596/Enemys/MushroomManager.h"
#include "../students/Yama596/Enemys/SkeletonManager.h"
#include "../students/FIREBAR/PlayerStatus.h"
#include "../students/mcd6752Tuyoshi/Map/Map.h"
#include "../students/bamboojr36/Collision.h"
#include "../students/oreistake/Camera.h"

#include "DxLib.h"

#include "../Utility/Color.h"
#include "../Utility/Game.h"
#include "../Utility/Input.h"

namespace {

    // 3秒
    const int kSpawnInterval = 180;

    // ゴブリンタイマー
    const int kGoblinTimer = 600;

    // マッシュルームタイマー
    const int kMushroomTimer = 1200;

    // スケルトンタイマー
    const int kSkeletonTimer = 1800;

}

SceneTutorial::SceneTutorial() :
    m_firstFrame(false),
    m_bossDead(false),
    m_playerDead(false),
    m_playerHit(false),
    m_playerInvincibleTime(0.0f),
    m_spawnTimer(0),
    m_gameCount(0),
    m_spawnGoblin(false),
    m_spawnMushroom(false),
    m_spawnSkeleton(false),
    m_pPlayer(nullptr),
    m_pBatMgr(nullptr),
    m_pGoblinMgr(nullptr),
    m_pMushroomMgr(nullptr),
    m_pSkeletonMgr(nullptr),
    m_pPlayerStatus(nullptr),
    m_pMap(nullptr),
    m_pCollision(nullptr),
    m_pCamera(nullptr)
{

    m_pPlayerStatus = new PlayerStatus();

    m_pPlayer = new PlayerMove(m_pPlayerStatus);

    m_pBatMgr = new BatManager();

    m_pGoblinMgr = new GoblinManager();

    m_pMushroomMgr = new MushroomManager();

    m_pSkeletonMgr = new SkeletonManager();

    m_pMap = new Map();

    m_pCollision = new Collision();

    m_pCamera = new Camera();

}

void SceneTutorial::Init()
{

    m_pPlayer->Init();

    m_enemyManagers.push_back(m_pBatMgr);

    m_enemyManagers.push_back(m_pGoblinMgr);

    m_enemyManagers.push_back(m_pMushroomMgr);

    m_enemyManagers.push_back(m_pSkeletonMgr);

    for (auto manager : m_enemyManagers) {

        manager->SetPlayer(m_pPlayer);

        manager->SetCamera(m_pCamera);

        manager->Init();

    }

    /*
    //m_pBatMgr->Init();

    //m_pBatMgr->SetPlayer(m_pPlayer);

    //m_pBatMgr->SetCamera(m_pCamera);

    //m_pGoblinMgr->Init();

    //m_pGoblinMgr->SetPlayer(m_pPlayer);

    //m_pGoblinMgr->SetCamera(m_pCamera);

    //m_pMushroomMgr->Init();

    //m_pMushroomMgr->SetPlayer(m_pPlayer);

    //m_pMushroomMgr->SetCamera(m_pCamera);

    //m_pSkeletonMgr->Init();

    //m_pSkeletonMgr->SetPlayer(m_pPlayer);

    //m_pSkeletonMgr->SetCamera(m_pCamera);
    */

    m_pMap->Init();

    m_pCamera->Init(m_pPlayer, m_pMap);

    m_pPlayer->SetMap(m_pMap);

}

void SceneTutorial::End()
{

    m_pPlayer->End();
    delete m_pPlayer;
    m_pPlayer = nullptr;

    m_pPlayerStatus->End();
    delete m_pPlayerStatus;
    m_pPlayerStatus = nullptr;

    for (auto manager : m_enemyManagers) {

        manager->End();

    }

    /*
    //m_pBatMgr->End();
    //delete m_pBatMgr;
    //m_pBatMgr = nullptr;

    //m_pGoblinMgr->End();
    //delete m_pGoblinMgr;
    //m_pGoblinMgr = nullptr;

    //m_pMushroomMgr->End();
    //delete m_pMushroomMgr;
    //m_pMushroomMgr = nullptr;

    //m_pSkeletonMgr->End();
    //delete m_pSkeletonMgr;
    //m_pSkeletonMgr = nullptr;
    */

    m_pMap->End();
    delete m_pMap;
    m_pMap = nullptr;

    m_pCamera->End();
    delete m_pCamera;
    m_pCamera = nullptr;

}

SceneBase* SceneTutorial::Update()
{

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
        &&! m_playerHit && !m_playerDead){

        m_pPlayer->Damage(1);

        m_playerHit = true;

    }

    if (m_playerHit){

        m_playerInvincibleTime++;

        if (m_playerInvincibleTime >= 25.0f)
        {

            m_playerHit = false;

            m_playerInvincibleTime = 0;

        }

    }

    if (m_pPlayer->Dead()) {

        StartFadeOut();

    }
    else if (m_pSkeletonMgr->CheckSkeletonDead()) {

        m_bossDead = true;

        StartFadeOut();

    }

    // ↓ボスが死んだらシーン遷移する処理を書く
    /*
    else if (m_pBat->Dead()) {

        // 連続遷移防止
        prevSpace = true;

        // 死亡している
        m_bossDead = true;

        StartFadeOut();

    }
    */

    UpdateFade();

    if (IsFadeOutEnd()) {

        if (m_bossDead) {

            // シーン遷移
            return new SceneTitle;

        }
        else if (!m_bossDead) {

            // シーン遷移
            return new SceneTitle;

        }

    }

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

    /*
    //m_pBatMgr->Update();

    //m_pGoblinMgr->Update();

    //m_pMushroomMgr->Update();

    //m_pSkeletonMgr->Update();
    */

    m_pMap->Update();

    m_pCamera->Update();

    return this;

}

void SceneTutorial::Draw()
{

    SetDrawScreen(m_pCamera->GetWorldScreen());

    m_pMap->Draw();

    m_pPlayer->Draw();

    for (auto manager : m_enemyManagers) {

        manager->Draw();

    }

    /*
    //m_pBatMgr->Draw();

    //m_pGoblinMgr->Draw();

    //m_pMushroomMgr->Draw();

    //m_pSkeletonMgr->Draw();
    */

    SetDrawScreen(DX_SCREEN_BACK);

    m_pCamera->Draw();

    DrawFade();

#ifdef _DEBUG

    printfDx("ここはチュートリアルシーンです\n");

    printfDx("Player : %f %f\n", m_pPlayer->GetModelPos().x, m_pPlayer->GetModelPos().y);

    printfDx("m_spawnTimer : %d\n", m_spawnTimer);

#endif

}

void SceneTutorial::EnemyKnockBack()
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

            if (m_pCollision->CheckRectCommon(allEnemies[i]->GetCheckRect(),allEnemies[j]->GetCheckRect()))
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
