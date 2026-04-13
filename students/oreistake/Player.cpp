#include "Player.h"
#include "Literal.h"
<<<<<<< HEAD
#include <DxLib.h>
#include"../students/bamboojr36/Vector2.h"
#include"../Utility/Input.h"

namespace {

	const char* const kModelPath = "Resource\\Medieval Warrior Pack 2\\Sprites\\Idle.png";
=======


namespace {

	
>>>>>>> 8b6342a078cdd2be1fa9f28a9b90a2199c487ced

}


<<<<<<< HEAD
Player::Player() :
	m_graphHandle{},
	m_playerSpeed(6.0f),
	m_posX(400.0f),
	m_posY(300.0f),
	m_sizeX(150),
	m_sizeY(150),
	m_motionCounter(0),
	m_motionFrame(0),
	m_status(Status::STATUS_IDLE),
	m_pVector2(0)
{
}
=======
Player::Player()
{}
>>>>>>> 8b6342a078cdd2be1fa9f28a9b90a2199c487ced

void Player::Init()
{

	InitAnimation();


}

void Player::End()
{


}


void Player::InitAnimation()
{


<<<<<<< HEAD
		}
	}

	// プレイヤーの待機アニメーション読み込み
	LoadDivGraph(kModelPath,
		8, 8, 1, m_sizeX, m_sizeY,
		m_graphHandle[STATUS_IDLE]);

=======
>>>>>>> 8b6342a078cdd2be1fa9f28a9b90a2199c487ced
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
<<<<<<< HEAD
	DrawRotaGraph((int)m_posX, (int)m_posY,
		1.0f, 0, m_graphHandle[m_status][m_motionFrame], FALSE, FALSE);

	printfDx("PosX : %f\n", m_posX);
	printfDx("PosX : %f\n", m_posY);
	//printfDx("表示されてるyooooooooooooooooooooooooooooo");
	///*int h = LoadGraph("Resource\\Medieval Warrior Pack 2\\Sprites\\Idle.png");
	//printfDx("test = %d\n", h);*/
	/*printfDx("handle = %d\n", m_graphHandle[STATUS_IDLE][0]);*/
}

void Player::MoveHorizontal()
{
	// 右移動
	if (Input::IsDown(PAD_INPUT_RIGHT) || Input::IsDown(PAD_INPUT_6))
	{
		m_posX += m_playerSpeed;
	}

	// 左移動
	if (Input::IsDown(PAD_INPUT_LEFT) || Input::IsDown(PAD_INPUT_4))
	{
		m_posX -= m_playerSpeed;
	}
}

void Player::MoveVertical()
{
	// 下移動
	if (Input::IsDown(PAD_INPUT_DOWN) || Input::IsDown(PAD_INPUT_5))
	{
		m_posY -= m_playerSpeed;
	}

	// 上移動
	if (Input::IsDown(PAD_INPUT_UP) || Input::IsDown(PAD_INPUT_8))
	{
		m_posY += m_playerSpeed;
	}
=======
	
>>>>>>> 8b6342a078cdd2be1fa9f28a9b90a2199c487ced
}

void Player::Finalize()
{

}
