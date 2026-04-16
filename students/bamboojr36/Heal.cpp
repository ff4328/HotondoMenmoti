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
	DrawBox(m_position.x+10,m_position.y+15,
		m_position.x + 42, m_position.y + 35,
		GetColor(255, 0, 0), FALSE);

	DrawExtendGraph(
		m_position.x, m_position.y,
		m_position.x + 50, m_position.y + 50,
		m_graphHandleHeal, TRUE);

	printfDx("回復アイテムの座標 : %f, %f\n", m_position.x, m_position.y);
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