#include "EnemyManagerYama.h"
#include "EnemyYama.h"

#include "../students/bamboojr36/Collision.h"
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
	m_mapPoint(0),
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

	// enemyTableの全要素にアクセス
	for (int i = 0; i < ENEMY_NUM_YAMA; i++) {

		// ポインタが指した先に何もなければスルー
		if (enemyTable[i] == nullptr) continue;

		enemyTable[i]->Update();

	}

}

void EnemyManagerYama::Draw()
{
	// enemyTableの全要素にアクセス
	for (int i = 0; i < ENEMY_NUM_YAMA; i++) {

		// ポインタが指した先に何もなければスルー
		if (enemyTable[i] == nullptr) continue;

		enemyTable[i]->Draw();

	}
}

void EnemyManagerYama::Resister()
{

	// 仮の生成↓
	/*
	Vector2 spawnPos;

	int side = rand() % 4;

	// まだ画面に登場していない敵を調べる
	for (int i = 0; i < ENEMY_NUM_YAMA; i++) {

		// ポインタが指した先に何もなければスルー
		if (enemyTable[i] == nullptr) continue;

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

		pEnemy->Init();
		pEnemy->SetGraphHandle();

		// 敵の座標を設定する
		// enemyTable[i]->SetParam();

		// 敵を生成したのでループを抜ける
		break;

	}
	*/

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
