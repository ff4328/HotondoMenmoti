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
	constexpr float m_moveDir = 1.0f;
	constexpr float kSpeed = 1.0f;

}

EXPItem::EXPItem(Vector2 position) :
	isDown(true),
	m_position(),
	m_graphHandleEXPItem(-1),
	m_collision(nullptr)
{
	m_collision = std::make_unique<Collision>();
	m_position = position;
}

void EXPItem::Init()
{
	m_position = Vector2(1.0f, 1.0f);
	m_graphHandleEXPItem = LoadGraph(kItemEXP);
	isDown = true;
}

void EXPItem::End()
{
	DeleteGraph(m_graphHandleEXPItem);
}

void EXPItem::Update()
{
}

void EXPItem::Draw()
{
	if (!(isDown))return;
	if (canDraw) {

	DrawBox(m_position.x, m_position.y,
		m_position.x + 10, m_position.y + 10,
		GetColor(255, 0, 0), FALSE);

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
void EXPItem::Destroy()
{
	DeleteGraph(m_graphHandleEXPItem);
	m_graphHandleEXPItem = -1;
	canDraw = false;
	isDown = false;
}

/*
void EXPItem::GoPlayer()
{
	if (m_player != nullptr) {

		Vector2 dir = m_player->GetModelPos() - m_position;

		if (dir.GetSqLength() > 0.0f) {

			EXPItem(pos) = dir.GetNormalize();
		}
	}
	m_position.x += m_moveDir * kSpeed;
}

*/