#include "SkeletonManager.h"
#include "Skeleton.h"
#include "../students/oreistake/Player.h"
#include "../students/bamboojr36/Collision.h"

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
	m_pCollision(nullptr)
{

	m_skeletons.fill(nullptr);

	m_pCollision = new Collision;

}

void SkeletonManager::Init() {

	// グラフィックハンドルの初期化
	for (int i = 0; i < kMotionNum; i++) {

		m_graphHandle[i] = 0;

	}

	LoadDivGraph(kSkeletonPath, 8, 8, 1, kSize, kSize, m_graphHandle);

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
	for (int i = 0; i < kMotionNum; i++) {

		DeleteGraph(m_graphHandle[i]);

	}

}

void SkeletonManager::Update() {

	for (int i = 0; i < kMaxSkeletonNum; i++) {

		if (m_skeletons[i] == nullptr) continue;

		m_skeletons[i]->Update();

	}

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

	int side = GetRand(3);

	Vector2 spawnPos;

	switch (side)
	{
	case 0:
		spawnPos.x = GetRand(Game::kScreenWidth);
		spawnPos.y = -margin;
		break;

	case 1:
		spawnPos.x = GetRand(Game::kScreenWidth);
		spawnPos.y = Game::kScreenHeight + margin;
		break;

	case 2:
		spawnPos.x = -margin;
		spawnPos.y = GetRand(Game::kScreenHeight);
		break;

	case 3:
		spawnPos.x = Game::kScreenWidth + margin;
		spawnPos.y = GetRand(Game::kScreenHeight);
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