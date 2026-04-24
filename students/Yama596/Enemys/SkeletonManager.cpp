#include "SkeletonManager.h"
#include "Skeleton.h"
#include "../students/oreistake/Player.h"
#include "../students/bamboojr36/Collision.h"
#include "../students/oreistake/Camera.h"
#include "../students/Yama596/Enemys/Bat.h"
#include "../students/Yama596/Enemys/Goblin.h"
#include "../students/Yama596/Enemys/Mushroom.h"

#include "../Utility/Game.h"

#include <DxLib.h>
#include <cassert>

namespace {

	const char* const kSkeletonPath = "Resource\\Monsters Creatures Fantasy\\Sprites\\Skeleton\\Walk.png";

	const int kSize = 150;

}

SkeletonManager::SkeletonManager() :
	m_graphHandle{},
	m_pSkeleton(nullptr),
	m_pPlayer(nullptr),
	m_pCollision(nullptr),
	m_pCamera(nullptr),
	m_pBat(nullptr),
	m_pGoblin(nullptr),
	m_pMushroom(nullptr)
{

	m_skeletons.fill(nullptr);

	m_pBat = new Bat();

	m_pGoblin = new Goblin();

	m_pMushroom = new Mushroom();

	m_pSkeleton = new Skeleton();

	m_pCollision = new Collision;

}

void SkeletonManager::Init() {

	// グラフィックハンドルの初期化
	for (int i = 0; i < kSkeletonMotionNum; i++) {

		m_graphHandle[i] = 0;

	}

	LoadDivGraph(kSkeletonPath, 4, 4, 1, kSize, kSize, m_graphHandle);

	// enemyTableの初期化
	for (int i = 0; i < kMaxSkeletonNum; i++) {

		m_skeletons[i] = nullptr;

	}

	printfDx("ここ通った\n");

}

void SkeletonManager::End() {

	for (int i = 0; i < kMaxSkeletonNum; i++) {

		if (m_skeletons[i] != nullptr) {

			m_skeletons[i]->End();
			delete m_skeletons[i];
			m_skeletons[i] = nullptr;

		}

	}

	// グラフィックハンドルの破棄
	for (int i = 0; i < kSkeletonMotionNum; i++) {

		DeleteGraph(m_graphHandle[i]);

	}

}

EnemyManagerBase* SkeletonManager::Update() {

	for (int i = 0; i < kMaxSkeletonNum; i++) {

		if (m_skeletons[i] == nullptr) continue;

		m_skeletons[i]->Update();

	}

	return this;

}

void SkeletonManager::Draw() {

	for (int i = 0; i < kMaxSkeletonNum; i++) {

		if (m_skeletons[i] == nullptr) continue;

		m_skeletons[i]->Draw();

	}

}

void SkeletonManager::Spawn(const Vector2& pos)
{

	for (int i = 0; i < kMaxSkeletonNum; i++)
	{

		if (m_skeletons[i] != nullptr) continue;

		m_skeletons[i] = new Skeleton();

		m_skeletons[i]->SetPlayer(m_pPlayer);

		m_skeletons[i]->SetGraphHandle(m_graphHandle);

		m_skeletons[i]->SetPos(pos);

		m_skeletons[i]->Init();

		return;

	}

}

Vector2 SkeletonManager::GetRandomSpawnPos()
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

void SkeletonManager::CheckHitAttack(int damage) {

	for (int i = 0; i < kMaxSkeletonNum; i++)
	{

		if (m_skeletons[i] == nullptr) continue;

		if (m_skeletons[i]->Dead()) continue;

		m_skeletons[i]->Damege(damage);

	}

}

bool SkeletonManager::CheckHitPlayer(const Rect& playerRect)
{

	for (int i = 0; i < kMaxSkeletonNum; i++)
	{

		if (m_skeletons[i] == nullptr) continue;

		if (m_skeletons[i]->Dead()) continue;

		if (m_pCollision->CheckRectCommon(playerRect, m_skeletons[i]->GetCheckRect()))
		{

			return true;

		}

	}

	return false;

}

void SkeletonManager::SetPlayer(PlayerMove* player)
{

	m_pPlayer = player;

	for (int i = 0; i < kMaxSkeletonNum; i++)
	{

		if (m_skeletons[i])
		{

			m_skeletons[i]->SetPlayer(player);

		}

	}

}

EnemyBase* SkeletonManager::CreateEnemy()
{

	return new Skeleton;

}

void SkeletonManager::GetEnemies(std::vector<EnemyBase*>& outEnemies)
{

	for (auto skeleton : m_skeletons)
	{

		if (skeleton == nullptr) continue;

		if (skeleton->Dead()) continue;

		outEnemies.push_back(skeleton);

	}

}

bool SkeletonManager::CheckSkeletonDead()
{

	for (int i = 0; i < kMaxSkeletonNum; i++) {

		if (m_skeletons[i] == nullptr) return false;

		if (m_skeletons[i]->Dead()) {

			return true;

		}

		return false;

	}

}
