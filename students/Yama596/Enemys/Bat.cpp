#include "Bat.h"
#include "../students/oreistake/Player.h"
#include "../students/Yama596/Enemy/HitPointYama.h"

#include "../students/bamboojr36/Collision.h"
#include "../students/bamboojr36/Vector2.h"

namespace {

	const int kSpeed = 1;

}

Bat::Bat():
	m_graphHandle{},
	m_currentPos(Vector2()),
	m_prevPos(Vector2()),
	m_moveDir(Vector2()),
	m_motionCounter(0),
	m_motionFrame(0),
	m_pPlayer(nullptr),
	m_pHp(nullptr)
{

	m_pHp = new HitPointYama();

}

void Bat::Init() {

	m_pHp->SetHPMax(10);

}

void Bat::End() {

}

EnemyBase* Bat::Update() {

	if (Dead()) return this;

	RecordPosition();

	UpdateMove();

	return this;

}

void Bat::Draw() {

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

void Bat::Damege(int value) {

	m_pHp->Damage(value);

}

bool Bat::Dead() {

	return m_pHp->IsDead();

}

Rect Bat::GetCheckRect() {

	Rect myRect = {

			(m_currentPos.x - 15),
			(m_currentPos.y - 30),
			(m_currentPos.x + 15),
			(m_currentPos.y + 30),

	};

	return myRect;

}

void Bat::SetGraphHandle(int* graphHandle)
{

	for (int i = 0; i < kBatMotionNum; i++)
	{

		m_graphHandle[i] = graphHandle[i];

	}

}

void Bat::RecordPosition()
{

	m_prevPos.x = m_currentPos.x;

	m_prevPos.y = m_currentPos.y;

}

void Bat::RevertPosition()
{

	m_currentPos.x = m_prevPos.x;

	m_currentPos.y = m_prevPos.y;

}

Vector2 Bat::GetPos()
{

	return m_currentPos;

}

void Bat::AddPos(const Vector2& vector)
{

	m_currentPos += vector;

}

void Bat::UpdateMove() {

	// プレイヤーがいなかったら追尾しない
	if (m_pPlayer != nullptr) {

		Vector2 dir = m_pPlayer->GetModelPos() - m_currentPos;

		if (dir.GetSqLength() > 0.0f) {

			m_moveDir = dir.GetNormalize();

		}

	}

	m_currentPos += m_moveDir * kSpeed;

}

void Bat::DrawEnemy() {

	DrawRotaGraph((int)m_currentPos.x, (int)m_currentPos.y,1.0f, 0, m_graphHandle[m_motionFrame], TRUE);

}