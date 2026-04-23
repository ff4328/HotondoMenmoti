#include "PlayerStatus.h"

#include <string>
#include <vector>
#include <iostream>
#include "DxLib.h"

#include "../bamboojr36/Collision.h"

namespace
{
	float kPlayerHp = 100.0f;
	float kPlayerSpeed = 2.0f;
	int kPlayerMaxExp = 50;
	int kPlayerLevel = 0;
}
//名前、最大HP、現在のHP、スピード、経験値、レベル
PlayerStatus::PlayerStatus() :
	m_pCollision(nullptr),
	m_pHeal(nullptr)
{

	Player kensi = { "剣士",kPlayerHp,kPlayerHp,kPlayerSpeed ,0,0 };
	players.push_back(kensi);
}

void PlayerStatus::SetPlayerStatus()
{
	Player kensi = { "剣士",kPlayerHp,kPlayerHp,kPlayerSpeed ,0,0 };
	players.push_back(kensi);
}

void PlayerStatus::Init()
{
	m_pCollision = std::make_unique<Collision>();
	m_pHeal = std::make_unique<Heal>();
}
void PlayerStatus::End()
{
}
void PlayerStatus::Draw()
{
}
void PlayerStatus::Update()
{
}

void PlayerStatus::AddMaxHP()
{
	for (auto& player : players)
	{
		player.maxhp += 20;
	}
}

void PlayerStatus::AddSpeed()
{
	for (auto& player : players)
	{
		player.moveSpeed += 0.4f;
	}
}

void PlayerStatus::HealHP()
{
	for (auto& player : players)
	{
		player.currenthp += 20;
		if (player.currenthp > player.maxhp)
			player.currenthp = player.maxhp;
	}
}

float PlayerStatus::GetMoveSpeed() const
{
	return players[0].moveSpeed;
}

float PlayerStatus::GetMaxHP() const
{
	return players[0].maxhp;
}

void PlayerStatus::SetCurrentHP(float value)
{
	players[0].currenthp -= value;
}

float PlayerStatus::GetCurrentHP() const
{
	return players[0].currenthp;
}
