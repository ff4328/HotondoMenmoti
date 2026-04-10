#include "PlayerStatus.h"

namespace
{
	float kPlayerHp = 100.0f;
	float kPlayerSpeed = 2.0f;
}

PlayerStatus::PlayerStatus():
	hp(kPlayerHp),
	speed(kPlayerSpeed)
{}

void PlayerStatus::SetPlayerStatus()
{
	hp = kPlayerHp;
	speed = kPlayerSpeed;
}