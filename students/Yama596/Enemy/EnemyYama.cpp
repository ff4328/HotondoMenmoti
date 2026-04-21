#include<DxLib.h>
#include<math.h>
#include "../students/Yama596/Enemy/EnemyYama.h"
#include "../students/oreistake/Player.h"
#include "../students/FIREBAR/EnemyStatus.h"

namespace {

	const char* const kBatPath = "Resource\\Monsters Creatures Fantasy\\Sprites\\Flying eye\\Flight.png";

	const char* const kGoblinPath = "Resource\\Monsters Creatures Fantasy\\Sprites\\Goblin\\Run.png";

	const char* const kSkeletonPath = "Resource\\Monsters Creatures Fantasy\\Sprites\\Skeleton\\Walk.png";

	const char* const kMushPath = "Resource\\Monsters Creatures Fantasy\\Sprites\\Mushroom\\Run.png";

	const int kBatHitPoint = 10;

	const int kGoblinHitPoint = 10;

	const int kSkeletonHitPoint = 10;

	const int kMushHitPoint = 10;

};

EnemyYama::EnemyYama() :
	m_graphHandle{},
	m_enemySpeed(1.0f),
	m_currentPos(Vector2()),
	m_batCurrentPos(Vector2(300.0f, 200.0f)),
	m_goblinCurrentPos(Vector2(400.0f, 100.0f)),
	m_skeletonCurrentPos(Vector2(400.0f, 200.0f)),
	m_mushCurrentPos(Vector2(500.0f, 200.0f)),
	m_moveDir(Vector2()),
	m_batMoveDir(Vector2()),
	m_goblinMoveDir(Vector2()),
	m_skeletonMoveDir(Vector2()),
	m_mushMoveDir(Vector2()),
	m_motionCounter(0),
	m_motionFrame(0),
	m_sizeX(150),
	m_sizeY(150),
	m_hp(0.0f),
	m_maxHp(0.0f),
	m_attack(0.0f),
	m_speed(0.0f),
	m_enmeyType(EnemyTypeYama::ENEMY_TYPE_BAT_YAMA),
	m_pPlayer(nullptr),
	m_pEnemyStatus(nullptr),
	m_pHp(nullptr),
	m_pMap(nullptr)
{

}

EnemyYama::EnemyYama(EnemyStatus* enemystatus):
	m_graphHandle{},
	m_enemySpeed(1.0f),
	m_batCurrentPos(Vector2(300.0f, 200.0f)),
	m_goblinCurrentPos(Vector2(400.0f, 100.0f)),
	m_skeletonCurrentPos(Vector2(400.0f, 200.0f)),
	m_mushCurrentPos(Vector2(500.0f, 200.0f)),
	m_batMoveDir(Vector2()),
	m_goblinMoveDir(Vector2()),
	m_skeletonMoveDir(Vector2()),
	m_mushMoveDir(Vector2()),
	m_motionCounter(0),
	m_motionFrame(0),
	m_sizeX(150),
	m_sizeY(150),
	m_hp(0.0f),
	m_maxHp(0.0f),
	m_attack(0.0f),
	m_speed(0.0f),
	m_enmeyType(EnemyTypeYama::ENEMY_TYPE_BAT_YAMA),
	m_pPlayer(nullptr),
	m_pHp(nullptr)
{

	m_pEnemyStatus = enemystatus;

}

void EnemyYama::Init()
{

	// グラフィックハンドルの初期化
	for (int i = 0; i < ENEMY_TYPE_MAX_YAMA; i++) {

		for (int j = 0; j < ENEMY_MOTION_NUM_YAMA; j++) {

			m_graphHandle[i][j] = 0;

		}

	}

	InitAnimation();

	InitStatus();

}



void EnemyYama::End()
{

	// グラフィックハンドルの破棄
	for (int i = 0; i < ENEMY_TYPE_MAX_YAMA; i++) {

		for (int j = 0; j < ENEMY_MOTION_NUM_YAMA; j++) {

			DeleteGraph(m_graphHandle[i][j]);

		}

	}

}

void EnemyYama::Update()
{

	// if (Dead()) return;

	UpdateMove();

}

void EnemyYama::Draw()
{

	// if (Dead()) return;

	// モーション制御用のカウンタをカウントアップ
	m_motionCounter++;

	// アニメーションのフレームを1コマ進める
	if (m_motionCounter % 20 == 0) {

		m_motionCounter = 0;

		// 敵のアニメーションは全部で4コマ想定なので
		m_motionFrame++;
		m_motionFrame = m_motionFrame % 4;

	}

	DrawEnemy();

}

void EnemyYama::Damege(int value)
{

	m_hp -= value;

	if (m_hp < 0) {

		m_hp = 0;

	}

}

bool EnemyYama::Dead()
{

	return m_hp <= 0;

}

Rect EnemyYama::GetCheckRectBat()
{

	Rect myRect = {

		(m_batCurrentPos.x - 15),
		(m_batCurrentPos.y - 30),
		(m_batCurrentPos.x + 15),
		(m_batCurrentPos.y + 30),

	};

	return myRect;

}

Rect EnemyYama::GetCheckRectGoblin()
{

	Rect myRect = {

		(m_goblinCurrentPos.x - 15),
		(m_goblinCurrentPos.y - 30),
		(m_goblinCurrentPos.x + 15),
		(m_goblinCurrentPos.y + 30),

	};

	return myRect;

}

Rect EnemyYama::GetCheckRectSkeleton() {

	Rect myRect = {

		(m_skeletonCurrentPos.x - 15),
		(m_skeletonCurrentPos.y - 30),
		(m_skeletonCurrentPos.x + 15),
		(m_skeletonCurrentPos.y + 30),

	};

	return myRect;

}

Rect EnemyYama::GetCheckRectMush()
{

	Rect myRect = {

		(m_mushCurrentPos.x - 15),
		(m_mushCurrentPos.y - 30),
		(m_mushCurrentPos.x + 15),
		(m_mushCurrentPos.y + 30),

	};

	return myRect;

}

void EnemyYama::InitAnimation()
{

	LoadDivGraph(kBatPath,
		8, 8, 1, m_sizeX, m_sizeY,
		m_graphHandle[ENEMY_TYPE_BAT_YAMA]);

	LoadDivGraph(kGoblinPath,
		8, 8, 1, m_sizeX, m_sizeY,
		m_graphHandle[ENEMY_TYPE_GOBLIN_YAMA]);

	LoadDivGraph(kSkeletonPath,
		4, 4, 1, m_sizeX, m_sizeY,
		m_graphHandle[ENEMY_TYPE_SKELETON_YAMA]);

	LoadDivGraph(kMushPath,
		8, 8, 1, m_sizeX, m_sizeY,
		m_graphHandle[ENEMY_TYPE_MUSH_YAMA]);

}

void EnemyYama::InitStatus()
{
	if (m_pEnemyStatus == nullptr) {
		m_hp = 10;
		m_speed = 1.0f;
		return;
	}

	if (m_enmeyType >= m_pEnemyStatus->enemys.size()) {
		m_hp = 10;
		return;
	}

	const Enemys& status = m_pEnemyStatus->enemys[m_enmeyType];

	m_hp = status.enemyCurrentHP;

	m_maxHp = status.enemyMaxHP;

	m_attack = status.enemyAttackPower;

	m_speed = status.enemySpeed;

}

void EnemyYama::UpdateMove()
{

	/*
	// プレイヤーがいなかったら追尾しない
	if (m_pPlayer != nullptr) {

		Vector2 dir = m_pPlayer->GetModelPos() - m_batCurrentPos;

		if (dir.GetSqLength() > 0.0f) {

			m_batMoveDir = dir.GetNormalize();

		}

	}

	// プレイヤーがいなかったら追尾しない
	if (m_pPlayer != nullptr) {

		Vector2 dir = m_pPlayer->GetModelPos() - m_goblinCurrentPos;

		if (dir.GetSqLength() > 0.0f) {

			m_goblinMoveDir = dir.GetNormalize();

		}

	}

	// プレイヤーがいなかったら追尾しない
	if (m_pPlayer != nullptr) {

		Vector2 dir = m_pPlayer->GetModelPos() - m_mushCurrentPos;

		if (dir.GetSqLength() > 0.0f) {

			m_mushMoveDir = dir.GetNormalize();

		}

	}

	// プレイヤーがいなかったら追尾しない
	if (m_pPlayer != nullptr) {

		Vector2 dir = m_pPlayer->GetModelPos() - m_skeletonCurrentPos;

		if (dir.GetSqLength() > 0.0f) {

			m_skeletonMoveDir = dir.GetNormalize();

		}

	}

	// バットの移動処理
	m_batCurrentPos += m_batMoveDir * m_speed;

	// ゴブリンの移動処理
	m_goblinCurrentPos += m_goblinMoveDir * m_speed;

	// マッシュルームの移動処理
	m_mushCurrentPos += m_mushMoveDir * m_speed;

	// スケルトンの移動処理
	m_skeletonCurrentPos += m_skeletonMoveDir * m_speed;
	*/

	if (m_pPlayer != nullptr) {

		Vector2 dir = m_pPlayer->GetModelPos() - m_currentPos;

		m_moveDir = dir.GetNormalize();

	}

	m_currentPos += m_moveDir * m_speed;

}

void EnemyYama::DrawEnemy()
{

	/*
	DrawRotaGraph((int)m_batCurrentPos.x, (int)m_batCurrentPos.y,
		1.0f, 0, m_graphHandle[ENEMY_TYPE_BAT_YAMA][m_motionFrame], TRUE);


	DrawRotaGraph((int)m_goblinCurrentPos.x, (int)m_goblinCurrentPos.y,
		1.0f, 0, m_graphHandle[ENEMY_TYPE_GOBLIN_YAMA][m_motionFrame], TRUE);


	DrawRotaGraph((int)m_skeletonCurrentPos.x, (int)m_skeletonCurrentPos.y,
		1.0f, 0, m_graphHandle[ENEMY_TYPE_SKELETON_YAMA][m_motionFrame], TRUE);


	DrawRotaGraph((int)m_mushCurrentPos.x, (int)m_mushCurrentPos.y,
		1.0f, 0, m_graphHandle[ENEMY_TYPE_MUSH_YAMA][m_motionFrame], TRUE);
	
	*/

	int handle = m_graphHandle[m_enmeyType][m_motionFrame];

	DrawRotaGraph((int)m_currentPos.x, (int)m_currentPos.y, 1.0f, 0, handle, TRUE);

	DrawBox(GetCheckRectBat().left, GetCheckRectBat().top, GetCheckRectBat().right, GetCheckRectBat().bottom, GetColor(255, 255, 255), false);

	DrawBox(GetCheckRectGoblin().left, GetCheckRectGoblin().top, GetCheckRectGoblin().right, GetCheckRectGoblin().bottom, GetColor(255, 255, 255), false);

	DrawBox(GetCheckRectSkeleton().left, GetCheckRectSkeleton().top, GetCheckRectSkeleton().right, GetCheckRectSkeleton().bottom, GetColor(255, 255, 255), false);

	DrawBox(GetCheckRectMush().left, GetCheckRectMush().top, GetCheckRectMush().right, GetCheckRectMush().bottom, GetColor(255, 255, 255), false);

}

void EnemyYama::SetGraphHandle(int enemyMgr[ENEMY_TYPE_MAX_YAMA][ENEMY_MOTION_NUM_YAMA])
{

	// エネミーマネージャーから受け取ったグラフィックハンドルを設定
	for (int i = 0; i < ENEMY_TYPE_MAX_YAMA; i++) {

		for (int j = 0; j < ENEMY_MOTION_NUM_YAMA; j++) {

			m_graphHandle[i][j] = enemyMgr[i][j];

		}

	}

}

void EnemyYama::SetParam(Vector2 currentPos, Vector2 moveDir)
{

	m_currentPos = currentPos;
	m_moveDir = moveDir;

}
