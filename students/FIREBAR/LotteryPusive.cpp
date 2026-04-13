#include "LotteryPusive.h"
#include <random>
#include <DxLib.h>

LotteryPusive::LotteryPusive()
{
	for (int i = 0; i < 3; i++)
	{
		slot[i] = 0;
	}
}

void LotteryPusive::RandomLottery()
{
	for (int i = 0; i < 3; i++)
	{
		slot[i] = GetRand(static_cast<int>(MAXPUSIVE));
	}
}

void LotteryPusive::Draw()
{
	for (int i = 0; i < 3; i++)
	{
		printfDx("Slot%d:%d\n", i, slot[i]);
	}
}