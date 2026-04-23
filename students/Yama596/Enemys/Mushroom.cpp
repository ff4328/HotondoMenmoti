#include "Mushroom.h"
#include "../students/oreistake/Player.h"
#include "../students/Yama596/Enemy/HitPointYama.h"

#include "../students/bamboojr36/Collision.h"
#include "../students/bamboojr36/Vector2.h"

namespace {

	const char* const kMushPath = "Resource\\Monsters Creatures Fantasy\\Sprites\\Mushroom\\Run.png";

	const int kSize = 150;

	const int kSpeed = 1;

}

Mushroom::Mushroom() :
	m_graphHandle{},
	m_currentPos(Vector2()),
	m_moveDir(Vector2()),
	m_motionCounter(0),
	m_motionFrame(0),
	m_pPlayer(nullptr),
	m_pHp(nullptr)
{

	m_pPlayer = new PlayerMove();

	m_pHp = new HitPointYama();

}

void Mushroom::Init() {

	// グラフィックハンドルの初期化
	for (int i = 0; i < kMotionNum; i++) {

		m_graphHandle[i] = 0;

	}

}

void Mushroom::End() {

	// グラフィックハンドルの初期化
	for (int i = 0; i < kMotionNum; i++) {

		DeleteGraph(m_graphHandle[i]);

	}

}

void Mushroom::Update() {

	if (Dead()) return;

	UpdateMove();

}

void Mushroom::Draw() {

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

void Mushroom::Damege(int value) {

	m_pHp->Damage(value);

}

bool Mushroom::Dead() {

	return m_pHp->IsDead();

}

Rect Mushroom::GetCheckRect() {

	Rect myRect = {

			(m_currentPos.x - 15),
			(m_currentPos.y - 30),
			(m_currentPos.x + 15),
			(m_currentPos.y + 30),

	};

	return myRect;

}

void Mushroom::SetGraphHandle(int* graphHandle)
{

	for (int i = 0; i < kMotionNum; i++)
	{

		m_graphHandle[i] = graphHandle[i];

	}

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

	DrawRotaGraph((int)m_currentPos.x, (int)m_currentPos.y, 1.0f, 0, m_graphHandle[m_motionFrame], TRUE);

	DrawBox(GetCheckRect().left, GetCheckRect().top, GetCheckRect().right, GetCheckRect().bottom, GetColor(255, 255, 255), false);

}
