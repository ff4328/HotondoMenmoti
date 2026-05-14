#include "LotteryPusive.h"
#include "../Utility/Color.h"
#include "../Utility/Input.h"
#include <random>
#include <DxLib.h>

#include "WeaponManager.h"
#include "PlayerStatus.h"
#include "../students/mcd6752Tuyoshi/ExpBar/EXPBar.h"
#include "../System/SoundManager.h"

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
		"Resource\\image\\AxeSlot.png",
		"Resource\\image\\ArrowSlot.png",
		"Resource\\image\\SwordSlot.png",
		"Resource\\image\\MagicBottleSlot.png",
		"Resource\\Item\\Heal.png",
		"Resource\\image\\LevelUp.png" 
	};

	bool kflag = false;

	const int kInterval = 150;
	
	int kgameCount = 0;

}

LotteryPassive::LotteryPassive() :
	slot{},
	m_PassiveGraph{},
	m_selectNum(-1),
	m_oneShotoFlag(false),
	m_passiveLevel{},
	weaponMgr(),
	pPlayerStatus(),
	m_pEXPBar(), 
	m_pShowChoiceManager()
{
}

LotteryPassive::LotteryPassive(WeaponStatus* weaponMgr, PlayerStatus* playerStatus, EXPBar* expBar, ShowChoiceManager*pShowChoiceManager):
	slot{}, 
	m_PassiveGraph{ -1 },
	m_selectNum(0),
	m_oneShotoFlag(false),
	m_passiveLevel{},
	weaponMgr(weaponMgr),
	pPlayerStatus(playerStatus),
	m_pEXPBar(expBar),
	m_pShowChoiceManager(pShowChoiceManager)
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

	if (slot[0] == slot[1] && slot[1] == slot[2])
	{
		SoundManager::GetInstance().PlaySe(Sound::SE::Kansei_to_Hakusyu);
		kflag = true;
	}
	else
	{
		SoundManager::GetInstance().PlaySe(Sound::SE::LevelUp);
	}
	m_oneShotoFlag = !m_oneShotoFlag;
}

void LotteryPassive::SelectPassive(int v)
{
	if (v == static_cast<int>(Passive::ATTACKRANGE))
	{
		m_passiveLevel[static_cast<int>(Passive::ATTACKRANGE)]+=1;

		if (m_passiveLevel[static_cast<int>(Passive::ATTACKRANGE)] > 5)
		{
			m_passiveLevel[static_cast<int>(Passive::ATTACKRANGE)] = 5;
			return;
		}
		weaponMgr->AddAttackRange();

		m_pShowChoiceManager->SetChoicePassives(v, m_PassiveGraph[0], m_passiveLevel[static_cast<int>(Passive::ATTACKRANGE)]);
	}
	else if (v == static_cast<int>(Passive::ATTACKSPEED))
	{
		m_passiveLevel[static_cast<int>(Passive::ATTACKSPEED)]+=1;

		if (m_passiveLevel[static_cast<int>(Passive::ATTACKSPEED)] > 5)
		{
			m_passiveLevel[static_cast<int>(Passive::ATTACKSPEED)] = 5;
			return;
		}

		weaponMgr->AddAttackSpeed();

		m_pShowChoiceManager->SetChoicePassives(v, m_PassiveGraph[1], m_passiveLevel[static_cast<int>(Passive::ATTACKSPEED)]);
	}
	else if (v == static_cast<int>(Passive::MAXHPUP))
	{
		m_passiveLevel[static_cast<int>(Passive::MAXHPUP)]+=1;

		if (m_passiveLevel[static_cast<int>(Passive::MAXHPUP)] > 5)
		{
			m_passiveLevel[static_cast<int>(Passive::MAXHPUP)] = 5;
			return;
		}

		pPlayerStatus->AddMaxHP();

		m_pShowChoiceManager->SetChoicePassives(v, m_PassiveGraph[2], m_passiveLevel[static_cast<int>(Passive::MAXHPUP)]);
	}
	else if (v == static_cast<int>(Passive::MOVESPEED))
	{
		m_passiveLevel[static_cast<int>(Passive::MOVESPEED)]+=1;

		if (m_passiveLevel[static_cast<int>(Passive::MOVESPEED)] > 5)
		{
			m_passiveLevel[static_cast<int>(Passive::MOVESPEED)] = 5;
			return;
		}

		pPlayerStatus->AddSpeed();

		m_pShowChoiceManager->SetChoicePassives(v, m_PassiveGraph[3], m_passiveLevel[static_cast<int>(Passive::MOVESPEED)]);
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////
	else if (v == static_cast<int>(Passive::ARROW))
	{
		if (weaponMgr->GetAddWeapons(0))
		{
			m_passiveLevel[static_cast<int>(Passive::ARROW)]++;
		}

		if (m_passiveLevel[static_cast<int>(Passive::ARROW)] > 5)
		{
			m_passiveLevel[static_cast<int>(Passive::ARROW)] = 5;
			return;
		}

		if (weaponMgr->GetAddWeapons(0))
		{
			weaponMgr->AddAttack(0);
		}

		m_pShowChoiceManager->SetChoiceWeapons(v,m_PassiveGraph[5], m_passiveLevel[static_cast<int>(Passive::ARROW)]);

		weaponMgr->SetAddWeapons(0, true);
	}
	else if (v == static_cast<int>(Passive::KATANA))
	{
		m_passiveLevel[static_cast<int>(Passive::KATANA)]++;


		if (m_passiveLevel[static_cast<int>(Passive::KATANA)] > 5)
		{
			m_passiveLevel[static_cast<int>(Passive::KATANA)] = 5;
			return;
		}

		weaponMgr->AddAttack(1);

		m_pShowChoiceManager->SetChoiceWeapons(v, m_PassiveGraph[6], m_passiveLevel[static_cast<int>(Passive::KATANA)]);
	}
	else if (v == static_cast<int>(Passive::AXE))
	{
		if (weaponMgr->GetAddWeapons(1))
			m_passiveLevel[static_cast<int>(Passive::AXE)]++;

		if (m_passiveLevel[static_cast<int>(Passive::AXE)] > 5)
		{
			m_passiveLevel[static_cast<int>(Passive::AXE)] = 5;
			return;
		}

		if (weaponMgr->GetAddWeapons(1))
			weaponMgr->AddAttack(2);

		m_pShowChoiceManager->SetChoiceWeapons(v, m_PassiveGraph[4], m_passiveLevel[static_cast<int>(Passive::AXE)]);

		weaponMgr->SetAddWeapons(1, true);
	}
	else if (v == static_cast<int>(Passive::MAGIC))
	{
		if (weaponMgr->GetAddWeapons(2))
			m_passiveLevel[static_cast<int>(Passive::MAGIC)]++;

		if (m_passiveLevel[static_cast<int>(Passive::MAGIC)] > 5)
		{
			m_passiveLevel[static_cast<int>(Passive::MAGIC)] = 5;
			return;
		}

		if (weaponMgr->GetAddWeapons(2))
			weaponMgr->AddAttack(3);

		m_pShowChoiceManager->SetChoiceWeapons(v, m_PassiveGraph[7], m_passiveLevel[static_cast<int>(Passive::MAGIC)]);

		weaponMgr->SetAddWeapons(2, true);
	}
	else if (v == static_cast<int>(Passive::HPHEAL)-1)
	{
		pPlayerStatus->HealHP();
		SoundManager::GetInstance().PlaySe(Sound::SE::Gauge_Recovery01);
	}
}

void LotteryPassive::Init()
{
	for (int i = 0; i < MAX_PASSIVE_NUM; i++)
	{
		m_PassiveGraph[i] = LoadGraph(kGHandle[i]);
	}
	m_pShowChoiceManager->SetChoiceWeapons(static_cast<int>(Passive::KATANA), m_PassiveGraph[6], m_passiveLevel[static_cast<int>(Passive::KATANA)]);
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

	if (kflag)
	{
		kgameCount++;

		if (kgameCount > kInterval)
		{
			SelectPassive(slot[0]);
			SelectPassive(slot[1]);
			SelectPassive(slot[2]);
			m_oneShotoFlag = false;
			m_pEXPBar->SetLevelFlag(false);

			SoundManager::GetInstance().PlaySe(Sound::SE::Kingaku_hyouji);

			kgameCount = 0;

			kflag = false;
		}
	}

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
		m_selectNum -= 1;
		if (m_selectNum < 0)
			m_selectNum = 2;

		SoundManager::GetInstance().PlaySe(Sound::SE::DecisionSE);
	}
	else if ((nowRight && !prevRight)|| (nowD && !prevD))
	{
		m_selectNum += 1;
		if (m_selectNum > 2)
			m_selectNum = 0;

		SoundManager::GetInstance().PlaySe(Sound::SE::DecisionSE);
	}
	else if (nowEnter &&!prevEnter &&!kflag)
	{
		SelectPassive(slot[m_selectNum]);
		m_oneShotoFlag = false;
		m_pEXPBar->SetLevelFlag(false);

		int d = GetRand(100);

		if (d <= 5)
		{
			PlaySound(".\\students\\FIREBAR\\Men Whoa!.mp3", DX_PLAYTYPE_BACK);
		}
		else if (d <= 10)
		{
			PlaySound(".\\students\\FIREBAR\\That's too bad.mp3", DX_PLAYTYPE_BACK);
		}
		else if (d <= 15)
		{
			PlaySound(".\\students\\FIREBAR\\chesto.mp3", DX_PLAYTYPE_BACK);
		}
		else
		{
			SoundManager::GetInstance().PlaySe(Sound::SE::Kingaku_hyouji);
		}
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
	RandomLottery();

	DrawExtendGraph(150, 75, 650, 525, m_PassiveGraph[MAX_PASSIVE_NUM-1], true);

	switch (m_selectNum)
	{
	case 0:
		DrawTriangle(170, 300, 176, 297, 176, 303, Color::kYellow, true);
		DrawTriangle(326, 300, 320, 297, 320, 303, Color::kYellow, true);

		DrawBox(195, 245, 305, 355, Color::kYellow, false);
		DrawBox(197, 247, 303, 353, Color::kYellow, false);
		break;
	case 1:
		DrawTriangle(320, 300, 326, 297, 326, 303, Color::kYellow, true);
		DrawTriangle(476, 300, 470, 297, 470, 303, Color::kYellow, true);
		
		DrawBox(345, 245, 455, 355, Color::kYellow, false);
		DrawBox(347, 247, 453, 353, Color::kYellow, false);
		break;
	case 2:
		DrawTriangle(470, 300, 476, 297, 476, 303, Color::kYellow, true);
		DrawTriangle(634, 300, 628, 297, 628, 303, Color::kYellow, true);

		DrawBox(495, 245, 605, 355, Color::kYellow, false);
		DrawBox(497, 247, 603, 353, Color::kYellow, false);
		break;
	default:
		break;
	}

	if (slot[m_selectNum] == static_cast<int>(Passive::ATTACKRANGE))
	{
		DrawString(340, 370, "　 攻撃範囲↑　", Color::kBlack);
	}
	else if (slot[m_selectNum] == static_cast<int>(Passive::ATTACKSPEED))
	{
		DrawString(340, 370, " クールタイム↓", Color::kBlack);
	}
	else if (slot[m_selectNum] == static_cast<int>(Passive::MAXHPUP))
	{
		DrawString(340, 370, "　　最大HP↑　 ", Color::kBlack);
	}
	else if (slot[m_selectNum] == static_cast<int>(Passive::MOVESPEED))
	{
		DrawString(340, 370, "　 移動速度↑　", Color::kBlack);
	}
	else if (slot[m_selectNum] == static_cast<int>(Passive::AXE))
	{
		DrawString(340, 370, "　　　 斧　　　", Color::kBlack);
	}
	else if (slot[m_selectNum] == static_cast<int>(Passive::ARROW))
	{
		DrawString(340, 370, "　　　 矢　　　", Color::kBlack);
	}
	else if (slot[m_selectNum] == static_cast<int>(Passive::KATANA))
	{
		DrawString(340, 370, "　　　 刀　　　", Color::kBlack);
	}
	else if (slot[m_selectNum] == static_cast<int>(Passive::MAGIC))
	{
		DrawString(340, 370, "　 　魔法瓶　　", Color::kBlack);
	}
	else if (slot[m_selectNum] == static_cast<int>(Passive::HPHEAL) - 1)
	{
		DrawString(340, 370, "　　 HP回復　　", Color::kBlack);
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