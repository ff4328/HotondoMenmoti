#include "MushroomManager.h"
#include "Mushroom.h"
#include "../students/oreistake/Player.h"
#include "../students/bamboojr36/Collision.h"
#include "../students/oreistake/Camera.h"
#include "../students/Yama596/Enemys/Bat.h"
#include "../students/Yama596/Enemys/Goblin.h"
#include "../students/Yama596/Enemys/Skeleton.h"

#include "../Utility/Game.h"

#include <DxLib.h>
#include <cassert>

namespace {

	const char* const kMushroomPath = "Resource\\Monsters Creatures Fantasy\\Sprites\\Mushroom\\Run.png";

	const int kSize = 150;

}

MushroomManager::MushroomManager() :
	m_graphHandle{},
	m_pMushroom(nullptr),
	m_pPlayer(nullptr),
	m_pCollision(nullptr),
	m_pCamera(nullptr),
	m_pBat(nullptr),
	m_pGoblin(nullptr),
	m_pSkeleton(nullptr)
{

	m_mushrooms.fill(nullptr);

	m_pBat = new Bat();

	m_pGoblin = new Goblin();

	m_pMushroom = new Mushroom();

	m_pSkeleton = new Skeleton();

	m_pCollision = new Collision;

}

void MushroomManager::Init() {

	// グラフィックハンドルの初期化
	for (int i = 0; i < kMushroomMotionNum; i++) {

		m_graphHandle[i] = 0;

	}

	LoadDivGraph(kMushroomPath, 8, 8, 1, kSize, kSize, m_graphHandle);

	// enemyTableの初期化
	for (int i = 0; i < kMaxMushroomNum; i++) {

		m_mushrooms[i] = nullptr;

	}

	printfDx("ここ通った\n");

}

void MushroomManager::End() {

	for (int i = 0; i < kMaxMushroomNum; i++) {

		if (m_mushrooms[i] != nullptr) {

			m_mushrooms[i]->End();
			delete m_mushrooms[i];
			m_mushrooms[i] = nullptr;

		}

	}

	// グラフィックハンドルの破棄
	for (int i = 0; i < kMushroomMotionNum; i++) {

		DeleteGraph(m_graphHandle[i]);

	}

}

EnemyManagerBase* MushroomManager::Update() {

	for (int i = 0; i < kMaxMushroomNum; i++) {

		if (m_mushrooms[i] == nullptr) continue;

		m_mushrooms[i]->Update();

	}

	return this;

}

void MushroomManager::Draw() {

	for (int i = 0; i < kMaxMushroomNum; i++) {

		if (m_mushrooms[i] == nullptr) continue;

		m_mushrooms[i]->Draw();

	}

}

void MushroomManager::Spawn(const Vector2& pos)
{

	for (int i = 0; i < kMaxMushroomNum; i++)
	{

		if (m_mushrooms[i] != nullptr) continue;

		m_mushrooms[i] = new Mushroom();

		m_mushrooms[i]->SetPlayer(m_pPlayer);

		m_mushrooms[i]->SetGraphHandle(m_graphHandle);

		m_mushrooms[i]->SetPos(pos);

		m_mushrooms[i]->Init();

		return;

	}

}

Vector2 MushroomManager::GetRandomSpawnPos()
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

void MushroomManager::CheckHitAttack(int damage) {

	for (int i = 0; i < kMaxMushroomNum; i++)
	{

		if (m_mushrooms[i] == nullptr) continue;

		if (m_mushrooms[i]->Dead()) continue;

		m_mushrooms[i]->Damege(damage);

	}

}

bool MushroomManager::CheckHitPlayer(const Rect& playerRect)
{

	for (int i = 0; i < kMaxMushroomNum; i++)
	{

		if (m_mushrooms[i] == nullptr) continue;

		if (m_mushrooms[i]->Dead()) continue;

		if (m_pCollision->CheckRectCommon(playerRect, m_mushrooms[i]->GetCheckRect()))
		{

			return true;

		}

	}

	return false;

}

void MushroomManager::SetPlayer(PlayerMove* player)
{

	m_pPlayer = player;

	for (int i = 0; i < kMaxMushroomNum; i++)
	{

		if (m_mushrooms[i])
		{

			m_mushrooms[i]->SetPlayer(player);

		}

	}

}

EnemyBase* MushroomManager::CreateEnemy()
{

	return new Mushroom;

}

void MushroomManager::GetEnemies(std::vector<EnemyBase*>& outEnemies)
{

	for (auto mushroom : m_mushrooms)
	{

		if (mushroom == nullptr) continue;

		if (mushroom->Dead()) continue;

		outEnemies.push_back(mushroom);

	}

}

bool MushroomManager::CheckDead()
{

	for (int i = 0; i < kMaxMushroomNum; i++) {

		if (m_mushrooms[i] == nullptr) return false;

		if (m_mushrooms[i]->Dead()) {

			return true;

		}

		return false;

	}

}
