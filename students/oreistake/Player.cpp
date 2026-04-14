#include "Player.h"
#include "Literal.h"

#include <DxLib.h>
#include"../students/bamboojr36/Vector2.h"
#include"../Utility/Input.h"

namespace {

	const char* const kModelPath = "Resource\\Medieval Warrior Pack 2\\Sprites\\Idle.png";

}
Player::Player() :
	m_graphHandle{},
	m_playerSpeed(6.0f),
	/*m_posX(400.0f),
	m_posY(300.0f),*/
	m_sizeX(150),
	m_sizeY(150),
	m_motionCounter(0),
	m_motionFrame(0),
	m_pWeponMgr(nullptr),
	m_status(Status::STATUS_IDLE),
	m_currentPos(Vector2(400.0f,300.0f)),
	m_prevPos(m_currentPos)
{
}

void Player::Init()
{

	InitAnimation();


}

void Player::End()
{


}

void Player::InitAnimation()
{
	// プレイヤーの待機アニメーション読み込み
	LoadDivGraph(kModelPath,
		8, 8,1, m_sizeX, m_sizeY,
		m_graphHandle[STATUS_IDLE]);
}

void Player::Update()
{
	MoveHorizontal();
	MoveVertical();

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



void Player::Draw()
{

	DrawRotaGraph((int)m_currentPos.x, (int)m_currentPos.y,
		1.0f, 0, m_graphHandle[m_status][m_motionFrame], FALSE, FALSE);

	printfDx("PosX : %f\n", m_currentPos.x);
	printfDx("PosX : %f\n", m_currentPos.y);
	printfDx("speed : %f\n", m_playerSpeed);
}

void Player::MoveHorizontal()
{
	// 右移動
	if (CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D))
	{
		m_currentPos.x += m_playerSpeed;
	}

	// 左移動
	if (CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A))
	{
		m_currentPos.x -= m_playerSpeed;
	}
}

void Player::MoveVertical()
{
	// 下移動
	if (CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_S))
	{
		m_currentPos.y += m_playerSpeed;
	}

	// 上移動
	if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_W))
	{
		m_currentPos.y -= m_playerSpeed;
	}
}

void Player::Finalize()
{

}

void Player::RestorePos()
{
	m_currentPos = m_prevPos;
}

void Player::UpdatePrevPos()
{
	m_prevPos = m_currentPos;
}

