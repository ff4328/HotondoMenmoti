#include "MagicBottle.h"

#include <DxLib.h>
#include <iostream>
#include <math.h>
#include <string>
#include <memory>

#include "../students/bamboojr36/Collision.h"
#include "../students/bamboojr36/Vector2.h"
#include "../Utility/Color.h"
#include "../oreistake/Weapon/Magic.h"

namespace {

	// ƒtƒ@ƒCƒ‹ƒpƒX
	const char* const kGraphPath = "Resource\\image\\MagicBottle.png";

	// •Ší–¼‚Ì‹K’è’l
	const char* const kInitName = "katana";

	// —^ƒ_ƒ[ƒW‚Ì‹K’è’l
	constexpr float kDamege = 10.0f;

	// ŽË’ö‚Ì‹K’è’l
	constexpr float kRange = 40.0f;

	// UŒ‚”ÍˆÍ‚Ì‹K’è’l
	constexpr float kAttackRange = 2.0f;

	// •Šíƒiƒ“ƒo[‚Ì‹K’è’l
	constexpr int kWeaponNumber = 1;

	// ƒN[ƒ‹ƒ^ƒCƒ€‚Ì‹K’è’l
	constexpr int kCoolTime = 150;

	// oŒ»ŽžŠÔ‚Ì‹K’è’l
	constexpr int kAppearTime = 120;

	// •Ší•\Ž¦À•W‚Ì‰ñ“]Šp“x‚Ì‹K’è’l
	constexpr float kRotateAngle = 0.05f;

	// •Ší•\Ž¦À•W‚ªˆêŽü‚·‚é‚Ü‚Å‚Ì”{—¦‚Ì‹K’è’l
	constexpr float kAroundRotateMagnification = 2.0f;

	// Œ»ÝUŒ‚”ÍˆÍ‚ª‘Œ¸‚·‚é”{—¦‚Ì‹K’è’l
	constexpr double kScaleIncreaseMagnification = 0.1;

	// ‰æ‘œ‚ð‰ñ“]•`‰æ‚·‚é‰æ–Êã‚Ì’†SXÀ•W‚Ì‹K’è’l
	constexpr int kImageCenterPosX = 8;

	// ‰æ‘œ‚ð‰ñ“]•`‰æ‚·‚é‰æ–Êã‚Ì’†SXÀ•W‚Ì‹K’è’l
	constexpr int kImageCenterPosY = 49;

	// “æ’[‚Ì‹K’è’l
	constexpr float kKatanaHeadPos = 50.0f;

	//Œ»Ý‚Ìó‘Ô
	State kstate;

	//Œ»ÝÀ•W
	float kposX;
	float kposY;

	//—Ž‚Æ‚·À•W
	float ktargetX=400;
	float ktargetY=300;

	//—Ž‚¿‚é‘¬“x
	float kfallSpeed;

	//¶‘¶ŽžŠÔ
	int ktimer;
}

/////////////////////////////////////////////////////////////////////////////////////////

MagicBottle::MagicBottle():
	m_graphHandle(),
	m_name(kInitName),
	m_damage(kDamege),
	m_range(kRange),
	m_attackRange(kAttackRange),
	m_coolTime(kCoolTime),
	m_weaponNum(kWeaponNumber),
	m_appearTime(kAppearTime),
	m_frameCount(0),
	m_appearCount(m_appearTime),
	m_isAppear(false),
	m_playerPosX(400.0f),
	m_playerPosY(300.0f),
	m_rotateAngle(0),
	m_angle(0),
	m_katanaTerminalPosX(0),
	m_katanaTerminalPosY(0),
	m_scale(0.0),
	m_state(State::Idle),
	m_posX(0),
	m_posY(0),
	m_targetX(0),
	m_targetY(0),
	m_fallSpeed(0),
	m_timer(0)
{
}


MagicBottle::MagicBottle(
	std::string name, 
	float damage,
	float range, 
	float attackRange, 
	int coolTime, 
	int weaponNum, 
	Vector2 playerPos):
	m_graphHandle(),
	m_name(name),
	m_damage(damage),
	m_range(range),
	m_attackRange(attackRange),
	m_coolTime(coolTime),
	m_weaponNum(weaponNum),
	m_appearTime(kAppearTime),
	m_frameCount(0),
	m_appearCount(m_appearTime),
	m_isAppear(false),
	m_playerPosX(playerPos.x),
	m_playerPosY(playerPos.y),
	m_rotateAngle(0),
	m_angle(0),
	m_katanaTerminalPosX(0),
	m_katanaTerminalPosY(0),
	m_scale(0.0),
	m_state(State::Idle),
	m_posX(0),
	m_posY(0),
	m_targetX(0),
	m_targetY(0),
	m_fallSpeed(0),
	m_timer(0)
{

}

void MagicBottle::Init()
{
	m_graphHandle = LoadGraph(kGraphPath);
}

void MagicBottle::Init(Vector2 playerPos)
{
	m_graphHandle = LoadGraph(kGraphPath);
	m_playerPosX = playerPos.x;
	m_playerPosY = playerPos.y;
}

void MagicBottle::End()
{
	DeleteGraph(m_graphHandle);
}

void MagicBottle::Update()
{
	//UpdateKatana();
	switch (m_state)
	{
	case State::Idle:
		m_attackRange-=2;
		break;

	case State::Falling:
		m_posY += m_fallSpeed;

		if (m_posY >= m_targetY)
		{
			m_posY = m_targetY;
			m_state = State::Impact;
			m_timer = 90;
		}
		break;

	case State::Impact:
		m_timer--;

		if (m_timer <= 0)
		{
			m_state = State::Idle;
		}
		break;
	}
}

void MagicBottle::Draw(int v)
{
	if (m_state == State::Falling)
	{
		DrawGraph(m_posX, m_posY, v, true);
	}
	else if (m_state == State::Impact)
	{
		DrawCircle(m_targetX, m_targetY, m_attackRange, Color::kCyan, true);
	}
	else
	{
		DrawCircle(m_targetX, m_targetY, m_attackRange, Color::kCyan, true);
	}
}

Rect Magic::GetCheckRect()
{
	Rect myRect = {
		(m_katanaTerminalPosX)+(cosf(m_rotateAngle) * kKatanaHeadPos) * m_scale,
			(m_katanaTerminalPosY)+(sinf(m_rotateAngle) * kKatanaHeadPos) * m_scale,
			(m_katanaTerminalPosX),
			m_katanaTerminalPosY
	};

	return myRect;
}

/////////////////////////////////////////////////////////////////////////////////////////

void MagicBottle::UpdateKatana()
{
	m_rotateAngle += kRotateAngle;
	if (m_rotateAngle >= (DX_PI_F * kAroundRotateMagnification))
		m_rotateAngle = 0.0f;

	m_angle += (180.0f / DX_PI_F * kRotateAngle);
	if (m_angle >= 360.0f)
		m_angle = 0;

	if (m_coolTime <= m_frameCount) {
		m_isAppear = true;

		if (m_appearCount > 0) {

			if (m_scale < m_attackRange)
				m_scale += kScaleIncreaseMagnification;
			if (m_scale >= m_attackRange)
				m_scale = m_attackRange;
		}

		if (m_coolTime <= 0)return;
		m_appearCount--;
	}
	else
	{
		m_frameCount++;
	}


	if (m_appearCount <= 0) {
		if (m_scale >= 0) {
			m_scale -= kScaleIncreaseMagnification;
		}
		else
		{
			m_scale = 0.0;
			m_isAppear = false;
			m_appearCount = m_appearTime;
			m_frameCount = 0;
		}
	}

}

void MagicBottle::DrawKatana()
{
	m_katanaTerminalPosX = m_playerPosX + (cosf(m_rotateAngle) * m_range);
	m_katanaTerminalPosY = m_playerPosY + (sinf(m_rotateAngle) * m_range);

	if (m_isAppear) {

		// «DrawRotaGraph2‚É‚Â‚¢‚Ä
		// https://dxlib.xsrv.jp/function/dxfunc_graph1.html#R3N19
		DrawRotaGraph2(m_katanaTerminalPosX, m_katanaTerminalPosY,
			kImageCenterPosX, kImageCenterPosY, m_scale,
			(DX_PI_F / 180.0f * m_angle) + (DX_PI_F / 180.0f * 90.0f),
			m_graphHandle, true, false);

#ifdef _DEBUG
		DrawBox((m_katanaTerminalPosX)+(cosf(m_rotateAngle) * kKatanaHeadPos) * m_scale,
			(m_katanaTerminalPosY)+(sinf(m_rotateAngle) * kKatanaHeadPos) * m_scale,
			(m_katanaTerminalPosX),
			m_katanaTerminalPosY,
			Color::kCyan, false);
#endif // _DEBUG

	}

}

void MagicBottle::DebugUpdate()
{
	if (CheckHitKey(KEY_INPUT_F) == 1 && m_attackRange > 2.0) {
		m_attackRange -= 0.2;
	}

	if (CheckHitKey(KEY_INPUT_G) == 1 && m_attackRange < 3.0) {
		m_attackRange += 0.2;
	}

}

void MagicBottle::DebugDraw()
{
	m_katanaTerminalPosX = 400.0f + (cosf(m_rotateAngle) * m_range);
	m_katanaTerminalPosY = 300.0f + (sinf(m_rotateAngle) * m_range);

	

	if (m_isAppear) {

		//DrawRotaGraph(x, y, 3.0, (DX_PI_F / 180.0f * m_angle) + (DX_PI_F / 180.0f * 90.0f), m_graphHandle, true, false);
		DrawRotaGraph2(m_katanaTerminalPosX, m_katanaTerminalPosY,
			kImageCenterPosX, kImageCenterPosY, m_scale, 
			(DX_PI_F / 180.0f * m_angle) + (DX_PI_F / 180.0f * 90.0f),
			m_graphHandle, true, false);

		DrawBox((m_katanaTerminalPosX) + (cosf(m_rotateAngle) * kKatanaHeadPos) * m_scale,
			(m_katanaTerminalPosY)+ (sinf(m_rotateAngle) * kKatanaHeadPos) * m_scale,
			(m_katanaTerminalPosX),
			m_katanaTerminalPosY,
			Color::kCyan, false);
	}

	printfDx("\nx : %4f // y : %4f\n", m_katanaTerminalPosX, m_katanaTerminalPosY);
	printfDx("m_rotateAngle : %4f\n", m_rotateAngle);
	printfDx("cosf(m_rotateAngle) : %4f\n", cosf(m_rotateAngle));
	printfDx("sinf(m_rotateAngle) : %4f\n", sinf(m_rotateAngle));
	printfDx("m_angle : %4f\n", m_angle);
	printfDx("m_coolTime : %d\n", m_coolTime);
	printfDx("m_appearTime : %d\n", m_appearTime);
	printfDx("m_frameCount : %d\n", m_frameCount);
	printfDx("m_appearCount : %d\n", m_appearCount);
}

void MagicBottle::StartFall()
{
	m_state = State::Falling;

	float radius = GetRand(200);
	float angle = GetRand(360) * DX_PI_F / 180.0f;

	m_targetX = m_playerPosX + cosf(angle) * radius;
	m_targetY = m_playerPosY + sinf(angle) * radius;

	m_posX = m_targetX;
	m_posY = m_targetY - 600.0f;

	m_fallSpeed = 15.0f;
}

Rect MagicBottle::GetCheckRect()
{
	if (m_state != State::Impact) return { 0,0,0,0 };

	return {
		static_cast<int>(m_targetX) - static_cast<int>(m_attackRange),
		static_cast<int>(m_targetY) - static_cast<int>(m_attackRange),
		static_cast<int>(m_targetX) + static_cast<int>(m_attackRange),
		static_cast<int>(m_targetY) + static_cast<int> (m_attackRange)
	};
}