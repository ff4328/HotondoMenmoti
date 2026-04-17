#include "HitPoint.h"

HitPoint::HitPoint():
	m_posX(),
	m_posY(),
	m_gaugePosX(),
	m_gaugePosY(),
	m_hp(),
	m_hpMax(),
	m_pPlayerMove(nullptr)
{
	
}

void HitPoint::Init()
{

}

void HitPoint::Update()
{

}

void HitPoint::Draw()
{

}

void HitPoint::Finalize()
{

}

void HitPoint::DebugShow()
{

}

void HitPoint::Damage(int value)
{
	// ˆø”‚Ì’l‚ğhp‚©‚çŒ¸Z
	m_hp -= value;

	// 0ˆÈ‰º‚É‚È‚Á‚½‚ç0‚É‚·‚é
	if (m_hp <= 0) m_hp = 0;
}

void HitPoint::Heal(int value)
{
	
}

//bool HitPoint::IsDead()
//{
//	
//}

void HitPoint::SetPosition(float _posX, float _posY)
{

}

void HitPoint::SetHPMax(int value)
{
	m_hpMax = value;
	m_hp = m_hpMax;
}
