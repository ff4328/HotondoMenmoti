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


void EXPItem::GoPlayer()
{
	if (m_player != nullptr) {

		Vector2 dir = m_player->GetModelPos() - m_position;

		if (dir.GetSqLength() > 0.0f) {

			m_moveDir = dir.GetNormalize();
		}
	}
	m_position += m_moveDir * m_Speed;

}

void EXPItem::Generate(Vector2 pos)
{
	DrawExtendGraph(
		pos.x, pos.y,
		pos.x + 10, pos.y + 10,
		m_graphHandleEXPItem, TRUE);
}


