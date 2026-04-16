#include "Camera.h"

Camera::Camera():
	m_targetX(0),
	m_targetY(0),
	m_pPlayermove(nullptr)
{
}

void Camera::Init(PlayerMove* playermove)
{

	m_pPlayermove = new PlayerMove();
	m_pPlayermove = playermove;

}

void Camera::Update()
{

}

void Camera::Draw()
{

	//DrawRectGraph
	//(
	//	0, 0,									// 描画座標の左上
	//	(int)targetX - WINDOW_WIDTH / 2,	// 描画元の左端の座標
	//	(int)targetY - WINDOW_HEIGHT / 2,	// 描画元の上端の座標
	//	WINDOW_WIDTH, WINDOW_HEIGHT,			// 描画するサイズ
	//	worldScreen,							// 描画のもとになるバッファ
	//	false
	//);
}

void Camera::Finalize()
{

}

void Camera::GenerateWorldScreen()
{

}
