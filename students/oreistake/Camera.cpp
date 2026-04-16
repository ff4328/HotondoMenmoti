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
	m_targetX += ()
}

void Camera::Draw()
{

}

void Camera::Finalize()
{

}

