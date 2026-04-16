#include "Enemy.h"
#include<DxLib.h>
#include<math.h>
#include "Literal.h"
#include "Player.h"

namespace {

	const char* const kGoblinPath = "Resource\\Monsters Creatures Fantasy\\Sprites\\Goblin\\Run.png";

	const char* const kMushroomPath = "Resource\\Monsters Creatures Fantasy\\Sprites\\Mushroom\\Run.png";

	const char* const kFlyingEyePath = "Resource\\Monsters Creatures Fantasy\\Sprites\\Flying eye\\Run.png";

	const char* const kSkeletonPath = "Resource\\Monsters Creatures Fantasy\\Sprites\\Skeleton\\Run.png";
};


Enemy::Enemy():
	m_graphHandle{},
	m_enemySpeed(2.0f),
	m_currentPos(Vector2(400.0f,300.0f)),
	m_prevPos(m_currentPos),
	m_motionCounter(0),
	m_motionFrame(0),
	m_sizeX(150),
	m_sizeY(150),
	m_enmeyType(EnemyType::ENEMY_TYPE_GOBLIN)
{
}

void Enemy::Init()
{

	InitAnimation();
}

void Enemy::InitAnimation()
{
	LoadDivGraph(kGoblinPath,
		8, 8, 1, m_sizeX, m_sizeY,
		m_graphHandle[ENEMY_TYPE_GOBLIN]);
}

void Enemy::End()
{

}

void Enemy::Update()
{
	m_motionCounter++;
	if (m_motionCounter >= 10)
	{
		m_motionCounter = 0;
		m_motionFrame++;
		if (m_motionFrame >= 8)
		{
			m_motionFrame = 0;
		}
	}
}

void Enemy::Draw()
{


	DrawRotaGraph((int)m_currentPos.x, (int)m_currentPos.y,
		1.0f, 0, m_graphHandle[m_enmeyType][m_motionFrame], TRUE);

	printfDx("mobPosX : %f\n", m_currentPos.x);
	printfDx("mobPosX : %f\n", m_currentPos.y);

}


void Enemy::RestorePos()
{
	m_currentPos = m_prevPos;
}

void Enemy::UpdatePrevPos()
{
	m_prevPos = m_currentPos;
}
