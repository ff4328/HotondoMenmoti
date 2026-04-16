#include "Bomb.h"
#include "Collision.h"
#include "Vector2.h"
#include<memory>
#include "DxLib.h"

namespace
{
	constexpr float kHealScale = 1.0f;
	const char* const kItembomb = ".\\Resource\\Item\\Bomb.png";
}

Bomb::Bomb(Vector2 position) :
	m_position(position),
	m_graphHandleBomb(-1),
	m_collision(nullptr)
{
	m_collision = std::make_unique<Collision>();
}

void Bomb::Init()
{
	m_position = Vector2(100.0f, 100.0f);
	m_graphHandleBomb = LoadGraph(kItembomb);
}

void Bomb::End()
{
	DeleteGraph(m_graphHandleBomb);
}


void Bomb::Update()
{
}

void Bomb::Draw()
{
	DrawBox(m_position.x+13, m_position.y+13,
		m_position.x + 40, m_position.y + 40,
		GetColor(255, 0, 0), FALSE);

	DrawExtendGraph(
		m_position.x, m_position.y,
		m_position.x + 50, m_position.y + 50,
		m_graphHandleBomb, TRUE);
}

Rect Bomb::GetCheckRect() {
	Rect myRect = {
		(m_position.x+13),
		(m_position.y+13),
		(m_position.x + 40),
		(m_position.y + 40),
	};
	return myRect;
}