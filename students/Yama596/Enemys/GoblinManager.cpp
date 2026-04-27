#include "GoblinManager.h"
#include "Goblin.h"
#include "../students/oreistake/Player.h"
#include "../students/bamboojr36/Collision.h"
#include "../students/oreistake/Camera.h"
#include "../students/Yama596/Enemys/Bat.h"
#include "../students/Yama596/Enemys/Mushroom.h"
#include "../students/Yama596/Enemys/Skeleton.h"

#include "../Utility/Game.h"

#include <DxLib.h>
#include <cassert>

namespace {

	const char* const kGoblinPath = "Resource\\Monsters Creatures Fantasy\\Sprites\\Goblin\\Run.png";

	const int kSize = 150;

}

GoblinManager::GoblinManager() :
	m_graphHandle{},
	m_pGoblin(nullptr),
	m_pPlayer(nullptr),
	m_pCollision(nullptr),
	m_pCamera(nullptr),
	m_pBat(nullptr),
	m_pMushroom(nullptr),
	m_pSkeleton(nullptr)
{

	m_goblins.fill(nullptr);

	m_pBat = new Bat();

	m_pGoblin = new Goblin();

	m_pMushroom = new Mushroom();

	m_pSkeleton = new Skeleton();

	m_pCollision = new Collision;

}

void GoblinManager::Init() {

	// グラフィックハンドルの初期化
	for (int i = 0; i < kGoblinMotionNum; i++) {

		m_graphHandle[i] = 0;

	}

	LoadDivGraph(kGoblinPath, 8, 8, 1, kSize, kSize, m_graphHandle);

	// enemyTableの初期化
	for (int i = 0; i < kMaxGoblinNum; i++) {

		m_goblins[i] = nullptr;

	}

	printfDx("ここ通った\n");

}

void GoblinManager::End() {

	for (int i = 0; i < kMaxGoblinNum; i++) {

		if (m_goblins[i] != nullptr) {

			m_goblins[i]->End();
			delete m_goblins[i];
			m_goblins[i] = nullptr;

		}

	}

	// グラフィックハンドルの破棄
	for (int i = 0; i < kGoblinMotionNum; i++) {

		DeleteGraph(m_graphHandle[i]);

	}

}

EnemyManagerBase* GoblinManager::Update() {

	for (int i = 0; i < kMaxGoblinNum; i++) {

		if (m_goblins[i] == nullptr) continue;

		m_goblins[i]->Update();

	}

	return this;

}

void GoblinManager::Draw() {

	for (int i = 0; i < kMaxGoblinNum; i++) {

		if (m_goblins[i] == nullptr) continue;

		m_goblins[i]->Draw();

	}

}

void GoblinManager::Spawn(const Vector2& pos)
{

	for (int i = 0; i < kMaxGoblinNum; i++)
	{

		if (m_goblins[i] != nullptr) continue;

		m_goblins[i] = new Goblin();

		m_goblins[i]->SetPlayer(m_pPlayer);

		m_goblins[i]->SetGraphHandle(m_graphHandle);

		m_goblins[i]->SetPos(pos);

		m_goblins[i]->Init();

		return;

	}

}

Vector2 GoblinManager::GetRandomSpawnPos()
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

void GoblinManager::CheckHitAttack(int damage) {

	for (int i = 0; i < kMaxGoblinNum; i++)
	{

		if (m_goblins[i] == nullptr) continue;

		if (m_goblins[i]->Dead()) continue;

		m_goblins[i]->Damege(damage);

	}

}

bool GoblinManager::CheckHitPlayer(const Rect& playerRect)
{

	for (int i = 0; i < kMaxGoblinNum; i++)
	{

		if (m_goblins[i] == nullptr) continue;

		if (m_goblins[i]->Dead()) continue;

		if (m_pCollision->CheckRectCommon(playerRect, m_goblins[i]->GetCheckRect()))
		{
			//コメント外すと当たった敵だけにダメージ
			//m_goblins[i]->Damege(100);

			return true;

		}

	}

	return false;

}

bool GoblinManager::CheckHitWeapon(const Rect& playerRect, int damage)
{

	for (int i = 0; i < kMaxGoblinNum; i++)
	{

		if (m_goblins[i] == nullptr) continue;

		if (m_goblins[i]->Dead()) continue;

		if (m_pCollision->CheckRectCommon(playerRect, m_goblins[i]->GetCheckRect()))
		{
			//コメント外すと当たった敵だけにダメージ
			m_goblins[i]->Damege(damage);

			return true;

		}

	}

	return false;

}

void GoblinManager::SetPlayer(PlayerMove* player)
{

	m_pPlayer = player;

	for (int i = 0; i < kMaxGoblinNum; i++)
	{

		if (m_goblins[i])
		{

			m_goblins[i]->SetPlayer(player);

		}

	}

}

EnemyBase* GoblinManager::CreateEnemy()
{

	return new Goblin;

}

void GoblinManager::GetEnemies(std::vector<EnemyBase*>& outEnemies)
{

	for (auto goblin : m_goblins)
	{

		if (goblin == nullptr) continue;

		//if (goblin->Dead()) continue;

		outEnemies.push_back(goblin);

	}

}

bool GoblinManager::CheckDead()
{

	for (int i = 0; i < kMaxGoblinNum; i++) {

		if (m_goblins[i] == nullptr) return false;

		if (m_goblins[i]->Dead()) {

			return true;

		}

		return false;

	}

}
