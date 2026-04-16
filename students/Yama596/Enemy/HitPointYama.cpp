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

void HitPointYama::Init()
{

}

void HitPointYama::Update()
{

}

void HitPointYama::Draw()
{

}

void HitPointYama::Finalize()
{

}

void HitPointYama::DebugShow()
{
	printfDx("åªç›ÇÃHP : %d\n", m_hp);
}

void HitPointYama::Damage(int value)
{

	// à¯êîÇÃílÇhpÇ©ÇÁå∏éZ
	m_hp -= value;

	// 0à»â∫Ç…Ç»Ç¡ÇΩÇÁ0Ç…Ç∑ÇÈ
	if (m_hp <= 0) m_hp = 0;

}

void HitPointYama::Heal(int value)
{

}

bool HitPointYama::IsDead()
{

	// hpÇÃílÇ™0à»â∫Ç»ÇÁtrueÇï‘Ç∑
	if (m_hp <= 0) return true;

	// ÇªÇ§Ç∂Ç·Ç»ÇØÇÍÇŒfalseÇï‘Ç∑
	return false;

}

void HitPointYama::SetPosition(float _posX, float _posY)
{

}

void HitPointYama::SetHPMax(int value)
{

	m_hpMax = value;
	m_hp = m_hpMax;

}
