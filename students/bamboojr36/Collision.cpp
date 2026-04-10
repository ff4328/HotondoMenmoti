#include "Collision.h"
#include <cassert>
#include <DxLib.h>

bool Collision::CheckCollision(const Collision& other) const
{
	const float checkBox = dynamic_cast<const Collision&>(other).m_size.x / 2 + m_size.x / 2;

	assert(checkBox > 0 && "Collision:è’ìÀîªíËÇÃÉTÉCÉYÇ™0à»â∫");

	if(m_position.x - checkBox < other.m_position.x && m_position.x + checkBox > other.m_position.x)return false;
	if(m_position.y - checkBox < other.m_position.y && m_position.y + checkBox > other.m_position.y)return false;

	return true;
}

void Collision::DebugDraw() const
{
	Vector2 Vertex[4];

	Vertex[0] = Vector2(m_position.x - m_size.x / 2, m_position.y - m_size.y / 2);
	Vertex[1] = Vector2(m_position.x + m_size.x / 2, m_position.y - m_size.y / 2);
	Vertex[2] = Vector2(m_position.x + m_size.x / 2, m_position.y + m_size.y / 2);
	Vertex[3] = Vector2(m_position.x - m_size.x / 2, m_position.y + m_size.y / 2);

	DrawBox(
		static_cast<int>(Vertex[0].x), static_cast<int>(Vertex[0].y),
		static_cast<int>(Vertex[2].x), static_cast<int>(Vertex[2].y),
		GetColor(255, 0, 0), FALSE);

}
