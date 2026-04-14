#pragma once
#include "WeaponManager.h"
#include "PlayerStatus.h"

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
	LotteryPusive(WeaponManager* weaponMgr, PlayerStatus* playerStatus);
	~LotteryPusive() = default;

	void RandomLottery();
	void SelectPassive(int v);
	void Init();
	void End();
	void Update();
	void Draw();


private:
	int slot[3];
	int m_PassiveGraph[4];
	int m_selectNum;

	WeaponManager* weaponMgr;
	PlayerStatus* pPlayerStatus;
};