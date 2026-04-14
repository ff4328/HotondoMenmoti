#include "LotteryPusive.h"
#include "../Utility/Color.h"
#include "../Utility/Input.h"
#include <random>
#include <DxLib.h>

#include "WeaponManager.h"
#include "PlayerStatus.h"

namespace
{
	const char* const kGHandle[] = {"Resource\\Item\\AttackRange.png",
									 "Resource\\Item\\AttackSpeed.png",
									 "Resource\\Item\\Heal.png",
									 "Resource\\Item\\LimitBreak.png"};
}

LotteryPusive::LotteryPusive() :
	slot{},
	m_PassiveGraph{},
	m_selectNum(-1),
	weaponMgr(),
	pPlayerStatus()
{
}

LotteryPusive::LotteryPusive(WeaponManager* weaponMgr, PlayerStatus* playerStatus):
	slot{}, 
	m_PassiveGraph{ -1 },
	m_selectNum(0),
	weaponMgr(weaponMgr),
	pPlayerStatus(playerStatus)
{
	for (auto& e : m_PassiveGraph)
		m_PassiveGraph[e] = 0;
}


void LotteryPusive::RandomLottery()
{
	for (int i = 0; i < 3; i++)
	{
		slot[i] = GetRand(static_cast<int>(Pusive::MAXPUSIVE) - 1);
	}
}

void LotteryPusive::SelectPassive(int v)
{
	if (v == static_cast<int>(Pusive::ATTACKRANGE))
	{
		printfDx("ssssssssssssss");
		weaponMgr->AddAttackRange();
	}
	else if (v == static_cast<int>(Pusive::ATTACKSPEED))
	{
		weaponMgr->AddAttackSpeed();
	}
	else if (v == static_cast<int>(Pusive::MAXHPUP))
	{
		pPlayerStatus->AddMaxHP();
	}
	else if (v == static_cast<int>(Pusive::MOVESPEED))
	{
		pPlayerStatus->AddSpeed();
	}
}

void LotteryPusive::Init()
{
	for (int i = 0; i < 4; i++)
	{
		m_PassiveGraph[i] = LoadGraph(kGHandle[i]);
	}
}

void LotteryPusive::End()
{
}

void LotteryPusive::Update()
{
	static bool prevLeft = (CheckHitKey(KEY_INPUT_LEFT) == 1);
	static bool prevRight = (CheckHitKey(KEY_INPUT_RIGHT) == 1);
	static bool prevEnter = (CheckHitKey(KEY_INPUT_RETURN) == 1);

	bool nowLeft = (CheckHitKey(KEY_INPUT_LEFT) == 1);
	bool nowRight = (CheckHitKey(KEY_INPUT_RIGHT) == 1);
	bool nowEnter = (CheckHitKey(KEY_INPUT_RETURN) == 1);



	if (nowLeft&&!prevLeft)
	{
		printfDx("A‚ª‰Ÿ‚³‚ê‚½");
		m_selectNum -= 1;
		if (m_selectNum < 0)
			m_selectNum = 2;
	}
	else if (nowRight&&!prevRight)
	{
		m_selectNum += 1;
		if (m_selectNum > 2)
			m_selectNum = 0;
	}
	else if (nowEnter &&!prevEnter)
	{
		SelectPassive(slot[m_selectNum]);
	}
	else if ((nowRight && !prevRight)&& (nowLeft && !prevLeft))
	{
	}

	prevLeft = nowLeft;
	prevRight = nowRight;
	prevEnter = nowEnter;
}

void LotteryPusive::Draw()
{
	printfDx("\n");
	for (int i = 0; i < 3; i++)
	{
		printfDx("Slot%d:%d\n", i, slot[i]);
	}

	switch (m_selectNum)
	{
	case 0:
		DrawBox(195, 245, 305, 355, Color::kRed, false);
		DrawBox(345, 245, 455, 355, Color::kCyan, false);
		DrawBox(495, 245, 605, 355, Color::kCyan, false);
		break;
	case 1:
		DrawBox(195, 245, 305, 355, Color::kCyan, false);
		DrawBox(345, 245, 455, 355, Color::kRed, false);
		DrawBox(495, 245, 605, 355, Color::kCyan, false);
		break;
	case 2:
		DrawBox(195, 245, 305, 355, Color::kCyan, false);
		DrawBox(345, 245, 455, 355, Color::kCyan, false);
		DrawBox(495, 245, 605, 355, Color::kRed, false);
		break;
	default:
		DrawBox(195, 245, 305, 355, Color::kCyan, false);
		DrawBox(345, 245, 455, 355, Color::kCyan, false);
		DrawBox(495, 245, 605, 355, Color::kCyan, false);
		break;
	}

	DrawExtendGraph(200,250,300,350,m_PassiveGraph[slot[0]],true);
	DrawExtendGraph(350,250,450,350,m_PassiveGraph[slot[1]],true);
	DrawExtendGraph(500,250,600,350,m_PassiveGraph[slot[2]],true);
}