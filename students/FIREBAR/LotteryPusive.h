#pragma once
#include "PassiveEffect.h"

enum class Pusive
{
	ATTACKRANGE,
	ATTACKSPEED,
	MAXHPUP,
	MOVESPEED,
	MAXPUSIVE,
};


class LotteryPusive
{
public:
	LotteryPusive();
	~LotteryPusive() = default;

	void RandomLottery();
	void Init();
	void End();
	void Update();
	void Draw();

private:
	int slot[3];
	int m_PassiveGraph[4];
	PassiveEffect* pPassiveEffect;
};