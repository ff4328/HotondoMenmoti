#include "MiniMushroomManager.h"
#include "MiniMushroom.h"
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

	const char* const kMushroomDeadPath = "Resource\\Monsters Creatures Fantasy\\Sprites\\Mushroom\\Death.png";

	const int kSize = 150;

}

MiniMushroomManager::MiniMushroomManager() :
	m_graphHandle{},
	m_pMiniMushroom(nullptr),
	m_pPlayer(nullptr),
	m_pCollision(nullptr),
	m_pCamera(nullptr)
{

	m_miniMushrooms.fill(nullptr);

	m_pMiniMushroom = new MiniMushroom();

	m_pCollision = new Collision;

}

void MiniMushroomManager::Init()
{

	// グラフィックハンドルの初期化
	for (int i = 0; i < kMiniMushroomMotionNum; i++) {

		for (int j = 0; j < kStatusMiniMushroomNum; j++) {

			m_graphHandle[i][j] = 0;

		}

	}

	LoadDivGraph(kMushroomPath, 8, 8, 1, kSize, kSize, m_graphHandle[STATUS_RUN]);

	LoadDivGraph(kMushroomDeadPath, 4, 4, 1, kSize, kSize, m_graphHandle[STATUS_DEAD]);

	// enemyTableの初期化
	for (int i = 0; i < kMaxMiniMushroomNum; i++) {

		m_miniMushrooms[i] = nullptr;

	}

}

void MiniMushroomManager::End()
{

	for (int i = 0; i < kMaxMiniMushroomNum; i++) {

		if (m_miniMushrooms[i] != nullptr) {

			m_miniMushrooms[i]->End();
			delete m_miniMushrooms[i];
			m_miniMushrooms[i] = nullptr;

		}

	}

	// グラフィックハンドルの破棄
	for (int i = 0; i < kMiniMushroomMotionNum; i++) {

		for (int j = 0; j < kStatusMiniMushroomNum; j++) {

			DeleteGraph(m_graphHandle[i][j]);

		}

	}

	delete m_pCollision;
	m_pCollision = nullptr;

}

EnemyManagerBase* MiniMushroomManager::Update()
{

	for (int i = 0; i < kMaxMiniMushroomNum; i++) {

		if (m_miniMushrooms[i] == nullptr) continue;

		m_miniMushrooms[i]->Update();

	}

	CheckDead();

	return this;

}

void MiniMushroomManager::Draw()
{

	for (int i = 0; i < kMaxMiniMushroomNum; i++) {

		if (m_miniMushrooms[i] == nullptr) continue;

		m_miniMushrooms[i]->Draw();

	}

}

void MiniMushroomManager::Spawn(const Vector2& pos)
{

	for (int i = 0; i < kMaxMiniMushroomNum; i++)
	{

		if (m_miniMushrooms[i] != nullptr) continue;

		m_miniMushrooms[i] = new MiniMushroom();

		m_miniMushrooms[i]->SetPlayer(m_pPlayer);

		m_miniMushrooms[i]->SetRunGraphHandle(m_graphHandle[STATUS_RUN]);

		m_miniMushrooms[i]->SetDeadGraphHandle(m_graphHandle[STATUS_DEAD]);

		m_miniMushrooms[i]->SetPos(pos);

		m_miniMushrooms[i]->Init();

		return;

	}

}

Vector2 MiniMushroomManager::GetRandomSpawnPos()
{

	// カメラの端から50のランダムな位置に敵を出現させる
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

void MiniMushroomManager::CheckHitAttack(int damage) {

	for (int i = 0; i < kMaxMiniMushroomNum; i++)
	{

		if (m_miniMushrooms[i] == nullptr) continue;

		if (m_miniMushrooms[i]->Dead()) continue;

		m_miniMushrooms[i]->Damege(damage);

	}

}

bool MiniMushroomManager::CheckHitPlayer(const Rect& playerRect)
{

	for (int i = 0; i < kMaxMiniMushroomNum; i++)
	{

		if (m_miniMushrooms[i] == nullptr) continue;

		if (m_miniMushrooms[i]->Dead()) continue;

		if (m_pCollision->CheckRectCommon(playerRect, m_miniMushrooms[i]->GetCheckRect()))
		{
			//コメント外すと当たった敵だけにダメージ
			//m_miniMushrooms[i]->Damege(100);

			return true;

		}

	}

	return false;

}

bool MiniMushroomManager::CheckHitWeapon(const Rect& playerRect, int damage)
{

	for (int i = 0; i < kMaxMiniMushroomNum; i++)
	{

		if (m_miniMushrooms[i] == nullptr) continue;

		if (m_miniMushrooms[i]->Dead()) continue;

		if (m_pCollision->CheckRectCommon(playerRect, m_miniMushrooms[i]->GetCheckRect()))
		{
			//コメント外すと当たった敵だけにダメージ
			m_miniMushrooms[i]->Damege(damage);

			return true;

		}

	}

	return false;

}

bool MiniMushroomManager::CheckHitWeapon(
	const std::vector<Rect>& rects,
	int damage)
{
	for (const auto& rect : rects)
	{
		if (CheckHitWeapon(rect, damage))
		{
			return true;
		}
	}

	return false;
}

void MiniMushroomManager::SetPlayer(PlayerMove* player)
{

	m_pPlayer = player;

	for (int i = 0; i < kMaxMiniMushroomNum; i++)
	{

		if (m_miniMushrooms[i])
		{

			m_miniMushrooms[i]->SetPlayer(player);

		}

	}

}

EnemyBase* MiniMushroomManager::CreateEnemy()
{

	return new MiniMushroom;

}

void MiniMushroomManager::GetEnemies(std::vector<EnemyBase*>& outEnemies)
{

	for (auto mushroom : m_miniMushrooms)
	{

		if (mushroom == nullptr) continue;

		//if (mushroom->Dead()) continue;

		outEnemies.push_back(mushroom);

	}

}

bool MiniMushroomManager::CheckDead()
{

	for (int i = 0; i < kMaxMiniMushroomNum; i++) {

		if (m_miniMushrooms[i] == nullptr) continue;

		if (m_miniMushrooms[i]->DeadEnd()) {

			delete m_miniMushrooms[i];
			m_miniMushrooms[i] = nullptr;

			return true;

		}

	}

	return false;

}
