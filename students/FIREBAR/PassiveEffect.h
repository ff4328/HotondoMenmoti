#pragma once
#include "WeaponManager.h"
#include "PlayerStatus.h"

class PassiveEffect
{
public:
	/// <summary>
	/// PassiveEffectのコンストラクタ
	/// </summary>
	PassiveEffect() = default;

	/// <summary>
	/// PassiveEffectのデストラクタ
	/// </summary>
	~PassiveEffect() = default;

	/// <summary>
	///	攻撃力増加
	/// </summary>
	/// <param name="weapon">対象武器</param>
	void AddAttackPower(Weapon& weapon);

	/// <summary>
	/// 攻撃範囲増加
	/// </summary>
	/// <param name="weapon">対象武器</param>
	void AddAttackRange(Weapon& weapon);

	/// <summary>
	/// プレイヤーの移動速度増加
	/// </summary>
	/// <param name="playerStatus">プレイヤー</param>
	void AddPlayerSpeed(PlayerStatus& playerStatus);

	/// <summary>
	/// プレイヤーの最大HP増加
	/// </summary>
	/// <param name="playerStatus">プレイヤー</param>
	void AddPlayerHp(PlayerStatus& playerStatus);
};