#include "Arrow.h"
#include <DxLib.h>

#include "../students/bamboojr36/Collision.h"
#include "../students/bamboojr36/Vector2.h"
#include "../students/bamboojr36/Random.h"
#include"../students/oreistake/Player.h"



namespace
{

	const char* const kGraphPath = ".\\Resource\\image\\Arrow.png";

	// •Ší–¼‚Ì‹K’è’l
	const char* const kInitName = "arrow";

	// —^ƒ_ƒ[ƒW‚Ì‹K’è’l
	constexpr float kDamege = 10.0f;

	// ŽË’ö‚Ì‹K’è’l
	constexpr float kRange = 40.0f;

	// UŒ‚”ÍˆÍ‚Ì‹K’è’l
	constexpr float kAttackRange = 2.0f;

	// •Šíƒiƒ“ƒo[‚Ì‹K’è’l
	constexpr int kWeaponNumber = 1;

	// ƒN[ƒ‹ƒ^ƒCƒ€‚Ì‹K’è’l
	constexpr int kCoolTime = 150;

}


Arrow::Arrow():
	m_graphHandle(),
	m_name(kInitName),
	m_damage(kDamege),
	m_range(kRange),
	m_attackRange(kAttackRange),
	m_coolTime(kCoolTime),
	m_weaponNum(kWeaponNumber),
	m_appearTime(0),
	m_angle(0.0f),
	m_radius(0.0f),
	m_startPosX(m_pPlayerMove->GetModelPos().x),
	m_startPosY(m_pPlayerMove->GetModelPos().y),
	m_pPlayerMove(nullptr)
{

	m_pPlayerMove = new PlayerMove();

}
Arrow::Arrow(
	std::string name,
	float damage,
	float range,
	float attackRange,
	int coolTime,
	int weaponNum,
	Vector2 playerPos,
	PlayerMove* pPlayerMove):
	m_graphHandle(),
	m_name(kInitName),
	m_damage(kDamege),
	m_range(kRange),
	m_attackRange(kAttackRange),
	m_coolTime(kCoolTime),
	m_weaponNum(kWeaponNumber),
	m_appearTime(0),
	m_angle(0.0f),
	m_radius(0.0f),
	m_startPosX(playerPos.x),
	m_startPosY(playerPos.y),
	m_pPlayerMove(pPlayerMove)
{

}
void Arrow::Init()
{
	m_graphHandle = LoadGraph(kGraphPath);
}

void Arrow::End()
{

}

void Arrow::Update()
{
	m_radius += 1.0f;
	//m_angle -= 100.0f;
	if (m_radius <= 1)
	{

		m_angle = MyRandom::Int(0, 360);
		m_startPosX = m_pPlayerMove->GetModelPos().x + (int)(cosf(m_angle) * m_radius);
		m_startPosY = m_pPlayerMove->GetModelPos().y + (int)(sinf(m_angle) * m_radius);

		m_currentPos = m_pPlayerMove->GetModelPos();
	}
	else
	{

		m_startPosX = m_currentPos.x + (int)(cosf(m_angle) * m_radius);
		m_startPosY = m_currentPos.y + (int)(sinf(m_angle) * m_radius);

	}
	
}

void Arrow::Draw()
{
	//printfDx("jkdaksangle : %f\n",m_angle);
	DrawRotaGraph(m_startPosX, m_startPosY, 1,m_angle, m_graphHandle, TRUE, false);
	/*DrawGraph(m_startPosX, m_startPosY,m_graphHandle,true);*/

	DrawBox(GetCheckRect().left, GetCheckRect().top, GetCheckRect().right, GetCheckRect().bottom, GetColor(255, 255, 255), false);


}

Rect Arrow::GetCheckRect()
{
	Rect myRect = {
		(m_startPosX - 10),
		(m_startPosY - 10),
		(m_startPosX + 10),
		(m_startPosY + 10),
	};

	return myRect;
}

