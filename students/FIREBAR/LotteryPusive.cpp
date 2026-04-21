#include "LotteryPusive.h"
#include "../Utility/Color.h"
#include "../Utility/Input.h"
#include <random>
#include <DxLib.h>

#include "WeaponManager.h"
#include "PlayerStatus.h"
#include "../students/mcd6752Tuyoshi/ExpBar/EXPBar.h"

const int MAX_PASSIVE_NUM = static_cast<int>(Passive::HPHEAL) + 1;

namespace
{
	//グラフデータ
	const char* const kGHandle[] = 
	{
		"Resource\\Item\\AttackRange.png",
		"Resource\\Item\\AttackSpeed.png",
		"Resource\\Item\\LimitBreak.png",
		"Resource\\Item\\MovementSpeed.png",
		"Resource\\Item\\Heal.png",
		"Resource\\image\\LevelUp.png" 
	};
}

LotteryPassive::LotteryPassive() :
	slot{},
	m_PassiveGraph{},
	m_selectNum(-1),
	m_oneShotoFlag(false),
	m_passiveLevel{},
	weaponMgr(),
	pPlayerStatus(),
	m_pEXPBar()
{
}

LotteryPassive::LotteryPassive(WeaponStatus* weaponMgr, PlayerStatus* playerStatus, EXPBar* expBar):
	slot{}, 
	m_PassiveGraph{ -1 },
	m_selectNum(0),
	m_oneShotoFlag(false),
	m_passiveLevel{},
	weaponMgr(weaponMgr),
	pPlayerStatus(playerStatus),
	m_pEXPBar(expBar)
{
	for (auto& e : m_passiveLevel)
		m_passiveLevel[e] = 0;

	for (auto& e : m_PassiveGraph)
		m_PassiveGraph[e] = 0;
}


void LotteryPassive::RandomLottery()
{
	if (m_oneShotoFlag)return;
	for (int i = 0; i < 3; i++)
	{
		slot[i] = GetRand(static_cast<int>(Passive::MAXPUSIVE) - 1);

		if (m_passiveLevel[slot[i]] == 5)
			slot[i] = static_cast<int>(Passive::HPHEAL) - 1;
	}
	m_oneShotoFlag = !m_oneShotoFlag;
}

void LotteryPassive::SelectPassive(int v)
{
	if (v == static_cast<int>(Passive::ATTACKRANGE))
	{
		m_passiveLevel[static_cast<int>(Passive::ATTACKRANGE)]++;
		weaponMgr->AddAttackRange();
	}
	else if (v == static_cast<int>(Passive::ATTACKSPEED))
	{
		m_passiveLevel[static_cast<int>(Passive::ATTACKSPEED)]++;
		weaponMgr->AddAttackSpeed();
	}
	else if (v == static_cast<int>(Passive::MAXHPUP))
	{
		m_passiveLevel[static_cast<int>(Passive::MAXHPUP)]++;
		pPlayerStatus->AddMaxHP();
	}
	else if (v == static_cast<int>(Passive::MOVESPEED))
	{
		m_passiveLevel[static_cast<int>(Passive::MOVESPEED)]++;
		pPlayerStatus->AddSpeed();
	}
	else if (v == static_cast<int>(Passive::HPHEAL)-1)
	{
		pPlayerStatus->HealHP();
	}
}

void LotteryPassive::Init()
{
	for (int i = 0; i < MAX_PASSIVE_NUM; i++)
	{
		m_PassiveGraph[i] = LoadGraph(kGHandle[i]);
	}
}

void LotteryPassive::End() const
{
	for (int i = 0; i < MAX_PASSIVE_NUM; i++)
	{
		DeleteGraph( m_PassiveGraph[i]);
	}
}

void LotteryPassive::Update()
{
	if (!m_pEXPBar->GetLevelFlag())return;

	static bool prevLeft = (CheckHitKey(KEY_INPUT_LEFT) == 1);
	static bool prevRight = (CheckHitKey(KEY_INPUT_RIGHT) == 1);
	static bool prevEnter = (CheckHitKey(KEY_INPUT_RETURN) == 1);
	static bool prevA = (CheckHitKey(KEY_INPUT_A) == 1);
	static bool prevD = (CheckHitKey(KEY_INPUT_D) == 1);

	bool nowLeft = (CheckHitKey(KEY_INPUT_LEFT) == 1);
	bool nowRight = (CheckHitKey(KEY_INPUT_RIGHT) == 1);
	bool nowEnter = (CheckHitKey(KEY_INPUT_RETURN) == 1);
	bool nowA = (CheckHitKey(KEY_INPUT_A) == 1);
	bool nowD = (CheckHitKey(KEY_INPUT_D) == 1);

	if ((nowLeft && !prevLeft)|| (nowA && !prevA))
	{
		//printfDx("Aが押された");
		m_selectNum -= 1;
		if (m_selectNum < 0)
			m_selectNum = 2;
	}
	else if ((nowRight && !prevRight)|| (nowD && !prevD))
	{
		m_selectNum += 1;
		if (m_selectNum > 2)
			m_selectNum = 0;
	}
	else if (nowEnter &&!prevEnter)
	{
		SelectPassive(slot[m_selectNum]);
		m_oneShotoFlag = false;
		m_pEXPBar->SetLevelFlag(false);
	}
	else if ((nowRight && !prevRight)&& (nowLeft && !prevLeft))
	{
	}

	prevLeft = nowLeft;
	prevRight = nowRight;
	prevEnter = nowEnter;
	prevA = nowA;
	prevD = nowD;
}

void LotteryPassive::Draw()
{
	//printfDx("\n");
	//for (int i = 0; i < 3; i++)
	//{
	//	printfDx("Slot%d:%d\n", i, slot[i]);
	//}

	RandomLottery();

	DrawExtendGraph(150, 75, 650, 525, m_PassiveGraph[MAX_PASSIVE_NUM-1], true);

	switch (m_selectNum)
	{
	case 0:
		DrawBox(195, 245, 305, 355, Color::kYellow, false);
		DrawBox(197, 247, 303, 353, Color::kYellow, false);
		break;
	case 1:
		DrawBox(345, 245, 455, 355, Color::kYellow, false);
		DrawBox(347, 247, 453, 353, Color::kYellow, false);
		break;
	case 2:
		DrawBox(495, 245, 605, 355, Color::kYellow, false);
		DrawBox(497, 247, 603, 353, Color::kYellow, false);
		break;
	default:
		break;
	}

	if (slot[m_selectNum] == static_cast<int>(Passive::ATTACKRANGE))
	{
		DrawString(340, 370, "　攻撃範囲↑", Color::kBlack);
	}
	else if (slot[m_selectNum] == static_cast<int>(Passive::ATTACKSPEED))
	{
		DrawString(340, 370, "クールタイム↓", Color::kBlack);
	}
	else if (slot[m_selectNum] == static_cast<int>(Passive::MAXHPUP))
	{
		DrawString(340, 370, "　　最大HP↑", Color::kBlack);
	}
	else if (slot[m_selectNum] == static_cast<int>(Passive::MOVESPEED))
	{
		DrawString(340, 370, "　 移動速度↑", Color::kBlack);
	}
	else if (slot[m_selectNum] == static_cast<int>(Passive::HPHEAL) - 1)
	{
		DrawString(340, 370, "　　HP回復", Color::kBlack);
	}

	DrawExtendGraph(200, 250, 300, 350, m_PassiveGraph[slot[0]], true);
	DrawExtendGraph(350, 250, 450, 350, m_PassiveGraph[slot[1]], true);
	DrawExtendGraph(500, 250, 600, 350, m_PassiveGraph[slot[2]], true);
}

bool LotteryPassive::ShowSlot()
{
	if (!m_pEXPBar->GetLevelFlag())
	{
		return false;
	}
	else
	{
		return true;
	}
}