#include "PlayerStatus.h"

#include <string>
#include <vector>
#include <iostream>
#include "DxLib.h"

namespace
{
	float kPlayerHp = 100.0f;
	float kPlayerSpeed = 2.0f;
	int kPlayerMaxExp = 50;
	int kPlayerLevel = 0;
}
//名前、最大HP、現在のHP、スピード、経験値、レベル
PlayerStatus::PlayerStatus()
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
}
void PlayerStatus::End()
{

}
void PlayerStatus::Draw()
{
	for (const auto& player : players)
	{
		printfDx("名前：%s| HP：%f/%f| スピード：%f| 経験値：%d| レベル：%d\n",
			player.name.c_str(), player.currenthp, player.maxhp, player.moveSpeed, player.exp, player.level);
	}
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
		player.moveSpeed += 2.0f;
	}
}