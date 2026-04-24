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

enum class State
{
	Idle,     // 待機
	Falling,  // 落下中
	Impact    // 着弾（ダメージ判定）
};

namespace {

	// ファイルパス
	const char* const kGraphPath = "Resource\\image\\MagicBottle.png";

	// 武器名の規定値
	const char* const kInitName = "katana";

	// 与ダメージの規定値
	constexpr float kDamege = 10.0f;

	// 射程の規定値
	constexpr float kRange = 40.0f;

	// 攻撃範囲の規定値
	constexpr float kAttackRange = 2.0f;

	// 武器ナンバーの規定値
	constexpr int kWeaponNumber = 1;

	// クールタイムの規定値
	constexpr int kCoolTime = 150;

	// 出現時間の規定値
	constexpr int kAppearTime = 120;

	// 武器表示座標の回転角度の規定値
	constexpr float kRotateAngle = 0.05f;

	// 武器表示座標が一周するまでの倍率の規定値
	constexpr float kAroundRotateMagnification = 2.0f;

	// 現在攻撃範囲が増減する倍率の規定値
	constexpr double kScaleIncreaseMagnification = 0.1;

	// 画像を回転描画する画面上の中心X座標の規定値
	constexpr int kImageCenterPosX = 8;

	// 画像を回転描画する画面上の中心X座標の規定値
	constexpr int kImageCenterPosY = 49;

	// 刀先端の規定値
	constexpr float kKatanaHeadPos = 50.0f;

	//現在の状態
	State kstate;

	//現在座標
	float kposX;
	float kposY;

	//落とす座標
	float ktargetX=400;
	float ktargetY=300;

	//落ちる速度
	float kfallSpeed;

	//生存時間
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
	m_scale(0.0)
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
	m_scale(0.0)
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
	switch (kstate)
	{
	case State::Idle:
		m_frameCount++;
		if (m_frameCount > m_coolTime)
		{
			StartFall();
			m_frameCount = 0;
		}
		break;

	case State::Falling:
		kposY += kfallSpeed;

		if (kposY >= ktargetY)
		{
			kposY = ktargetY;
			kstate = State::Impact;
			ktimer = 90; // ダメージ表示時間
		}
		break;

	case State::Impact:
		ktimer--;

		if (ktimer <= 0)
		{
			kstate = State::Idle;
		}
		break;
	}

#ifdef _DEBUG
	DebugUpdate();
#endif // _DEBUG
}

void MagicBottle::Draw()
{
	//DrawKatana();
	if (kstate == State::Falling)
	{
		DrawGraph(kposX, kposY, m_graphHandle, true);
	}
	else if (kstate == State::Impact)
	{
		// 範囲表示
		DrawCircle(ktargetX, ktargetY, m_attackRange, Color::kCyan, true);
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

		// ↓DrawRotaGraph2について
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
	kstate = State::Falling;

	float radius = 200.0f;
	float angle = GetRand(360) * DX_PI_F / 180.0f;

	ktargetX = m_playerPosX + cosf(angle) * radius;
	ktargetY = m_playerPosY + sinf(angle) * radius;

	kposX = ktargetX;
	kposY = ktargetY - 300.0f; // 上から落とす

	kfallSpeed = 10.0f;
}

Rect MagicBottle::GetCheckRect()
{
	if (kstate != State::Impact) return { 0,0,0,0 };

	Rect rect = {
		ktargetX - m_attackRange,
		ktargetY - m_attackRange,
		ktargetX + m_attackRange,
		ktargetY + m_attackRange
	};

	return rect;
}