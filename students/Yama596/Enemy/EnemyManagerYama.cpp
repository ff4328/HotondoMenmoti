#include "EnemyManagerYama.h"
#include "EnemyYama.h"

#include "../students/bamboojr36/Collision.h"
#include "../students/FIREBAR/EnemyStatus.h"
#include "../Utility/Game.h"

#include<DxLib.h>

namespace {

	const char* const kBatPath = "Resource\\Monsters Creatures Fantasy\\Sprites\\Flying eye\\Flight.png";

	const char* const kGoblinPath = "Resource\\Monsters Creatures Fantasy\\Sprites\\Goblin\\Run.png";

	const char* const kSkeletonPath = "Resource\\Monsters Creatures Fantasy\\Sprites\\Skeleton\\Walk.png";

	const char* const kMushPath = "Resource\\Monsters Creatures Fantasy\\Sprites\\Mushroom\\Run.png";

	const int kEnemySize = 150;

	const int kBossSize = 200;

}

EnemyManagerYama::EnemyManagerYama():
	m_graphHandle{},
	m_gameCount(0),
	m_batCount(0),
	m_goblinCount(0),
	m_skeletonCount(0),
	m_mushCount(0),
	m_mapPoint(0),
	m_pPlayer(nullptr),
	m_pMap(nullptr)
{

	for (int i = 0; i < ENEMY_NUM_YAMA; i++) {

		enemyTable[i] = nullptr;

	}

}

void EnemyManagerYama::Init()
{

	// グラフィックハンドルの初期化
	for (int i = 0; i < ENEMY_TYPE_MAX_YAMA; i++) {

		for (int j = 0; j < ENEMY_MOTION_NUM_YAMA; j++) {

			m_graphHandle[i][j] = 0;

		}

	}

	m_enemyStatus.SetEnemyStatus();

}

void EnemyManagerYama::End()
{

	for (int i = 0; i < ENEMY_NUM_YAMA; i++) {

		if (enemyTable[i] != nullptr) {

			enemyTable[i]->End();
			delete enemyTable[i];
			enemyTable[i] = nullptr;

		}

	}

}

void EnemyManagerYama::Update()
{

	m_gameCount++;
	
	for (int i = 0; i < ENEMY_NUM_YAMA; i++) {

		
		if (enemyTable[i] != nullptr) continue;

		enemyTable[i]->Update();

	}

	m_gameCount++;

	if (m_gameCount % 60 == 0) {

		Resister(m_pPlayer);

	}

	// enemyTableの全要素にアクセス
	for (int i = 0; i < ENEMY_NUM_YAMA; i++) {

		// ポインタが指した先に何かあればスルー
		if (enemyTable[i] != nullptr) continue;

		enemyTable[i]->Update();

		if (enemyTable[i]->Dead()) {

			enemyTable[i]->End();
			delete enemyTable[i];
			enemyTable[i] = nullptr;

		}

	}

}

void EnemyManagerYama::Draw()
{
	// enemyTableの全要素にアクセス
	for (int i = 0; i < ENEMY_NUM_YAMA; i++) {

		// ポインタが指した先に何かあればスルー
		if (enemyTable[i] != nullptr) continue;

		enemyTable[i]->Draw();

	}
}

bool EnemyManagerYama::Resister(PlayerMove* pPlayer)
{

	Vector2 spawnPos;

	int side = rand() % 4;

	// まだ画面に登場していない敵を調べる
	for (int i = 0; i < ENEMY_NUM_YAMA; i++) {

		// ポインタが指した先に何かあればスルー
		if (enemyTable[i] != nullptr) continue;

		switch (side)
		{

		case 0:
			spawnPos.x = rand() % Game::kScreenWidth;
			spawnPos.y = -50;
			break;

		case 1:
			spawnPos.x = rand() % Game::kScreenWidth;
			spawnPos.y = Game::kScreenHeight + 50;
			break;

		case 2:
			spawnPos.x = -50;
			spawnPos.y = rand() % Game::kScreenHeight;
			break;

		case 3:
			spawnPos.x = Game::kScreenWidth + 50;
			spawnPos.y = rand() % Game::kScreenHeight;
			break;
		}

		EnemyYama* pEnemy = new EnemyYama();

		pEnemy->SetEnemyType(GetSpawnType());
		pEnemy->SetEnemyStatus(&m_enemyStatus);
		pEnemy->Init();

		pEnemy->SetGraphHandle(m_graphHandle);
		pEnemy->SetPos(spawnPos);
		pEnemy->SetPlayer(pPlayer);

		enemyTable[i] = pEnemy;

		return true;

	}
	
	return false;

}

void EnemyManagerYama::ResisterMapPoint()
{
}

void EnemyManagerYama::InitAnimation()
{

	LoadDivGraph(kBatPath,
		8, 8, 1, kEnemySize, kEnemySize,
		m_graphHandle[ENEMY_TYPE_BAT_YAMA]);

	LoadDivGraph(kGoblinPath,
		8, 8, 1, kEnemySize, kEnemySize,
		m_graphHandle[ENEMY_TYPE_GOBLIN_YAMA]);

	LoadDivGraph(kSkeletonPath,
		4, 4, 1, kBossSize, kBossSize,
		m_graphHandle[ENEMY_TYPE_SKELETON_YAMA]);

	LoadDivGraph(kMushPath,
		8, 8, 1, kEnemySize, kEnemySize,
		m_graphHandle[ENEMY_TYPE_MUSH_YAMA]);

}

void EnemyManagerYama::CheckHitToRect(Rect rect)
{
}

EnemyTypeYama EnemyManagerYama::GetSpawnType()
{

	int timeSec = m_gameCount / 60;

	if (timeSec < 5) {

		return ENEMY_TYPE_BAT_YAMA;

	}
	else if (timeSec < 10) {

		return (rand() % 2 == 0) ? ENEMY_TYPE_BAT_YAMA : ENEMY_TYPE_MUSH_YAMA;

	}
	else if (timeSec < 20) {

		int r = rand() % 3;

		if (r == 0) return ENEMY_TYPE_BAT_YAMA;

		if (r == 1) return ENEMY_TYPE_MUSH_YAMA;

		return ENEMY_TYPE_GOBLIN_YAMA;

	}
	else {

		int r = rand() % 4;

		return (EnemyTypeYama)(r);

	}
}

