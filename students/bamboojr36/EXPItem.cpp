#include "EXPItem.h"
#include "Collision.h"
#include "Vector2.h"
#include<memory>
#include "DxLib.h"

namespace
{
	constexpr float kEXPItemScale = 1.0f;
	const char* const kItemEXP = ".\\Resource\\Item\\EXP.png";
}

EXPItem::EXPItem(Vector2 position) :
	m_position(),
	m_graphHandleEXPItem(-1),
	m_collision(nullptr)
{
	m_collision = std::make_unique<Collision>();
	m_position = position;
}

void EXPItem::Init()
{
	m_position = Vector2(1.0f, 1.0f);
	m_graphHandleEXPItem = LoadGraph(kItemEXP);
}

void EXPItem::End()
{
	DeleteGraph(m_graphHandleEXPItem);
}

void EXPItem::Update()
{

	if (CheckHitKey(KEY_INPUT_I) == 1) {
		m_position.y -= 1.0f;
	}
	if (CheckHitKey(KEY_INPUT_J) == 1) {
		m_position.x -= 1.0f;
	}
	if (CheckHitKey(KEY_INPUT_K) == 1) {
		m_position.y += 1.0f;
	}
	if (CheckHitKey(KEY_INPUT_L) == 1) {
		m_position.x += 1.0f;
	}
}

void EXPItem::Draw()
{
	DrawBox(m_position.x, m_position.y,
		m_position.x + 10, m_position.y + 10,
		GetColor(255, 0, 0), FALSE);

	DrawExtendGraph(
		m_position.x, m_position.y,
		m_position.x + 10, m_position.y + 10,
		m_graphHandleEXPItem, TRUE);

	printfDx("m_position.x = %f\n", m_position.x);
	printfDx("m_position.y = %f\n", m_position.y);

}

Rect EXPItem::GetRect() {
	Rect myRect = {
		(m_position.x ),
		(m_position.y ),
		(m_position.x +10),
		(m_position.y +10),
	};
	return myRect;
}