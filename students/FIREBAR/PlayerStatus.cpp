#include "PlayerStatus.h"

namespace
{
	float kPlayerHp = 100.0f;
	float kPlayerSpeed = 2.0f;
	float kPlayerAttackPower = 5.0f;
}

PlayerStatus::PlayerStatus():
	hp(kPlayerHp),
	speed(kPlayerSpeed),
	attackPower(kPlayerAttackPower)
{}

void PlayerStatus::SetPlayerStatus()
{
	hp = kPlayerHp;
	speed = kPlayerSpeed;
	attackPower = kPlayerAttackPower;
}
