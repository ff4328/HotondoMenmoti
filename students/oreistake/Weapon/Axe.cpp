#include "Axe.h"

#include "../students/bamboojr36/Collision.h"
#include "../students/bamboojr36/Vector2.h"
bool AAA = true;

namespace
{
	const char* const kGraphPath = ".\\Resource\\image\\Axe.png";
}

Axe::Axe():
	m_graphHandle(-1),
	m_range(0),
	m_coolTime(),
	m_appearTime(),
	m_angle(),
	m_pCollision(nullptr)
{
	m_pCollision = std::make_unique<Collision>();
}

Axe::Axe(std::string name, float damage, float range, float attackRange, int coolTime, int weaponNum, Vector2 playerPos)
{
}

void Axe::Init() {
	position = Vector2(400.0f, 200.0f);
	m_graphHandle = LoadGraph(kGraphPath);
}

void Axe::End() {
	DeleteGraph(m_graphHandle);
}

void Axe::Update() {
	if (AAA) {
	position.x += 1;
	position.y -= 2;
	}
	if (position.x >= 215 && position.y <= 100){
		position.x += 0;
		position.y += 0;

		AAA = false;
	}
	if (!AAA) {
		position.x += 1;
		position.y += 5;
	}
	if (position.y >= 300) {
		DeleteGraph(m_graphHandle);
	}
}

void Axe::Draw() {
	DrawBox(position.x,position.y,
		position.x + 40, position.y + 40,
		GetColor(255, 0, 0), FALSE);

	DrawExtendGraph(
		position.x, position.y,
		position.x + 40, position.y + 40,
		m_graphHandle, TRUE);

	printfDx("X:%f\n", position.x);
	printfDx("Y:%f\n", position.y);
}

void Axe::DebugDraw() {

}

void Axe::UpdateAxe()
{
}

void Axe::DrawAxe()
{
}
