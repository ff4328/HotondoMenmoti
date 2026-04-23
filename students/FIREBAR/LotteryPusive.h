#pragma once
#include "WeaponManager.h"
#include "PlayerStatus.h"
#include "../students/mcd6752Tuyoshi/ExpBar/EXPBar.h"

/// <summary>
/// パッシブの種類ＨＰＨＥＡＬ個別
/// </summary>
enum class Passive
{
	ATTACKRANGE,	// 攻撃範囲
	ATTACKSPEED,	// 攻撃速度
	MAXHPUP,		// 最大HP
	MOVESPEED,		// 移動速度
	AXE,			// 斧
	ARROW,			// 矢
	KATANA,			// 刀
	MAGIC,			// 魔法
	MAXPUSIVE,		// パッシブ最大数
	HPHEAL,			// HP回復(レベル上限時出現
};


class LotteryPassive
{
public:
	//デフォルトこんすとら
	LotteryPassive();

	/// <summary>
	/// コンストラクタ武器とプレイヤーのステータス取得
	/// </summary>
	/// <param name="weaponMgr">WeaponManager</param>
	/// <param name="playerStatus">PlayerStatus</param>
	LotteryPassive(WeaponStatus* weaponMgr, PlayerStatus* playerStatus, EXPBar* expBar);

	//デストラクタ
	~LotteryPassive() = default;

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
	void End() const;
	void Update();
	void Draw();
	//////////////////

	/// <summary>
	/// レベルアップ時スロット表示
	/// </summary>
	/// <param name="f">true=表示</param>
	bool ShowSlot();

private:
	//抽選スロット
	int slot[3];

	//パッシブ画像
	int m_PassiveGraph[static_cast<int>(Passive::HPHEAL)+1];

	//スロットの何番目か
	int m_selectNum;

	//ランダム抽選を一回だけ呼ぶ
	bool m_oneShotoFlag;

	/// <summary>
	/// パッシブの最大レベル
	/// </summary>
	int m_passiveLevel[static_cast<int>(Passive::MAXPUSIVE)];

	//WeaponStatusのポインタ
	WeaponStatus* weaponMgr;

	//PlayerStatusのポインタ
	PlayerStatus* pPlayerStatus;

	//EXPBarのポインタ
	EXPBar* m_pEXPBar;
};