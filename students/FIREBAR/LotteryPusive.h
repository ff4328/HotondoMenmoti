#pragma once
#include "WeaponManager.h"
#include "PlayerStatus.h"

enum class Passive
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
	//デフォルトこんすとら
	LotteryPusive();

	/// <summary>
	/// コンストラクタ武器とプレイヤーのステータス取得
	/// </summary>
	/// <param name="weaponMgr">WeaponManager</param>
	/// <param name="playerStatus">PlayerStatus</param>
	LotteryPusive(WeaponManager* weaponMgr, PlayerStatus* playerStatus);

	//デストラクタ
	~LotteryPusive() = default;

	/// <summary>
	/// 抽選
	/// </summary>
	void RandomLottery();

	/// <summary>
	/// passiveを選択
	/// </summary>
	/// <param name="v">スロットに入ってるPassive class</param>
	void SelectPassive(int v);

	//////////////////いつものセット
	void Init();
	void End();
	void Update(bool* f);
	void Draw();
	//////////////////

	/// <summary>
	/// レベルアップ時スロット表示
	/// </summary>
	/// <param name="f">true=表示</param>
	bool ShowSlot(bool f);


private:
	//抽選スロット
	int slot[3];

	//パッシブ画像
	int m_PassiveGraph[4];

	//スロットの何番目か
	int m_selectNum;

	bool m_oneShotoFlag;

	WeaponManager* weaponMgr;
	PlayerStatus* pPlayerStatus;
};