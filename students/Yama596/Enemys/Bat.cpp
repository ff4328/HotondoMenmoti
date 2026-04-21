#include "Bat.h"
#include "../students/oreistake/Player.h"
#include "../students/Yama596/Enemy/HitPointYama.h"

#include "../students/bamboojr36/Collision.h"
#include "../students/bamboojr36/Vector2.h"

namespace {

	const char* const kBatPath = "Resource\\Monsters Creatures Fantasy\\Sprites\\Flying eye\\Flight.png";

	const int kSpeed = 1;

}

Bat::Bat():
	m_graphHandle{},
	m_currentPos(Vector2()),
	m_moveDir(Vector2()),
	m_motionCounter(0),
	m_motionFrame(0),
	m_pPlayer(nullptr),
	m_pHp(nullptr)
{

	m_pHp = new HitPointYama();

}

void Bat::Init() {

	InitAnimation();

	InitStatus();

}

void Bat::End() {

	// グラフィックハンドルの初期化
	for (int i = 0; i < kMotionNum; i++) {

		DeleteGraph(m_graphHandle[i]);

	}

}

void Bat::Update() {

	if (Dead()) return;

	UpdateMove();

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

void Bat::InitAnimation() {

}

void Bat::InitStatus() {



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

	DrawBox(GetCheckRect().left, GetCheckRect().top, GetCheckRect().right, GetCheckRect().bottom, GetColor(255, 255, 255), false);

}