#include "LotteryPusive.h"
#include <random>
#include <DxLib.h>

namespace
{
	const char* const kGHandle[4] = {"Resource\\Item\\AttackRange.png","Resource\\Item\\AttackSpeed.png","Resource\\Item\\Heal.png","Resource\\Item\\LimitBreak.png"};
}

LotteryPusive::LotteryPusive():
	slot{},
	m_PassiveGraph{},
	pPassiveEffect(nullptr)
{
}

void LotteryPusive::RandomLottery()
{
	for (int i = 0; i < 3; i++)
	{
		slot[i] = GetRand(static_cast<int>(Pusive::MAXPUSIVE) - 1);
		DrawGraph((i + 1) * 200, 250, m_PassiveGraph[slot[i]], false);
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
	delete pPassiveEffect;
	pPassiveEffect = nullptr;
}

void LotteryPusive::Update()
{

}

void LotteryPusive::Draw()
{
	for (int i = 0; i < 3; i++)
	{
		printfDx("Slot%d:%d\n", i, slot[i]);
	}
}