#include "GoblinManager.h"
#include "Goblin.h"
#include "../students/oreistake/Player.h"
#include "../students/bamboojr36/Collision.h"

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
	m_pCollision(nullptr)
{

	m_goblins.fill(nullptr);

	m_pCollision = new Collision;

}

void GoblinManager::Init() {

	// グラフィックハンドルの初期化
	for (int i = 0; i < kMotionNum; i++) {

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
	for (int i = 0; i < kMotionNum; i++) {

		DeleteGraph(m_graphHandle[i]);

	}

}

void GoblinManager::Update() {

	for (int i = 0; i < kMaxGoblinNum; i++) {

		if (m_goblins[i] == nullptr) continue;

		m_goblins[i]->Update();

	}

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
