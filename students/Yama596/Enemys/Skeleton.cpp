#include "Skeleton.h"
#include "../students/oreistake/Player.h"
#include "../students/Yama596/Enemy/HitPointYama.h"

#include "../students/bamboojr36/Collision.h"
#include "../students/bamboojr36/Vector2.h"

namespace {

	const int kSpeed = 1;

}

Skeleton::Skeleton() :
	m_graphHandle{},
	m_currentPos(Vector2()),
	m_prevPos(Vector2()),
	m_moveDir(Vector2()),
	m_motionCounter(0),
	m_motionFrame(0),
	m_direction(DIRECTION_RIGHT),
	m_pPlayer(nullptr),
	m_pHp(nullptr)
{

	m_pHp = new HitPointYama();

}

void Skeleton::Init() {

	m_pHp->SetHPMax(10);

}

void Skeleton::End() {

}

EnemyBase* Skeleton::Update() {

	if (Dead()) return this;

	UpdateMove();

	DirectionSwitch();

	return this;

}

void Skeleton::Draw() {

	if (Dead()) return;

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

void Skeleton::Damege(int value) {

	m_pHp->Damage(value);

}

bool Skeleton::Dead() {

	return m_pHp->IsDead();

}

Rect Skeleton::GetCheckRect() {

	Rect myRightRect = {

		(m_currentPos.x - 10),
		(m_currentPos.y - 40),
		(m_currentPos.x + 30),
		(m_currentPos.y + 40),

	};

	Rect myLeftRect = {

		(m_currentPos.x - 30),
		(m_currentPos.y - 40),
		(m_currentPos.x + 10),
		(m_currentPos.y + 40),

	};

	if (m_direction == DIRECTION_RIGHT) {

		return myRightRect;

	}
	else if(m_direction == DIRECTION_LEFT){

		return myLeftRect;

	}

}

void Skeleton::SetGraphHandle(int* graphHandle)
{

	for (int i = 0; i < kSkeletonMotionNum; i++)
	{

		m_graphHandle[i] = graphHandle[i];

	}

}

Vector2 Skeleton::GetPos()
{

	return m_currentPos;

}

void Skeleton::AddPos(const Vector2& vector)
{

	m_currentPos += vector;

}

void Skeleton::UpdateMove() {

	// プレイヤーがいなかったら追尾しない
	if (m_pPlayer != nullptr) {

		Vector2 dir = m_pPlayer->GetModelPos() - m_currentPos;

		if (dir.GetSqLength() > 0.0f) {

			m_moveDir = dir.GetNormalize();

		}

	}

	m_currentPos += m_moveDir * kSpeed;

}

void Skeleton::DrawEnemy() {

	DrawRotaGraph((int)m_currentPos.x, (int)m_currentPos.y, 1.5f, 0, m_graphHandle[m_motionFrame], true, m_direction);

}

void Skeleton::DirectionSwitch()
{

	if (m_moveDir.x > 0.0f) {

		m_direction = DIRECTION_RIGHT;

	}
	else if (m_moveDir.x < 0.0f) {

		m_direction = DIRECTION_LEFT;

	}

}