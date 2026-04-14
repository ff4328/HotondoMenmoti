#include "Heal.h"
#include "Collision.h"
#include "Vector2.h"
#include<memory>
#include "DxLib.h"

namespace 
{
	constexpr float kHealScale = 1.0f;
}

Heal::Heal(Vector2 position):
	m_graphHandle(0),
	m_scale(kHealScale),
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
	m_collision->SetPosition(m_position);
}

void Heal::Draw(int graphHandle)
{
	m_collision->DebugDraw();
}

Vector2 Heal::GetCollisionCenterPos() const
{
	Vector2 centerPos = m_collision->GetPosition();
	return centerPos;
}