#include "EXPItem.h"
#include "Collision.h"
#include "Vector2.h"
#include<memory>
#include "DxLib.h"
#include "../oreistake/Player.h"

namespace
{
	constexpr float kEXPItemScale = 1.0f;
	const char* const kItemEXP = ".\\Resource\\Item\\EXP.png";
}

EXPItem::EXPItem(Vector2 position):
	isDown(true),
	m_Speed(100.0f),
	m_position(Vector2(position)),
	m_moveDir(Vector2()),
	m_graphHandleEXPItem(-1),
	m_collision(nullptr),
	m_player(nullptr)
{
	m_collision = std::make_unique<Collision>();
}

void EXPItem::Init()
{
	m_player = new PlayerMove();
	m_graphHandleEXPItem = LoadGraph(kItemEXP);
	isDown = true;
}

void EXPItem::Draw()
{
	if (!(isDown))return;
	if (canDraw) {

		DrawExtendGraph(
			m_position.x, m_position.y,
			m_position.x + 10, m_position.y + 10,
			m_graphHandleEXPItem, TRUE);

	}	
}

Rect EXPItem::GetRect() {
	Rect myRect = {
		(m_position.x ),
		(m_position.y ),
		(m_position.x +10),
		(m_position.y +10),
	};
	return myRect;
}

Rect EXPItem::GetRects() {
	Rect myRect = {
		(m_position.x-10),
		(m_position.y-10),
		(m_position.x + 20),
		(m_position.y + 20),
	};
	return myRect;
}

void EXPItem::Destroy()
{
	DeleteGraph(m_graphHandleEXPItem);
	m_graphHandleEXPItem = -1;
	canDraw = false;
	isDown = false;
}


void EXPItem::GoPlayer()
{
	if (m_player == nullptr) return;

	Vector2 target = m_player->GetModelPos();
	Vector2 dir = target - m_position;

	float dist = dir.GetLength();
	if (dist <= 0.1f) return;

	// 正規化
	Vector2 n = dir.GetNormalize();

	// Lerp係数（0.0f〜1.0f）小さいほどゆっくり、大きいほど吸引が強い
	float t = 0.12f;

	// Lerp: 現在位置 + (目標方向 * t)
	m_position = m_position + (n * (dist * t));
}

void EXPItem::Generate(Vector2 pos)
{
	DrawExtendGraph(
		pos.x, pos.y,
		pos.x + 10, pos.y + 10,
		m_graphHandleEXPItem, TRUE);
}


