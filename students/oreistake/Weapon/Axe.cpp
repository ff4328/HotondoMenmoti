#include "Axe.h"

#include "../students/bamboojr36/Collision.h"
#include "../students/bamboojr36/Vector2.h"
#include "../students/bamboojr36/Random.h"

#include "../Camera.h"
namespace
{
	const char* const kGraphPath = "Resource\\image\\Axe.png.png";

	float speedY = -10;
	constexpr float gravity = 0.3f;
	constexpr float kRotateAngle = 0.05f;
	constexpr float kAroundRotateMagnification = 2.0f;
	int m_imgW, m_imgH;
	float m_rotateAngle = 0.0f;

}

Axe::Axe():
	m_graphHandle(-1),
	m_range(0),
	m_coolTime(330),
	m_appearTime(),
	m_angle(),
	m_isAlive(false),
	m_pCamera(nullptr),
	m_pCollision(nullptr)
{
	m_pCollision = std::make_unique<Collision>();
}

Axe::Axe(std::string name, float damage, float range, float attackRange, int coolTime, int weaponNum, Vector2 playerPos):
	m_coolTime(330),
	m_isAlive(false),
	position(playerPos),
	m_pCollision(nullptr)
{
	m_pCollision = std::make_unique<Collision>();
}

void Axe::Init() {
	position = Vector2(400.0f, 200.0f);
	m_graphHandle = LoadGraph(kGraphPath);

	// 画像サイズ取得
	GetGraphSize(m_graphHandle, &m_imgW, &m_imgH);

	// 40×40 に収めるための拡大率
	m_scale = 40.0f / (float)m_imgW;
}


void Axe::End() {
	DeleteGraph(m_graphHandle);
}

void Axe::Update() {
	if (m_isAlive) {

		// x はランダム角度で飛ぶ
		position.x += m_velocity.x;

		// y は重力で落ちる
		m_velocity.y += gravity;
		position.y += m_velocity.y;

		// 回転
		m_rotateAngle += kRotateAngle;
		if (m_rotateAngle >= DX_PI_F * 2)
			m_rotateAngle = 0.0f;
	}

	if (m_pCamera != nullptr) {
		UpdateAxe(m_pCamera);
	}
}

void Axe::Draw() {
	if (m_isAlive) {

		// デバッグ用の当たり判定
		DrawBox(position.x, position.y,
			position.x + 40, position.y + 40,
			GetColor(255, 0, 0), FALSE);

		if (!m_isAlive) return;

		// 中心座標（40×40 の中心）
		float centerX = position.x + 20.0f;
		float centerY = position.y + 20.0f;

		DrawRotaGraphF(
			centerX, centerY,
			m_scale,
			m_rotateAngle,
			m_graphHandle,
			TRUE
		);
	}
}


void Axe::DebugDraw() {

}

Rect Axe::GetRects()
{
	Rect myRect = {
		(position.x),
		(position.y),
		(position.x + 40),
		(position.y + 40),
	};
	return myRect;
}

void Axe::Spawn(Vector2 startPos)
{
	m_isAlive = true;
	position = startPos;

	float throwSpeed = MyRandom::Int(0, 5);

	int randDeg = MyRandom::Int(0,180);

	float throwAngle = randDeg * DX_PI_F / 180.0f;

	// ★ x方向だけランダム角度で飛ばす
	m_velocity.x = cosf(throwAngle) * throwSpeed;

	// ★ y方向は重力だけで落ちる
	m_velocity.y = speedY;
}

void Axe::UpdateAxe(const Camera* pCamera)
{
	float margin = 64.0f;

	// カメラが存在する場合の判定
	if (pCamera != nullptr) {
		if (position.x < pCamera->GetLeft() - margin ||
			position.x > pCamera->GetRight() + margin ||
			position.y > pCamera->GetBottom() + margin)
		{
			m_isAlive = false;
		}
	}
	else {
		m_isAlive = false;
	}

}

void Axe::UpdateAxes()
{
	m_rotateAngle += kRotateAngle;
	if (m_rotateAngle >= (DX_PI_F * kAroundRotateMagnification))
		m_rotateAngle = 0.0f;

	m_angle += (180.0f / DX_PI_F * kRotateAngle);
	if (m_angle >= 360.0f)
		m_angle = 0;

	if (m_coolTime <= m_frameCount) {
		Spawn(position);
		m_frameCount = 0;
	}
	else {
		m_frameCount++;
	}
}

void Axe::DrawAxe()
{
}
