#include "MiniMushroom.h"
#include "../students/oreistake/Player.h"
#include "../students/Yama596/Enemy/HitPointYama.h"

#include "../students/bamboojr36/Collision.h"
#include "../students/bamboojr36/Vector2.h"

namespace {

	const float kSpeed = 1.5f;

	const float kNeutralSize = 0.5f;

	const float kDamageSize = 0.0f;

	const float kFirstInvisibleStart = 0.1f;

	const float kFirstInvisibleEnd = 5.0f;

	const float kSecondInvisibleStart = 10.0f;

	const float kSecondInvisibleEnd = 15.0f;

	const float kThirdInvisibleStart = 20.0f;

	const float kThirdInvisibleEnd = 25.0f;

	const int kHp_0 = 5;

}

MiniMushroom::MiniMushroom() :
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
	m_size(kNeutralSize),
	m_direction(DIRECTION_RIGHT),
	m_pPlayer(nullptr),
	m_pHp(nullptr)
{

	m_pHp = new HitPointYama();

}

void MiniMushroom::Init()
{

	m_pHp->SetHPMax(kHp_0);

}

void MiniMushroom::End()
{
}

EnemyBase* MiniMushroom::Update()
{

	if (m_isDead) return this;

	Dead();

	DamageInterval();

	UpdateMove();

	DirectionSwitch();

	return this;

}

void MiniMushroom::Draw()
{

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

	//printfDx("ミニマッシュルームの体力 : %d\n", m_pHp->GetHP());

	DrawBox(GetCheckRect().left, GetCheckRect().top, GetCheckRect().right, GetCheckRect().bottom, GetColor(255, 255, 255), false);

#endif

}

void MiniMushroom::Damege(int value)
{

	if (m_hit) return;

	m_pHp->Damage(value);

	m_hit = true;

}

bool MiniMushroom::Dead()
{

	if (m_pHp->IsDead() && !m_isDead) {

		m_isDead = true;

		m_motionFrame = 0;

		for (int i = 0; i < kMiniMushroomMotionNum; i++)
		{

			m_graphHandle[i] = m_deadGraphHandle[i];

		}

	}

	return m_isDead;

}

Rect MiniMushroom::GetCheckRect()
{

	if (m_isDead)
	{

		return { 0,0,0,0 };

	}

	Rect myRect = {

		(m_currentPos.x - 5),
		(m_currentPos.y - 5),
		(m_currentPos.x + 5),
		(m_currentPos.y + 15),

	};

	return myRect;

}

Vector2 MiniMushroom::GetPos()
{

	return m_currentPos;

}

void MiniMushroom::AddPos(const Vector2& vector)
{

	m_currentPos += vector;

}

void MiniMushroom::SetRunGraphHandle(int* handle)
{

	for (int i = 0; i < kMiniMushroomMotionNum; i++)
	{

		m_runGraphHandle[i] = handle[i];

		m_graphHandle[i] = handle[i];

	}

}

void MiniMushroom::SetDeadGraphHandle(int* handle)
{

	for (int i = 0; i < kMiniMushroomMotionNum; i++)
	{

		m_deadGraphHandle[i] = handle[i];

	}

}

bool MiniMushroom::DeadEnd()
{

	return m_isDead && m_motionFrame >= 4;

}

void MiniMushroom::UpdateMove() {

	// プレイヤーがいなかったら追尾しない
	if (m_pPlayer != nullptr) {

		Vector2 dir = m_pPlayer->GetModelPos() - m_currentPos;

		if (dir.GetSqLength() > 0.0f) {

			m_moveDir = dir.GetNormalize();

		}

	}

	// プレイヤーの方向に移動する
	m_currentPos += m_moveDir * kSpeed;

}

void MiniMushroom::DrawEnemy() {

	DrawRotaGraph((int)m_currentPos.x, (int)m_currentPos.y, kNeutralSize, 0, m_graphHandle[m_motionFrame], true, m_direction);

}

void MiniMushroom::DirectionSwitch()
{

	// 右に移動していたら
	if (m_moveDir.x > 0.0f) {

		m_direction = DIRECTION_RIGHT;

	}
	// 左に移動していたら
	else if (m_moveDir.x < 0.0f) {

		m_direction = DIRECTION_LEFT;

	}

}

void MiniMushroom::DamageInterval()
{

	if (!m_hit) return;

	m_invincibleTime++;

	// 3回点滅させる処理を行う
	if ((m_invincibleTime >= kFirstInvisibleStart && m_invincibleTime <= kFirstInvisibleEnd) ||
		(m_invincibleTime >= kSecondInvisibleStart && m_invincibleTime <= kSecondInvisibleEnd) ||
		(m_invincibleTime >= kThirdInvisibleStart && m_invincibleTime <= kThirdInvisibleEnd)) {

		m_size = kDamageSize;

	}
	else {

		m_size = kNeutralSize;

	}

	if (m_invincibleTime >= 30.0f)
	{

		m_hit = false;

		m_invincibleTime = 0;

	}

}
