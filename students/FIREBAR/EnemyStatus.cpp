#include "EnemyStatus.h"

/// <summary>
/// モンスターの定数
/// </summary>
const int MONSTER_NUM = 4;

//敵の名前、HP、攻撃力、移動速度
EnemyStatus::EnemyStatus()
{
	Enemys m_enemysList[] =
	{
		{"スケルトン",10,3,0.5f},
		{"キノコ",15,4,0.5f},
		{"ゴブリン",25,6,0.5f},
		{"コウモリ",5,2,1.0f},
	};

	for (int i = 0; i < MONSTER_NUM;i++)
	{
		enemys.push_back(m_enemysList[i]);
	}
}

void EnemyStatus::SetEnemyStatus()
{
	Enemys m_enemysList[] =
	{
		{"スケルトン",10,3,0.5f},
		{"キノコ",15,4,0.5f},
		{"ゴブリン",25,6,0.5f},
		{"コウモリ",5,2,1.0f},
	};

	for (int i = 0; i < MONSTER_NUM; i++)
	{
		enemys.push_back(m_enemysList[i]);
	}
}
void EnemyStatus::Init()
{
}
void EnemyStatus::End()
{
}
void EnemyStatus::Draw()
{
}
void EnemyStatus::Update()
{
}
