#include "Heal.h"
#include "Collision.h"
#include "Vector2.h"

namespace 
{
	constexpr float kHealScale = 0.1f;
}

Heal::Heal() :
	m_position(0, 0),
	m_collision(nullptr)
{
}

Heal::Heal(Vector2 position):
//	m_graphHandle(0),
//  m_scale(kHealScale),
	m_position(position),
	m_collision(std::make_unique<Collision>(position, Vector2(50 * kHealScale, 50 * kHealScale)))
{
}

void Heal::Init()
{

}	

void Heal::End()
{
}

void Heal::Update()
{
	m_collision->SetPosition(GetCollisionCenterPos());
}

void Heal::Draw(int graphHandle)
{
	DrawRotaGraph(
		static_cast<int>(m_position.x),
		static_cast<int>(m_position.y),
		kHealScale,
		0.0,
		graphHandle,
		TRUE);
}

Vector2 Heal::GetCollisionCenterPos() const
{
	Vector2 centerPos = m_collision->GetPosition();
	return centerPos;
}