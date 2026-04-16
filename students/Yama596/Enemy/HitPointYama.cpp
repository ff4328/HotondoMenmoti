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

}

void HitPointYama::Damage(int value)
{

	// 引数の値をhpから減算
	m_hp -= value;

	// 0以下になったら0にする
	if (m_hp <= 0) m_hp = 0;

}

void HitPointYama::Heal(int value)
{

	// 引数の値をhpから加算
	m_hp += value;

	// 最大HPを超えていないかチェック
	if (m_hp > m_hpMax) m_hp = m_hpMax;

}

bool HitPointYama::IsDead()
{

	// hpの値が0以下ならtrueを返す
	if (m_hp <= 0) return true;

	// そうじゃなければfalseを返す
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
