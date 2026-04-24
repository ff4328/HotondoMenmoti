#include "BatManager.h"
#include "Bat.h"
#include "../students/oreistake/Player.h"
#include "../students/bamboojr36/Collision.h"
#include "../students/oreistake/Camera.h"
#include "../students/Yama596/Enemys/Goblin.h"
#include "../students/Yama596/Enemys/Mushroom.h"
#include "../students/Yama596/Enemys/Skeleton.h"

#include "../Utility/Game.h"

#include <DxLib.h>
#include <cassert>

namespace {

	const char* const kBatPath = "Resource\\Monsters Creatures Fantasy\\Sprites\\Flying eye\\Flight.png";

	const int kSize = 150;

}

BatManager::BatManager() :
	m_graphHandle{},
	m_pBat(nullptr),
	m_pPlayer(nullptr),
	m_pCollision(nullptr),
	m_pCamera(nullptr),
	m_pGoblin(nullptr),
	m_pMushroom(nullptr),
	m_pSkeleton(nullptr)
{

	m_bats.fill(nullptr);

	m_pBat = new Bat();

	m_pGoblin = new Goblin();

	m_pMushroom = new Mushroom();

	m_pSkeleton = new Skeleton();

	m_pCollision = new Collision;

}

void BatManager::Init() {

	// グラフィックハンドルの初期化
	for (int i = 0; i < kBatMotionNum; i++) {

		m_graphHandle[i] = 0;

	}

	LoadDivGraph(kBatPath, 8, 8, 1, kSize, kSize, m_graphHandle);

	// enemyTableの初期化
	for (int i = 0; i < kMaxBatNum; i++) {

		m_bats[i] = nullptr;

	}

}

void BatManager::End() {

	for (int i = 0; i < kMaxBatNum; i++) {

		if (m_bats[i] != nullptr) {

			m_bats[i]->End();
			delete m_bats[i];
			m_bats[i] = nullptr;

		}

	}

	// グラフィックハンドルの破棄
	for (int i = 0; i < kBatMotionNum; i++) {

		DeleteGraph(m_graphHandle[i]);

	}

}

EnemyManagerBase* BatManager::Update() {

	for (int i = 0; i < kMaxBatNum; i++) {

		if (m_bats[i] == nullptr) continue;

		m_bats[i]->Update();

	}

	return this;

}

void BatManager::Draw() {

	for (int i = 0; i < kMaxBatNum; i++) {

		if (m_bats[i] == nullptr) continue;

		m_bats[i]->Draw();

	}

}

void BatManager::Spawn(const Vector2& pos)
{

	for (int i = 0; i < kMaxBatNum; i++)
	{

		if (m_bats[i] != nullptr) continue;

		m_bats[i] = new Bat();

		m_bats[i]->SetPlayer(m_pPlayer);

		m_bats[i]->SetGraphHandle(m_graphHandle);

		m_bats[i]->SetPos(pos);

		m_bats[i]->Init();

		return;

	}

}

Vector2 BatManager::GetRandomSpawnPos()
{

	const int margin = 50;

	float left = m_pCamera->GetLeft();

	float right = m_pCamera->GetRight();

	float top = m_pCamera->GetTop();

	float bottom = m_pCamera->GetBottom();

	int side = GetRand(3);

	Vector2 spawnPos;

	switch (side)
	{
	case 0:
		spawnPos.x = GetRand((int)(right - left)) + left;
		spawnPos.y = top - margin;
		break;

	case 1:
		spawnPos.x = GetRand((int)(right - left)) + left;
		spawnPos.y = bottom + margin;
		break;

	case 2:
		spawnPos.x = left - margin;
		spawnPos.y = GetRand((int)(bottom - top)) + top;
		break;

	case 3:
		spawnPos.x = right + margin;
		spawnPos.y = GetRand((int)(bottom - top)) + top;
		break;
	}

	return spawnPos;

}

void BatManager::CheckHitAttack(int damage) {

	for (int i = 0; i < kMaxBatNum; i++)
	{

		if (m_bats[i] == nullptr) continue;

		if (m_bats[i]->Dead()) continue;

		m_bats[i]->Damege(damage);

	}

}

bool BatManager::CheckHitPlayer(const Rect& playerRect)
{

	for (int i = 0; i < kMaxBatNum; i++)
	{

		if (m_bats[i] == nullptr) continue;

		if (m_bats[i]->Dead()) continue;

		if (m_pCollision->CheckRectCommon(playerRect, m_bats[i]->GetCheckRect()))
		{

			return true;

		}

	}

	return false;
}

void BatManager::SetPlayer(PlayerMove* player)
{

	m_pPlayer = player;

	for (int i = 0; i < kMaxBatNum; i++)
	{

		if (m_bats[i])
		{

			m_bats[i]->SetPlayer(player);

		}

	}

}

EnemyBase* BatManager::CreateEnemy()
{

	return new Bat;

}

void BatManager::GetEnemies(std::vector<EnemyBase*>& outEnemies)
{

	for (auto bat : m_bats)
	{

		if (bat == nullptr) continue;

		if (bat->Dead()) continue;

		outEnemies.push_back(bat);

	}

}

bool BatManager::CheckDead()
{

	for (int i = 0; i < kMaxBatNum; i++) {

		if (m_bats[i] == nullptr) return false;

		if (m_bats[i]->Dead()) {

			return true;

		}

		return false;

	}

}
