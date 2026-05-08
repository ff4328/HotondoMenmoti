#include "Mushroom.h"
#include "../students/oreistake/Player.h"
#include "../students/Yama596/Enemy/HitPointYama.h"

#include "../students/bamboojr36/Collision.h"
#include "../students/bamboojr36/Vector2.h"

namespace {

	const int kSpeed = 1;

}

Mushroom::Mushroom() :
	m_graphHandle{},
	m_currentPos(Vector2()),
	m_prevPos(Vector2()),
	m_moveDir(Vector2()),
	m_motionCounter(0),
	m_motionFrame(0),
	m_isDead(false),
	m_deadCount(false),
	m_invincibleTime(0.0f),
	m_hit(false),
	m_direction(DIRECTION_RIGHT),
	m_pPlayer(nullptr),
	m_pHp(nullptr)
{

	m_pHp = new HitPointYama();

}

void Mushroom::Init() {

	m_pHp->SetHPMax(30);

}

void Mushroom::End() {

}

EnemyBase* Mushroom::Update() {

	if (m_isDead) return this;

	Dead();

	DamageInterval();

	UpdateMove();

	DirectionSwitch();

	return this;

}

void Mushroom::Draw() {

	//if (m_isDead) return;

	// モーション制御用のカウンタをカウントアップ
	m_motionCounter++;

	// アニメーションのフレームを1コマ進める
	if (m_motionCounter % 20 == 0) {

		m_motionCounter = 0;

		if (m_isDead)
		{

			if (m_motionFrame < 4)
			{

				m_motionFrame++;

			}

		}
		else
		{

			m_motionFrame++;

			m_motionFrame %= 8;

		}

	}

	DrawEnemy();

#ifdef _DEBUG

	//printfDx("ヒット : %d\n", m_hit);

	printfDx("マッシュルームの体力 : %d\n", m_pHp->GetHP());

	DrawBox(GetCheckRect().left, GetCheckRect().top, GetCheckRect().right, GetCheckRect().bottom, GetColor(255, 255, 255), false);

#endif

}

void Mushroom::Damege(int value) {

	if (m_hit) return;

	m_pHp->Damage(value);

	m_hit = true;

}

bool Mushroom::Dead() {

	if (m_pHp->IsDead() && !m_isDead) {

		m_isDead = true;

		m_motionFrame = 0;

		for (int i = 0; i < kMushroomMotionNum; i++)
		{

			m_graphHandle[i] = m_deadGraphHandle[i];

		}

	}

	return m_isDead;

}

Rect Mushroom::GetCheckRect() {

	if (m_isDead)
	{

		return { 0,0,0,0 };

	}

	Rect myRect = {

		(m_currentPos.x - 15),
		(m_currentPos.y - 15),
		(m_currentPos.x + 15),
		(m_currentPos.y + 25),

	};

	return myRect;

}

void Mushroom::SetGraphHandle(int* graphHandle)
{

	for (int i = 0; i < kMushroomMotionNum; i++)
	{

		m_graphHandle[i] = graphHandle[i];

	}

}

Vector2 Mushroom::GetPos()
{

	return m_currentPos;

}

void Mushroom::AddPos(const Vector2& vector)
{

	m_currentPos += vector;

}

void Mushroom::SetRunGraphHandle(int* handle)
{

	for (int i = 0; i < kMushroomMotionNum; i++)
	{

		m_runGraphHandle[i] = handle[i];

		m_graphHandle[i] = handle[i];

	}

}

void Mushroom::SetDeadGraphHandle(int* handle)
{

	for (int i = 0; i < kMushroomMotionNum; i++)
	{

		m_deadGraphHandle[i] = handle[i];

	}

}

bool Mushroom::DeadEnd()
{

	return m_isDead && m_motionFrame >= 4;

}

void Mushroom::UpdateMove() {

	// プレイヤーがいなかったら追尾しない
	if (m_pPlayer != nullptr) {

		Vector2 dir = m_pPlayer->GetModelPos() - m_currentPos;

		if (dir.GetSqLength() > 0.0f) {

			m_moveDir = dir.GetNormalize();

		}

	}

	m_currentPos += m_moveDir * kSpeed;

}

void Mushroom::DrawEnemy() {

	DrawRotaGraph((int)m_currentPos.x, (int)m_currentPos.y, 1.0f, 0, m_graphHandle[m_motionFrame], true, m_direction);

}

void Mushroom::DirectionSwitch()
{

	if (m_moveDir.x > 0.0f) {

		m_direction = DIRECTION_RIGHT;

	}
	else if (m_moveDir.x < 0.0f) {

		m_direction = DIRECTION_LEFT;

	}

}

void Mushroom::DamageInterval()
{

	if (!m_hit) return;

	m_invincibleTime++;

	if (m_invincibleTime >= 30.0f)
	{

		m_hit = false;

		m_invincibleTime = 0;

	}

}
