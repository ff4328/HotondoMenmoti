#include "PassiveEffect.h"

Weapon PassiveEffect::AddAttackPower(Weapon& weapon)
{
	weapon.damage += 5.0f; // 攻撃力を5増加させる例
    return weapon;
}

Weapon PassiveEffect::AddAttackRange(Weapon& weapon)
{
	weapon.range += 2.0f; // 攻撃範囲を2増加させる例
    return weapon;
}

PlayerStatus PassiveEffect::AddPlayerSpeed(PlayerStatus& playerStatus)
{
	playerStatus.speed += 1.0f; // プレイヤーの移動速度を1増加させる例
    return playerStatus;
}

PlayerStatus PassiveEffect::AddPlayerHp(PlayerStatus& playerStatus)
{
	playerStatus.hp += 20.0f; // プレイヤーの最大HPを20増加させる例
    return playerStatus;
}
