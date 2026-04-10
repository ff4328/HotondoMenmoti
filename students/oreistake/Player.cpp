#include "Player.h"
#include "Literal.h"
#include <DxLib.h>

namespace {

	const char* const kModelPath = "..\\Resource\\Medieval Warrior Pack 2\\Sprites\\Idle.png";

}


Player::Player() :
	m_graphHandle{},
	m_posX(1),
	m_posY(1),
	m_sizeX(1),
	m_sizeY(1),
	m_motionCounter(1),
	m_motionFrame(1)
	//m_status(Status::STATUS_IDLE)
{
}

void Player::Init()
{

	InitAnimation();

}

void Player::End()
{

	for (int i = 0; i < CHARA_STATUS_NUM; i++)
	{
		for (int j = 0; j < CHARA_MOTION_NUM; j++)
		{
			DeleteGraph(m_graphHandle[i][j]);
		}
	}

}


void Player::InitAnimation()
{

	// グラフィックハンドルの初期化
	for (int i = 0; i < CHARA_STATUS_NUM; i++)
	{
		for (int j = 0; j < CHARA_MOTION_NUM; j++)
		{
			m_graphHandle[i][j] = 0;

		}
	}

	LoadDivGraph(kModelPath,
		8, 8, 1, m_sizeX, m_sizeY,
		m_graphHandle[STATUS_IDLE]);

	
}

void Player::Update()
{

}



void Player::Draw()
{
	DrawGraph(0, 0, m_graphHandle[STATUS_IDLE][0], TRUE);
}

