#include "Camera.h"
#include "Player.h"
#include "../Utility/Game.h"
#include "../students/mcd6752Tuyoshi/Map/Map.h"


Camera::Camera():
	m_targetX(0),
	m_targetY(0),
	m_pPlayermove(nullptr),
	m_pMap(nullptr)

{
}

void Camera::Init(PlayerMove* playermove,Map* map)
{

	m_pPlayermove = playermove;
	m_pMap = map;

	m_targetX = m_pPlayermove->GetModelPos().x;
	m_targetY = m_pPlayermove->GetModelPos().y;
	
	GenerateWorldScreen();
}

void Camera::Update()
{

	m_targetX += (m_pPlayermove->GetModelPos().x - m_targetX) / CAMERA_LATENCY;
	m_targetY += (m_pPlayermove->GetModelPos().y - m_targetY) / CAMERA_LATENCY;

	float worldScreenLeft = 0;
	float worldScreenRight = m_pMap->GetMapChipNumX() * m_pMap->GetMapChipChangeSize();
	float worldScreenUp = 0;
	float worldScreenDown = m_pMap->GetMapChipNumY() * m_pMap->GetMapChipChangeSize();

	// worldScreenの左端が描画されていたら
	if ((int)m_targetX - Game::kScreenWidth / 2 + CAMERA_HORIZONTAL_MARGIN < worldScreenLeft)
	{
		m_targetX = worldScreenLeft + Game::kScreenWidth / 2 - CAMERA_HORIZONTAL_MARGIN;
	}

	// worldScreenの右端が描画されていたら
	if ((int)m_targetX + Game::kScreenWidth / 2 + CAMERA_HORIZONTAL_MARGIN > worldScreenRight)
	{
		m_targetX = worldScreenRight - Game::kScreenWidth / 2 - CAMERA_HORIZONTAL_MARGIN;
	}

	// worldScreenの上端が描画されていたら
	if ((int)m_targetY - Game::kScreenHeight / 2 + CAMERA_VERTICAL_MARGIN < worldScreenUp)
	{
		m_targetY = worldScreenUp + Game::kScreenHeight / 2 - CAMERA_VERTICAL_MARGIN;
	}

	// worldScreenの下端が描画されていたら
	if ((int)m_targetY + Game::kScreenHeight / 2 + CAMERA_VERTICAL_MARGIN > worldScreenDown)
	{
		m_targetY = worldScreenDown - Game::kScreenHeight / 2 - CAMERA_VERTICAL_MARGIN;
	}

}

void Camera::Draw()
{

	DrawRectGraph
	(
		0, 0,										// 描画座標の左上
		(int)m_targetX - Game::kScreenWidth / 2,	// 描画元の左端の座標
		(int)m_targetY - Game::kScreenHeight / 2,	// 描画元の上端の座標
		Game::kScreenWidth, Game::kScreenHeight,	// 描画するサイズ
		m_worldScreen,								// 描画のもとになるバッファ
		false
	);
}

void Camera::End()
{
	DeleteGraph(m_worldScreen);
}

void Camera::GenerateWorldScreen()
{
	m_worldScreen = MakeScreen(
		m_pMap->GetMapChipNumX() * m_pMap->GetMapChipChangeSize(),
		m_pMap->GetMapChipNumY() * m_pMap->GetMapChipChangeSize(),
		false);
}
