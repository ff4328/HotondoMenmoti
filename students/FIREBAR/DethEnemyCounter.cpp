#include "DethEnemyCounter.h"
#include "../Utility/Color.h"
#include "DxLib.h"

#include <string>
#include <vector>
#include <iostream>

namespace
{
	const char* const kGraphPath = "Resource\\image\\Skull.png";
}

DeathEnemyCounter::DeathEnemyCounter():
	m_gHandle(-1),
	m_enemyCount(0)
{
}

void DeathEnemyCounter::Init()
{
	m_gHandle = LoadGraph(kGraphPath);
	m_enemyCount = 0;
}

void DeathEnemyCounter::End()
{
}

void DeathEnemyCounter::Update()
{
}

void DeathEnemyCounter::Draw()
{
	DrawBox(700,50,790,80,Color::kBlack,true);
	DrawBox(700,50,790,80,Color::kWhite,false);

	std::string str = std::to_string(m_enemyCount);
	int width = GetDrawStringWidth(str.c_str(), str.length());

	DrawString(785 - width, 58, str.c_str(), Color::kWhite);
	DrawExtendGraph(700, 48, 730, 78, m_gHandle, true);
}

void DeathEnemyCounter::CountUP()
{
	m_enemyCount++;
}
