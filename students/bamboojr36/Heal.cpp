#include "Heal.h"
#include "Collision.h"
#include "Vector2.h"

namespace 
{
	constexpr float kHealScale = 1.0f;
}


Heal::Heal():
	m_scale(kHealScale),
	m_position()
{
}

Heal::Heal(Vector2 position):
	m_scale(kHealScale),
	m_position(position)
{
}

void Heal::Init()
{
}	

void Heal::End()
{
	delete m_collision;
}

void Heal::Update()
{
	m_collision->SetPosition(m_position);
}

void Heal::Draw(int graphHandle)
{
	m_collision->DebugDraw();
}

Vector2 Heal::GetCollisionCenterPos() const
{
	Vector2 centerPos = m_collision->GetPosition();
	return Vector2();
}
