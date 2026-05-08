#include "Axe.h"

#include "../students/bamboojr36/Collision.h"
#include "../students/bamboojr36/Vector2.h"
#include "../students/bamboojr36/Random.h"

#include "../Camera.h"
#include"../System/SoundManager.h"
namespace
{
	const char* const kGraphPath = "Resource\\image\\Axe.png.png";

	float speedY = -10;
	constexpr float gravity = 0.3f;
	constexpr float kRotateAngle = 0.05f;
	constexpr float kAroundRotateMagnification = 2.0f;
}

Axe::Axe():
	m_graphHandle(),
	m_name("Axe"),
	m_damage(20),
	m_range(0),
	m_attackRange(2.0f),
	m_coolTime(330),
	m_weaponNum(2),
	m_appearTime(100),
	m_frameCount(0),
	m_appearCount(m_appearTime),
	m_isAppear(false),
	m_playerPosX(400.0f),
	m_playerPosY(300.0f),
	m_rotateAngle(0),
	m_angle(0),
	m_scale(0),
	m_isAlive(false),
	position(0,0),
	m_velocity(0,0),
	m_pCamera(nullptr),
	m_pCollision(nullptr)
{
	m_pCollision = std::make_unique<Collision>();
}

Axe::Axe(std::string name, float damage, float range, float attackRange, int coolTime, int weaponNum, Vector2 playerPos):
	m_graphHandle(),
	m_name(name),
	m_damage(damage),
	m_range(range),
	m_attackRange(attackRange),
	m_coolTime(coolTime),
	m_weaponNum(weaponNum),
	m_appearTime(100),
	m_frameCount(0),
	m_appearCount(m_appearTime),
	m_isAppear(false),
	m_playerPosX(playerPos.x),
	m_playerPosY(playerPos.y),
	m_rotateAngle(0),
	m_angle(0),
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
	m_scale = 20.0f / (float)m_imgW;
}


void Axe::End() {
	DeleteGraph(m_graphHandle);
}

void Axe::Update() {
	printfDx("\n\n%d\n\n", m_isAlive);
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
			position.x + 20 * m_attackRange, position.y + 20 * m_attackRange,
			GetColor(255, 0, 0), FALSE);

		if (!m_isAlive) return;
		float centerX = position.x + 10 * m_attackRange;
		float centerY = position.y + 10 * m_attackRange;

		// 中心座標（40×40 の中心）

		DrawRotaGraphF(
			centerX, centerY,
			m_scale * m_attackRange,
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
	if (!m_isAlive) {
		return Rect{ 0,0,0,0 };   // ★ 斧が死んでたら当たり判定なし
	}
	Rect myRect = {
		(position.x),
		(position.y),
		position.x + 20 * m_attackRange,
		position.y + 20 * m_attackRange
	};
	return myRect;
}

void Axe::Spawn(Vector2 startPos)
{
	m_isAlive = true;
	position = startPos;

	SoundManager::GetInstance().PlaySe(Sound::SE::Sword_Hits_Heavy_Metal);
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

	if (pCamera != nullptr) {
		if (position.x < pCamera->GetLeft() - margin ||
			position.x > pCamera->GetRight() + margin ||
			position.y > pCamera->GetBottom() + margin)
		{
			m_isAlive = false;   // ★ ここで死ぬ
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


bool Axe::CheckHit(Rect enemyRect)
{
	Collision collision;

	if (collision.CheckRectCommon(
		enemyRect,
		GetRects()))
	{
		return true;
	}

	return false;
}