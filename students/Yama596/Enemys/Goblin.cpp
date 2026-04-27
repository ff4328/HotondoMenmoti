#include "Goblin.h"
#include "../students/oreistake/Player.h"
#include "../students/Yama596/Enemy/HitPointYama.h"

#include "../students/bamboojr36/Collision.h"
#include "../students/bamboojr36/Vector2.h"

namespace {

	const int kSpeed = 5;

}

Goblin::Goblin() :
	m_graphHandle{},
	m_currentPos(Vector2()),
	m_prevPos(Vector2()),
	m_moveDir(Vector2()),
	m_motionCounter(0),
	m_motionFrame(0),
	m_homingTimer(0),
	m_isDead(false),
	m_deadCount(false),
	m_homingTimeMax(10),
	m_direction(DIRECTION_RIGHT),
	m_pPlayer(nullptr),
	m_pHp(nullptr)
{

	m_pHp = new HitPointYama();

}

void Goblin::Init() {

	m_pHp->SetHPMax(10);

	m_homingTimer = m_homingTimeMax;

}

void Goblin::End() {

}

EnemyBase* Goblin::Update() {

	if (m_isDead) return this;

	UpdateMove();

	DirectionSwitch();

	return this;

}

void Goblin::Draw() {

	if (m_isDead) return;

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

#ifdef _DEBUG

	DrawBox(GetCheckRect().left, GetCheckRect().top, GetCheckRect().right, GetCheckRect().bottom, GetColor(255, 255, 255), false);

#endif

}

void Goblin::Damege(int value) {

	m_pHp->Damage(value);

}

bool Goblin::Dead() {

	if (m_pHp->IsDead()) {

		m_isDead = true;

	}

	return m_isDead;

}

Rect Goblin::GetCheckRect() {

	Rect myRect = {

		(m_currentPos.x - 15),
		(m_currentPos.y - 10),
		(m_currentPos.x + 15),
		(m_currentPos.y + 25),

	};

	return myRect;

}

void Goblin::SetGraphHandle(int* graphHandle)
{

	for (int i = 0; i < kGoblinMotionNum; i++)
	{

		m_graphHandle[i] = graphHandle[i];

	}

}

Vector2 Goblin::GetPos()
{

	return m_currentPos;

}

void Goblin::AddPos(const Vector2& vector)
{

	m_currentPos += vector;

}

void Goblin::UpdateMove() {

	// プレイヤーがいなかったら追尾しない
	if (m_homingTimer > 0 && m_pPlayer != nullptr) {

		Vector2 dir = m_pPlayer->GetModelPos() - m_currentPos;

		if (dir.GetSqLength() > 0.0f) {

			m_moveDir = dir.GetNormalize();

		}

		m_homingTimer--;

	}

	m_currentPos += m_moveDir * kSpeed;

}

void Goblin::DrawEnemy() {

	DrawRotaGraph((int)m_currentPos.x, (int)m_currentPos.y, 1.0f, 0, m_graphHandle[m_motionFrame], true, m_direction);

}

void Goblin::DirectionSwitch()
{

	if (m_moveDir.x > 0.0f) {

		m_direction = DIRECTION_RIGHT;

	}
	else if (m_moveDir.x < 0.0f) {

		m_direction = DIRECTION_LEFT;

	}

}