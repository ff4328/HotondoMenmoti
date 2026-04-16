#include "../students/Yama596/Enemy/HitPoint.h"
#include "DxLib.h"

HitPoint::HitPoint():
	m_posX(),
	m_posY(),
	m_gaugePosX(),
	m_gaugePosY(),
	m_hp(0),
	m_hpMax(0),
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
	printfDx("Œ»İ‚ÌHP : %d\n", m_hp);
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

bool HitPoint::IsDead()
{

	// hp‚Ì’l‚ª0ˆÈ‰º‚È‚çtrue‚ğ•Ô‚·
	if (m_hp <= 0) return true;

	// ‚»‚¤‚¶‚á‚È‚¯‚ê‚Îfalse‚ğ•Ô‚·
	return false;

}

void HitPoint::SetPosition(float _posX, float _posY)
{

}

void HitPoint::SetHPMax(int value)
{

	m_hpMax = value;
	m_hp = m_hpMax;

}
