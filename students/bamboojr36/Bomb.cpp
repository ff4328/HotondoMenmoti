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
	m_position = Vector2(1.0f, 1.0f);
	m_graphHandleBomb = LoadGraph(kItembomb);
}

void Bomb::End()
{
	DeleteGraph(m_graphHandleBomb);
}


void Bomb::Update()
{
	if (CheckHitKey(KEY_INPUT_UP) == 1) {
		m_position.y -= 1.0f;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) == 1) {
		m_position.x -= 1.0f;
	}
	if (CheckHitKey(KEY_INPUT_DOWN) == 1) {
		m_position.y += 1.0f;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {
		m_position.x += 1.0f;
	}
}

void Bomb::Draw()
{
	DrawBox(m_position.x, m_position.y,
		m_position.x + 50, m_position.y + 50,
		GetColor(255, 0, 0), FALSE);

	DrawExtendGraph(
		m_position.x, m_position.y,
		m_position.x + 50, m_position.y + 50,
		m_graphHandleBomb, TRUE);

	printfDx("m_position.x = %f\n", m_position.x);
	printfDx("m_position.y = %f\n", m_position.y);	

}

Rect Bomb::GetCheckRect() {
	int margin = 5;
	Rect myRect = {
		(m_position.x - 50 / 2) ,
		(m_position.y - 50 / 2),
		(m_position.x + 50 / 2),
		(m_position.y + 50 / 2) ,
	};
	return myRect;
}