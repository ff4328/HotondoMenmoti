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
	isDown(true),
	m_position(position),
	m_graphHandleMagnet(-1),
	m_collision(nullptr)
{
	m_collision = std::make_unique<Collision>();
}

void Magnet::Init()
{
	m_position = Vector2(700.0f, 5.0f);
	m_graphHandleMagnet = LoadGraph(kItemGet);
}

void Magnet::End()
{

	DeleteGraph(m_graphHandleMagnet);
}

void Magnet::Update()
{
}

void Magnet::Draw()
{
	if (!(isDown))return;
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
void Magnet::Destroy()
{
	DeleteGraph(m_graphHandleMagnet);
	m_graphHandleMagnet = -1;
	isDown = false;
}