#include "Camera.h"

Camera::Camera()
{
}

void Camera::Init(PlayerMove* playermove)
{
}

void Camera::Update()
{
	targetX += (pPlayer->GetPosX() - targetX) / CAMERA_LATENCY;
	targetY += (pPlayer->GetPosY() - targetY) / CAMERA_LATENCY;
}

void Camera::Draw()
{

}

void Camera::