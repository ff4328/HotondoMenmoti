#include "Heal.h"
#include "Collision.h"
#include "Vector2.h"
#include<memory>
#include "DxLib.h"


namespace 
{
	constexpr float kHealScale = 1.0f;
	const char* const kItemHeal = ".\\Resource\\Item\\Heal.png";
}

Heal::Heal(Vector2 position):
	isDown(true),
	m_position(),
	m_graphHandleHeal(-1),
	m_collision(nullptr)
{
	m_collision = std::make_unique<Collision>();
	m_position = position;
}

void Heal::Init()
{
	m_position = Vector2(600.0f, 500.0f);
	m_graphHandleHeal = LoadGraph(kItemHeal);
}	

void Heal::End()
{
	DeleteGraph(m_graphHandleHeal);
}

void Heal::Update()
{
}

void Heal::Draw()
{
	if (!(isDown))return;
	DrawBox(m_position.x+10,m_position.y+15,
		m_position.x + 42, m_position.y + 35,
		GetColor(255, 0, 0), FALSE);

	DrawExtendGraph(
		m_position.x, m_position.y,
		m_position.x + 50, m_position.y + 50,
		m_graphHandleHeal, TRUE);
}

Rect Heal::GetRect() {
	Rect myRect = {
		(m_position.x+10),
		(m_position.y+15),
		(m_position.x + 42),
		(m_position.y + 35),
	};
	return myRect;
}
void Heal::Destroy()
{
	DeleteGraph(m_graphHandleHeal);
	m_graphHandleHeal = -1;
	isDown = false;
}