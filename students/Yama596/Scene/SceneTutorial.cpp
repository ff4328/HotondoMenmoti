#include "SceneTutorial.h"
#include "SceneTitle.h"

#include "../students/oreistake/Player.h"
#include "../students/Yama596/Enemys/Bat.h"
#include "../students/Yama596/Enemys/BatManager.h"
#include "../students/FIREBAR/PlayerStatus.h"
#include "../students/mcd6752Tuyoshi/Map/Map.h"
#include "../students/bamboojr36/Collision.h"
#include "../students/oreistake/Camera.h"

#include "DxLib.h"

#include "../Utility/Color.h"
#include "../Utility/Game.h"
#include "../Utility/Input.h"

namespace {

    // 2秒
    const float kSpawnInterval = 120.0f;

}

SceneTutorial::SceneTutorial() :
    m_firstFrame(false),
    m_bossDead(false),
    m_playerDead(false),
    m_playerHit(false),
    m_playerInvincibleTime(0.0f),
    m_spawnTimer(0.0f),
    m_pPlayer(nullptr),
    m_pBatMgr(nullptr),
    m_pPlayerStatus(nullptr),
    m_pMap(nullptr),
    m_pCollision(nullptr),
    m_pCamera(nullptr)
{

    m_pPlayerStatus = new PlayerStatus();

    m_pPlayer = new PlayerMove(m_pPlayerStatus);

    m_pBatMgr = new BatManager();

    m_pMap = new Map();

    m_pCamera = new Camera();

}

void SceneTutorial::Init()
{

    m_pPlayer->Init();

    m_pBatMgr->Init();

    m_pBatMgr->SetPlayer(m_pPlayer);

    m_pBatMgr->Spawn(m_pBatMgr->GetRandomSpawnPos());

    m_pMap->Init();

    m_pCamera->Init(m_pPlayer, m_pMap);

}

void SceneTutorial::End()
{

    m_pPlayer->End();
    delete m_pPlayer;
    m_pPlayer = nullptr;

    m_pPlayerStatus->End();
    delete m_pPlayerStatus;
    m_pPlayerStatus = nullptr;

    m_pBatMgr->End();
    delete m_pBatMgr;
    m_pBatMgr = nullptr;

    m_pMap->End();
    delete m_pMap;
    m_pMap = nullptr;

    m_pCamera->End();
    delete m_pCamera;
    m_pCamera = nullptr;

}

SceneBase* SceneTutorial::Update()
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

        m_pBatMgr->CheckHitAttack(100);

    }
    
    // プレイヤーと敵が当たったらプレイヤーにダメージ
    if (!m_playerDead && m_pBatMgr->CheckHitPlayer(m_pPlayer->GetCheckRect()) &&!m_playerHit){

        m_pPlayer->Damage(100);

        // m_pPlayerStatus->SetCurrentHP(1);

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

        // 連続遷移防止
        prevSpace = true;

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

    // 状態更新
    prevSpace = nowSpace;
    prevF = nowF;
    prevG = nowG;
    m_spawnTimer++;

    if (m_spawnTimer >= kSpawnInterval)
    {

        m_spawnTimer = 0;

        m_pBatMgr->Spawn(m_pBatMgr->GetRandomSpawnPos());

    }

    m_pPlayer->Update(m_pPlayerStatus);

    m_pBatMgr->Update();

    m_pMap->Update();

    m_pCamera->Update();

    return this;

}

void SceneTutorial::Draw()
{

    SetDrawScreen(m_pCamera->GetWorldScreen());

    m_pMap->Draw();

    m_pPlayer->Draw();

    m_pBatMgr->Draw();

    SetDrawScreen(DX_SCREEN_BACK);

    m_pCamera->Draw();

    DrawFade();

#ifdef _DEBUG

    printfDx("ここはチュートリアルシーンです\n");

    printfDx("Player : %f %f\n", m_pPlayer->GetModelPos().x, m_pPlayer->GetModelPos().y);

    //printfDx("ESCキーでタイトルシーンに行く\n");

    //printfDx("Pause : %s\n", m_Pause ? "はい" : "いいえ");

#endif

}