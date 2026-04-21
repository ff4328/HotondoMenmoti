#include "BatManager.h"

#include "../Utility/Game.h"

#include <DxLib.h>
#include <cassert>

namespace {

	const char* const kBatPath = "Resource\\Monsters Creatures Fantasy\\Sprites\\Flying eye\\Flight.png";

	const int kSize = 150;

}

BatManager::BatManager() :
	m_graphHandle{},
	m_pBat(nullptr)
{

	m_bats.fill(nullptr);

}

void BatManager::Init() {

	// グラフィックハンドルの初期化
	for (int i = 0; i < kMotionNum; i++) {

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
	for (int i = 0; i < kMotionNum; i++) {

		DeleteGraph(m_graphHandle[i]);

	}

}

void BatManager::Update() {

	for (int i = 0; i < kMaxBatNum; i++) {

		if (m_bats[i] == nullptr) continue;

		m_bats[i]->Update();

	}

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

		m_bats[i]->SetPos(pos);

		m_bats[i]->Init();

		return;

	}

}

Vector2 BatManager::GetRandomSpawnPos()
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
