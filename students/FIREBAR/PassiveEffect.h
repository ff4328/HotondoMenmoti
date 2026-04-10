#pragma once
#include "WeaponManager.h"
#include "PlayerStatus.h"

class PassiveEffect
{
public:
	PassiveEffect() = default;
	~PassiveEffect() = default;

	/// <summary>
	///	攻撃力増加
	/// </summary>
	/// <param name="weapon">対象武器</param>
	/// <returns>ステータス変更後の対象武器</returns>
	Weapon AddAttackPower(Weapon& weapon);

	/// <summary>
	/// 攻撃範囲増加
	/// </summary>
	/// <param name="weapon">対象武器</param>
	/// <returns>ステータス変更後の対象武器</returns>
	Weapon AddAttackRange(Weapon& weapon);

	/// <summary>
	/// プレイヤーの移動速度増加
	/// </summary>
	/// <param name="playerStatus">プレイヤー</param>
	/// <returns>ステータス変更後のプレイヤー</returns>
	PlayerStatus AddPlayerSpeed(PlayerStatus& playerStatus);

	/// <summary>
	/// プレイヤーの最大HP増加
	/// </summary>
	/// <param name="playerStatus">プレイヤー</param>
	/// <returns>ステータス変更後のプレイヤー</returns>
	PlayerStatus AddPlayerHp(PlayerStatus& playerStatus);
};