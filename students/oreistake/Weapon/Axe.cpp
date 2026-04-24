#include "Axe.h"

#include "../students/bamboojr36/Collision.h"
#include "../students/bamboojr36/Vector2.h"

#include "../Camera.h"
namespace
{
	const char* const kGraphPath = "Resource\\image\\Axe.png.png";

	float speedY = -5;
	constexpr float gravity = 0.3f;
}

Axe::Axe():
	m_graphHandle(-1),
	m_range(0),
	m_coolTime(),
	m_appearTime(),
	m_angle(),
	m_isAlive(false),
	m_pCamera(nullptr),
	m_pCollision(nullptr)
{
	m_pCollision = std::make_unique<Collision>();
}

Axe::Axe(std::string name, float damage, float range, float attackRange, int coolTime, int weaponNum, Vector2 playerPos):
	m_isAlive(false),
	position(playerPos),
	m_pCollision(nullptr)
{
	m_pCollision = std::make_unique<Collision>();
}

void Axe::Init() {
	position = Vector2(400.0f, 200.0f);
	m_graphHandle = LoadGraph(kGraphPath);
}

void Axe::End() {
	DeleteGraph(m_graphHandle);
}

void Axe::Update() {
	if (m_isAlive) {

		position.x += 3;
		position.y += speedY;
		speedY += gravity;
	}
	if (m_pCamera != nullptr) {

		UpdateAxe(m_pCamera);
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

	printfDx("X:%d\n", position.x);
	printfDx("Y:%d\n", position.y);
}

void Axe::DebugDraw() {

}

Rect Axe::GetRects()
{
	Rect myRect = {
		(position.x),
		(position.y),
		(position.x + 40),
		(position.y + 40),
	};
	return myRect;
}

void Axe::Spawn(Vector2 startPos)
{  
	m_isAlive = true; 
	position = startPos;
	speedY = -10;
	
}

void Axe::UpdateAxe(const Camera* pCamera)
{
	float margin = 64.0f;

	// ÉJÉÅÉâÇ™ë∂ç›Ç∑ÇÈèÍçáÇÃîªíË
	if (pCamera != nullptr) {
		if (position.x < pCamera->GetLeft() - margin ||
			position.x > pCamera->GetRight() + margin ||
			position.y > pCamera->GetBottom() + margin)
		{
			m_isAlive = false;
		}
	}
	else {


		m_isAlive = false;
	}

}

void Axe::DrawAxe()
{
}
