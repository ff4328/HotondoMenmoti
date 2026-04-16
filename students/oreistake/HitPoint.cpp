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
	// 引数の値をhpから減算
	m_hp -= value;

	// 0以下になったら0にする
	if (m_hp <= 0) m_hp = 0;
}

void HitPoint::Heal(int value)
{
	// 引数の値をhpから加算
	m_hp += value;

	// 最大HPを超えていないかチェック
	if (m_hp > m_hpMax) m_hp = m_hpMax;
}

bool HitPoint::IsDead()
{
	// hpの値が0以下ならtrueを返す
	if (m_hp <= 0) return true;

	// そうじゃなければfalseを返す
	return false;

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
