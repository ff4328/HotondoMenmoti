#include "Enemy.h"
#include<DxLib.h>
#include<math.h>
#include "../students/Yama596/Enemy/Literal.h"
#include "../students/oreistake/Player.h"

namespace {

	const char* const kGoblinPath = "Resource\\Monsters Creatures Fantasy\\Sprites\\Goblin\\Run.png";

	const char* const kSkeletonPath = "Resource\\Monsters Creatures Fantasy\\Sprites\\Skeleton\\Walk.png";

};

Enemy::Enemy():
	m_graphHandle(),
	m_enemySpeed(2.0f),
	m_currentPos(Vector2(400.0f,300.0f)),
	m_prevPos(m_currentPos),
	m_moveDir(Vector2()),
	m_motionCounter(0),
	m_motionFrame(0),
	m_sizeX(150),
	m_sizeY(150),
	m_enmeyType(EnemyType::ENEMY_TYPE_GOBLIN),
	m_direction(DIRECTION_RIGHT),
	m_pPlayer(nullptr)
{
}

void Enemy::Init()
{

	// グラフィックハンドルの初期化
	for (int i = 0; i < CHARA_MOTION_NUM; i++) {

		for (int j = 0; j < CHARA_MOB_NUM; j++) {

			m_graphHandle[i][j] = 0;

		}

	}

	InitAnimation();

}

void Enemy::InitAnimation()
{
	LoadDivGraph(kSkeletonPath,
		4, 4, 1, m_sizeX, m_sizeY,
		m_graphHandle[ENEMY_TYPE_SKELETON]);
}

void Enemy::End()
{

}

void Enemy::Update()
{

	UpdateMove();

}

void Enemy::Draw()
{

	// モーション制御用のカウンタをカウントアップ
	m_motionCounter++;

	// アニメーションのフレームを1コマ進める
	if (m_motionCounter % 20 == 0) {

		m_motionCounter = 0;

		// 敵のアニメーションは全部で4コマ想定なので
		m_motionFrame++;
		m_motionFrame = m_motionFrame % 4;

	}

	DrawRotaGraph((int)m_currentPos.x, (int)m_currentPos.y,
		1.0f, 0, m_graphHandle[ENEMY_TYPE_SKELETON][m_motionFrame], TRUE);

	printfDx("mobPosX : %f\n", m_currentPos.x);
	printfDx("mobPosX : %f\n", m_currentPos.y);

}

void Enemy::RestorePos()
{
	m_currentPos = m_prevPos;
}

void Enemy::UpdatePrevPos()
{
	m_prevPos = m_currentPos;
}

void Enemy::UpdateMove()
{

	if (m_pPlayer != nullptr) {

		Vector2 dir = m_pPlayer->GetModelPos() - m_currentPos;

		if (dir.GetSqLength() > 0.0f) {

			m_moveDir = dir.GetNormalize();

		}

	}

	m_currentPos += m_moveDir * m_enemySpeed;

}

void Enemy::SetGraphHandle(int enemyMgr[CHARA_MOTION_NUM_Yama][ENEMY_TYPE_MAX_Yama])
{

	// エネミーマネージャーから受け取ったグラフィックハンドルを設定
	for (int i = 0; i < CHARA_MOTION_NUM; i++) {

		for (int j = 0; i < CHARA_MOB_NUM; j++) {

			m_graphHandle[i][j] = enemyMgr[i][m_enmeyType];

		}

	}

}
