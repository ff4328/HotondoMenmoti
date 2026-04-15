#include "Magnet.h"
#include "Collision.h"
#include "Vector2.h"
#include<memory>
#include "DxLib.h"

namespace
{
	constexpr float kHealScale = 1.0f;
	const char* const kItemGet = ".\\Resource\\Item\\Magnet.png";
}

Magnet::Magnet(Vector2 position) :
	m_position(position),
	m_graphHandleMagnet(-1),
	m_collision(nullptr)
{
	m_collision = std::make_unique<Collision>();
}

void Magnet::Init()
{
	m_position = Vector2(1.0f, 1.0f);
	m_graphHandleMagnet = LoadGraph(kItemGet);
}

void Magnet::End()
{

	DeleteGraph(m_graphHandleMagnet);
}

void Magnet::Update()
{
	if (CheckHitKey(KEY_INPUT_T) == 1) {
		m_position.y -= 1.0f;
	}
	if (CheckHitKey(KEY_INPUT_F) == 1) {
		m_position.x -= 1.0f;
	}
	if (CheckHitKey(KEY_INPUT_G) == 1) {
		m_position.y += 1.0f;
	}
	if (CheckHitKey(KEY_INPUT_H) == 1) {
		m_position.x += 1.0f;
	}
}

void Magnet::Draw()
{
	DrawBox(m_position.x+13, m_position.y+13,
		m_position.x + 40, m_position.y + 40,
		GetColor(255, 0, 0), false);

	DrawExtendGraph(
		m_position.x, m_position.y,
		m_position.x + 50, m_position.y + 50,
		m_graphHandleMagnet, TRUE);
}

Rect Magnet::GetCheckRrect() {
	Rect myRect = {
			(m_position.x+13),
			(m_position.y+13),
			(m_position.x + 40),
			(m_position.y + 40),
	};
	return myRect;
}