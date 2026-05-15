#include "HitPointYama.h"
#include "DxLib.h"

HitPointYama::HitPointYama() :
	m_posX(),
	m_posY(),
	m_gaugePosX(),
	m_gaugePosY(),
	m_hp(0),
	m_hpMax(0),
	m_pPlayerMove(nullptr)
{

}

void HitPointYama::Damage(int value)
{

	// ˆø”‚Ì’l‚ğhp‚©‚çŒ¸Z
	m_hp -= value;

	// 0ˆÈ‰º‚É‚È‚Á‚½‚ç0‚É‚·‚é
	if (m_hp <= 0) m_hp = 0;

}

bool HitPointYama::IsDead()
{

	// hp‚Ì’l‚ª0ˆÈ‰º‚È‚çtrue‚ğ•Ô‚·
	if (m_hp <= 0) return true;

	// ‚»‚¤‚¶‚á‚È‚¯‚ê‚Îfalse‚ğ•Ô‚·
	return false;

}

void HitPointYama::SetHPMax(int value)
{

	m_hpMax = value;

	m_hp = m_hpMax;

}
